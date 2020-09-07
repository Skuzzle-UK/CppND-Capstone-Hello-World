#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include <string>
#include "AnalogSensor.h"

class Calibration
{
public:
    //Constructor / deconstructor
    Calibration(std::string);
    ~Calibration();

    //getters
    int GetRpm(int &);
    float GetTps(float &);
    float GetAccelRate();
    int GetTorque(int rpm, float tps);

private:
    
    void LoadCalibration();
    std::string _calibrationPath;
    int _torqueMap[8][8];
    int _maxRpm;
    int _teeth; //number of triggers per revolution of motor
    float _accelRate; //Rate of vehicle speed increase multiplier per loop
    AnalogSensor _tps;
};

#endif /* CALIBRATION_H_ */