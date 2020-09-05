#ifndef ANALOGSENSOR_H_
#define ANALOGSENSOR_H_

class AnalogSensor
{
public:
//Constructor - Destructor
AnalogSensor(float min, float max);
~AnalogSensor();

//Getters
float Value(float voltage); //method to get current value as a percentage

//Setters
void Update(float min, float max); //method to change value

private:
bool Sanity(float min, float max); //method to check for value sanity called by Update

float _min; //minimum voltage based on user calibration data
float _max; //maximum voltage based on user calibration data
};

#endif /* ANALOGSENSOR_H_ */