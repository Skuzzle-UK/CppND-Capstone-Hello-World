#include "Calibration.h"
#include "Simulation.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <filesystem>


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

//@TODO - Move this function to a seperate file : USEFUL for the future (reusable code is good)
std::vector<std::string> FindFilesOfType(std::string path, std::string ext)
{
    std::vector<std::string> files;
    for (auto &p : std::filesystem::recursive_directory_iterator(path))
    {
        if (p.path().extension() == ext)
        {
            files.emplace_back(p.path().stem().string());
        }
    }
    return files;
}

int main() {
    //set data file paths and extentions
    std::string calibrationPath = "../datafiles";
    std::string calibrationExt = ".map";
    std::string simulationPath = "../datafiles";
    std::string simulationExt = ".sim";

    //Get files of all correct types
    std::vector<std::string> calibrationFiles = FindFilesOfType(calibrationPath, calibrationExt);
    std::vector<std::string> simulationFiles = FindFilesOfType(simulationPath, simulationExt);

    //Create container vectors for calibrations and sims
    std::vector<std::unique_ptr<Calibration>> motors; //Unique pointer as only using once at a time
    std::vector<std::shared_ptr<Simulation>> sims; //Shared pointer as sim will run for all calibrations at the same time in seperate threads

    //Load each calibration and sim file into memory
    for(auto itr : calibrationFiles)
    {
        std::string path = calibrationPath + "/" + itr + calibrationExt;
        std::unique_ptr<Calibration> motor(new Calibration(path));
        motors.emplace_back(std::move(motor));
    }
    for(auto itr : simulationFiles)
    {
        std::string path = simulationPath + "/" + itr + simulationExt;
        std::shared_ptr<Simulation> sim(new Simulation(path));
        sims.emplace_back(sim);
    }

    //*** REMOVE WHEN HAPPY
    for(int i = 0; i < 2; i++) //Test motors has successfully loaded with calibrations
    {
        std::cout << motors[i]->MaxRpm() << "\n"; //Display max RPM of each motor (could have chosen any data for test)
    }
    // *** End here


    //@TODO write simulation class and load simulation data file(s)
    //Start simulation as an object (maybe several simulations on seperate threads)
    //Use rule of 5 to copy calibration data into sim as shared pointer perhaps.
    //Have already created Calibration motor as shared_ptr so part way there but also make a vector of calibrations.

    //Scrap voltage in analog sensor - Add min and max real figures i.e. 0-100%.
    //Add method to calc and return real human readable figure i.e. previously said percentage.
    //Dont store current value (just use sim to lookup current value from min and max calc)
    //so that it can be used during interpolation
    return 0;
}
