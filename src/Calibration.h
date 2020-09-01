#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include <string>
#include "AnalogSensor.h"
#include "DigitalSensor.h"

class Calibration
{
public:
Calibration(std::string);
~Calibration();

private:
void LoadCalibration();

std::string _calibrationPath;
int _torqueMap[8][8];
int _maxRpm;
AnalogSensor _tps(float, float);
DigitalSensor _ckp();
};

#endif /* CALIBRATION_H_ */