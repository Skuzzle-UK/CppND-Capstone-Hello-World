#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(){
    _currentValue = LOW;
}

DigitalSensor::digitalBool DigitalSensor::Value(){
    return _currentValue;
}

void DigitalSensor::GoHigh(){
    _currentValue = HIGH;
}

void DigitalSensor::GoLow(){
    _currentValue = LOW;
}