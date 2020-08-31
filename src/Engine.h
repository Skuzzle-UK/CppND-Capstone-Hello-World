#ifndef ENGINE_H_
#define ENGINE_H_

#include "Input.h"
#include "AnalogSensor.h"
#include "DigitalSensor.h"

class Engine
{
public:

private:
int _capicty; //Engine capacity in cc
int _torqueMap[10];
int _maxRpm;
};

#endif /* ENGINE_H_ */