#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Calibration.h"

//Lets make a sim whereby 3 or 4 calibration files are loaded in.
//These are then each fed through 10 or so simulations.
//start a thread for each calibration  when it runs through a sim.
//Program run order:
//Sim 1 - calib 1 >> calib 2 >> calib 3 (3 threads - wait until they all end)
//Display to term finish time for each calibration with best highlighted.
//Sim 2 - calib 1 >> calib 2 >> calib 3 (3 threads - wait until they all end)
//etc
//loop
//Finally pick overall best calibration

int main() {
    std::string calibrationPath = "./datafiles/Calibration.map";
    std::unique_ptr<Calibration> motor(new Calibration(calibrationPath));

    //@TODO write simulation class and load simulation data file(s)
    //Start simulation as an object (maybe several simulations on seperate threads)
    //Use rule of 5 to copy calibration data into sim as shared pointer perhaps.
    //Have already created Calibration motor as shared_ptr so part way there but also make a vector of calibrations.

    //Scrap voltage in analog sensor - Add min and max real figures i.e. 0-100%.
    //Add method to calc and return real human readable figure i.e. previously said percentage.
    //Dont store current value (just use sim to lookup current value from min and max calc)
    //so that it can be used during interpolation

}