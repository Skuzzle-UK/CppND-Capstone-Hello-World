#include "Calibration.h"
#include "Simulation.h"
#include "Result.h"
#include "SortResults.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <filesystem>
#include <future>
#include <algorithm>


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

    std::vector<Result> bestResults;
    for(int i = 0; i < sims.size(); i++)
    {
        std::vector<std::future<Result>> simThreads;
        std::vector<Result> simResults;
        for(int j = 0; j < motors.size(); j++)
        {
            simThreads.emplace_back(std::async(std::launch::async, &Simulation::StartSimulation, sims[i], motors[j]));
        }
        for(int k = 0; k < motors.size(); k++)
        {
            simResults.push_back(simThreads[k].get());
        }
        bestResults.push_back(BestResult(simResults)); //try to make std::unique_ptr later as it can be destroyed when BestResult() goes out of scope
    }
        //@TODO count through allResults vector to find the calibration with the most wins.

        //@TODO output to term the results in a visually appealing way.

    return 0;
}