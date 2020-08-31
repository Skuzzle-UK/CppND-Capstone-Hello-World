#ifndef ANALOGSENSOR_H_
#define ANALOGSENSOR_H_

#include "Input.h"

class AnalogSensor : public Input
{
public:
//Constructor - Destructor
AnalogSensor(float min, float max);
~AnalogSensor();

//Getters
float Voltage(){}; //method to get current value

//Setters
void Update(float &newVoltage){}; //method to change value

private:
bool Sanity(float &newVoltage){}; //method to check for value sanity called by Update

float _voltage; //value between min - max volts sanity checked through sanity method
float _min; //minimum voltage based on user calibration data
float _max; //maximum voltage based on user calibration data
};

#endif /* ANALOGSENSOR_H_ */