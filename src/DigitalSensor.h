#ifndef DIGITALSENSOR_H_
#define DIGITALSENSOR_H_

class DigitalSensor
{
public:
//Constructor - Destructor
DigitalSensor();
~DigitalSensor();

enum digitalBoolean {LOW, HIGH}; //value of high or low;

//Getters
digitalBoolean Value(); //method to get current value

//Setters
void GoHigh();
void GoLow();

private:
digitalBoolean _currentValue;

};

#endif /* DIGITALSENSOR_H_ */