#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include "Calibration.h"

Calibration::Calibration(std::string calibrationPath)
{
    _calibrationPath = calibrationPath;
    LoadCalibration();
}

Calibration::~Calibration()
{
    //Insert decontruction code here
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

void Calibration::LoadCalibration(){ //Read calibration data from file
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