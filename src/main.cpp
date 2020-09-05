#include <iostream>
#include <string>
#include "Calibration.h"

int main() {
    std::string calibrationPath = "./datafiles/Calibration.map";
    Calibration motor(calibrationPath);

    //@TODO write simulation class and load simulation data file(s)
    //Start simulation as an object (maybe several simulations on seperate threads)
    //Use rule of 5 to copy calibration data into sim as shared pointer perhaps.

    //Scrap voltage in analog sensor - Add min and max real figures i.e. 0-100%.
    //Add method to calc and return real human readable figure i.e. previously said percentage.
    //Dont store current value (just use sim to lookup current value from min and max calc)
    //so that it can be used during interpolation

}