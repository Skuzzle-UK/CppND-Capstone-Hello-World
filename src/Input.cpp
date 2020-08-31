#include "Input.h"
#include <string>

Input::Input(std::string friendlyName, int inputPin){
    _friendlyName = friendlyName;
    _inputPin = inputPin;
}
