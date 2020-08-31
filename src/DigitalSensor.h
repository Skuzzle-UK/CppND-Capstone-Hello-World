#ifndef DIGITALSENSOR_H_
#define DIGITALSENSOR_H_

#include "Input.h"

class DigitalSensor : public Input
{
public:
//Constructor - Destructor
DigitalSensor();
~DigitalSensor();

enum digitalBool {LOW, HIGH}; //value of high or low;

//Getters
digitalBool Value(); //method to get current value

//Setters
void GoHigh();
void GoLow();

private:
digitalBool _currentValue;

};

#endif /* DIGITALSENSOR_H_ */