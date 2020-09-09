#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <math.h>
#include "Calibration.h"

Calibration::Calibration(std::string calibrationPath)
{
    _calibrationPath = calibrationPath;
    LoadCalibration();
}

Calibration::~Calibration()
{
    //Insert deconstruction code here
}

int Calibration::GetRpm(int &triggersPerSecond)
{
    int currentRpm = 0;
    currentRpm = (triggersPerSecond * 60) / _teeth;
    return currentRpm;
}

float Calibration::GetTps(float &voltage)
{
    float tps = _tps.Value(voltage);
    return tps;
}


//Takes RPM value and TPS value to return the correct interpolated torque value from _torqueMap
int Calibration::GetTorque(int rpm, float tps)
{
    float xAxis_rpm_[8] {0, 1000, 2000, 3000, 4000, 5000, 6500, 8000}; //Predefined rpm point (maybe move into calibration.map at later point)
    float yAxis_tps_[8] {0, 10, 20, 35, 50, 75, 80, 100}; //TPS points see above comment
    float value = 0;

    //finds xAxis_rpm_ floating point position
    int x = 0;
    while(xAxis_rpm_[x] < rpm){
        x++;
    }
    float xPosition = (x + x + 1) / ((xAxis_rpm_[x] + xAxis_rpm_[x + 1]) / rpm); // works out steps across the axis
    xPosition = xPosition - floor(xPosition); //turns value into a percentage (0 - 1)

    //finds yAxis_tps_ floating point position
    int y=0;
    while(yAxis_tps_[y] < tps){
        y++;
    }
    float yPosition = (y + y + 1) / ((yAxis_tps_[y] + yAxis_tps_[y + 1]) / tps);  // works out steps across the axis
    yPosition = yPosition - floor(yPosition); //turns value into a percentage (0 - 1)

    //Finds 4 nearest cells in torqueMap_ from x and y position floats
    float a, b, c, d;
    if(x<7 && y<7 && x>0 && y>0){ //normal case
        a = _torqueMap[y-1][x-1];
        b = _torqueMap[y-1][x];
        c = _torqueMap[y][x-1];
        d = _torqueMap[y][x];
    }
    else if(x>=7 && y<7 && y>0) //X is at max
    {
        a = _torqueMap[y-1][7];
        b = a;
        c = _torqueMap[y][7];
        d = c;
    }
    else if(y>=7 && x<7 && x>0) //Y is at max
    {
        a = _torqueMap[7][x-1];
        b = _torqueMap[7][x];
        c = a;
        d = b;
    }
        else if(y>=7 && x>=7) //X & Y are at max
    {
        a = _torqueMap[7][7];
        b = a;
        c = a;
        d = a;
    }
    else if(x<=0 && y<=0){ //X & Y are at min
        a = _torqueMap[0][0];
        b = a;
        c = a;
        d = a;
    }
    else if(x<=0 && y>0){ //X is at min
        a = _torqueMap[y-1][0];
        b = a;
        c = _torqueMap[y][0];
        d = c;
    }
    else{ //Y is at min
        a = _torqueMap[0][x-1];
        b = _torqueMap[0][x];
        c = a;
        d = b;
    }
    
    //Interpolate a result
    float tableResult = 0;
    if( (a == b) && (a == c) && (c == d) ) { tableResult = a; } //Just on the off chance the 4 cells have the same value save processing cost
    else if(xPosition > 0 && yPosition > 0) { // normal case
      float x1Val = ((b - a) * xPosition) + a; //interpolates across top of square
      float x2Val = ((d - c) * xPosition) + c; //interpolates across bottom of square
      float y1Val = ((a - c) * yPosition) + c; //interpolates up left side of square
      float y2Val = ((b - d) * yPosition) + d; //interpolates up right side of square
      //equation works out the interpolated value of the 4 values above via correct percentage of weight
      tableResult = (((x1Val + x2Val) * xPosition) + ((y1Val + y2Val) * yPosition)) / ((xPosition + yPosition) * 2);
    }
    else { // clean up strays
        tableResult = (a + c + b + d) / 4;
      }
    value = tableResult;
    return static_cast<int>(value);
}

float Calibration::GetAccelRate()
{
    return _accelRate;
}

std::string Calibration::GetCalibrationPath()
{
    return _calibrationPath;
}

//Reads calibration data from file
void Calibration::LoadCalibration(){
    std::string line;
    std::string key;
    std::ifstream calibrationFile(_calibrationPath);
    
    if (calibrationFile.is_open()) {
        
        //Load TPS
        float f1, f2;
        std::getline(calibrationFile, line);
        std::istringstream linestream(line);
        linestream >> key >> f1 >> f2;
        _tps.Update(f1, f2);

        //Load number of trigger teeth per revolution
        int i1;
        std::getline(calibrationFile, line);
        linestream.str(line);
        linestream >> key >> i1;
        _teeth = i1;

        std::getline(calibrationFile, line);
        linestream.str(line);
        linestream >> key >> i1;
        _maxRpm = i1;

        std::getline(calibrationFile, line);
        linestream.str(line);
        linestream >> key >> f1;
        _accelRate = f1;

        //Load torque map
        int v[8];
        for (int y = 0; y < 8; y++){
            std::getline(calibrationFile, line);
            linestream.str(line);
            linestream >> v[0] >> v[1] >> v[2] >> v[3] >> v[4] >> v[5] >> v[6] >> v[7];
            for (int x = 0; x < 8; x++){
                _torqueMap[x][y] = v[x];
            }
        }

        calibrationFile.close();
    }
    else {
        throw std::runtime_error("Failed to open file at path : " + _calibrationPath);
    }
}