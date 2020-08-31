#include "AnalogSensor.h"
#include "Input.h"

AnalogSensor::AnalogSensor(float min, float max)
{
    _min = min;
    _max = max;
    _voltage = ((max - min) / 2) + min; // set start voltage to middle of range
}

float AnalogSensor::Voltage(){
    return _voltage;
}

void AnalogSensor::Update(float &newVoltage){
    if (Sanity){
        _voltage = newVoltage;
    }
}

bool AnalogSensor::Sanity(float &newVoltage){
    if (newVoltage >= _min || newVoltage <= _max){
        return true;
    }
    else return false;
}