#include "AnalogSensor.h"
#include <regex>

AnalogSensor::AnalogSensor()
{
    AnalogSensor::Update(0.0, 5.0);
}

float AnalogSensor::Value(float voltage)
{
    float value = 0;
    float inc;
    inc = (_max - _min) / 100;
    value = (voltage - _min) / inc;
    return value;
}

bool AnalogSensor::Sanity(float min, float max){
    if (min < max)
    {
        return true;
    }
    else
    {
        return false;
    }
}

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
