#include "AnalogSensor.h"
#include <regex>

AnalogSensor::AnalogSensor() : _min{0}, _max{5}
{
}

//Returns a percentage value between min and max voltage
float AnalogSensor::Value(float voltage)
{
    float value = 0;
    float inc;
    inc = (_max - _min) / 100;
    value = (voltage - _min) / inc;
    if (value <= 0){
        value = 0;
    }
    if (value >= 100){
        value = 100;
    }
    return value;
}

//Sanity check that min and max are is sensible
bool AnalogSensor::Sanity(float min, float max){
    if (min < max && min >= 0 && max <= 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Method to fill _min and _max values
void AnalogSensor::Update(float min, float max)
{
    if (Sanity(min, max))
    {
        _min = min;
        _max = max;
    }
    else{
        throw std::runtime_error("Minimum value must be less than maximum");
    }
}
