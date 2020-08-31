#ifndef INPUT_H_
#define INPUT_H_
#include <string>

class Input
{
public:
//Constructor - Destructor
Input(std::string, int);
~Input();

//Getters

//Setters

private:
int _inputPin;
std::string _friendlyName;
};

#endif /* INPUT_H_ */