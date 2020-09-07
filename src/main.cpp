#include "Calibration.h"
#include "Simulation.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <filesystem>
#include <future>


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
    std::vector<std::shared_ptr<Calibration>> motors; //Shared pointer as needs to move in and out of functions easily
    std::vector<std::shared_ptr<Simulation>> sims; //Shared pointer as sim will run for all calibrations at the same time in seperate threads

    //Load each calibration and sim file into memory
    for(auto itr : calibrationFiles)
    {
        std::string path = calibrationPath + "/" + itr + calibrationExt;
        std::shared_ptr<Calibration> motor(new Calibration(path));
        motors.emplace_back(motor);
    }
    for(auto itr : simulationFiles)
    {
        std::string path = simulationPath + "/" + itr + simulationExt;
        std::shared_ptr<Simulation> sim(new Simulation(path));
        sims.emplace_back(sim);
    }

    //@TODO sort out simulation running - currently just loads sims into threads
    for(int i = 0; i < sims.size(); i++)
    {
        std::vector<std::future<int>> simthreads;
        std::vector<int> results;
        for(int j = 0; j < motors.size(); j++)
        {
            simthreads.emplace_back(std::async(&Simulation::StartSimulation, sims[i], motors[j]));
        }
        //*** @TODO re-establish this section if required later once threads start working
        /*for(int k = 0; k < motors.size(); k++)
        {
            results.push_back(simthreads[k].get()); //@TODO work out how to actually deal with results
        }
        Plus add pop_back to threads after the get (which waits for completion) is called.
        ****/
    }


    return 0;
}