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

int Calibration::MaxRpm(){
    return _maxRpm;
}

void Calibration::LoadCalibration(){ //Read calibration data from file
    std::string line;
    std::string key;
    std::ifstream calibration(_calibrationPath);
    
    if (calibration.is_open()) {
        
        //Load TPS
        float f1, f2;
        std::getline(calibration, line);
        std::istringstream linestream1(line);
        linestream1 >> key >> f1 >> f2;
        AnalogSensor _tps(f1, f2);

        //Load number of trigger teeth per revolution
        int i1;
        std::getline(calibration, line);
        std::istringstream linestream2(line);
        linestream2 >> key >> i1;
        _teeth = i1;

        std::getline(calibration, line);
        std::istringstream linestream(line);
        linestream >> key >> i1;
        _maxRpm = i1;

        //Load torque map
        int v[8];
        for (int y = 0; y < 8; y++){
            std::getline(calibration, line);
            std::istringstream linestream3 (line);
            linestream3 >> v[0] >> v[1] >> v[2] >> v[3] >> v[4] >> v[5] >> v[6] >> v[7];
            for (int x = 0; x < 8; x++){
                _torqueMap[x][y] = v[x];
            }
        }

        calibration.close();
    }
    else {
        throw std::runtime_error("Failed to open file at path : " + _calibrationPath);
    }
}