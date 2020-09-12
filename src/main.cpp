#include "Calibration.h"
#include "Simulation.h"
#include "Result.h"
#include "SortResults.h"
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
//#include <filesystem> On my own system this worked - Udacity environment it didnt
#include <experimental/filesystem>
#include <future>
#include <algorithm>

const std::string clearTerm = "\x1B[2J\x1B[H"; //used to clear the console/terminal for visual asthetics

//@TODO - Move this function to a seperate file later : USEFUL for the future (reusable code is good!)
//No intention to move before submission as documentation would need editing, but well worth keeping for the future
//Finds all files of a specified extension type within the specified path
std::vector<std::string> FindFilesOfType(std::string path, std::string ext)
{
    std::vector<std::string> files;
    for (auto &p : std::experimental::filesystem::recursive_directory_iterator(path))
    {
        if (p.path().extension() == ext)
        {
            files.emplace_back(p.path().stem().string());
        }
    }
    return files;
}



//Program begins here
int main() {
    //Default data file paths and extentions
    const std::string defaultCalibrationPath = "../datafiles";
    const std::string defaultCalibrationExt = ".map";
    const std::string defaultSimulationPath = "../datafiles";
    const std::string defaultSimulationExt = ".sim";

    std::string calibrationPath;
    std::string calibrationExt;
    std::string simulationPath;
    std::string simulationExt;

    //Get user input of file locations and types (of default if left blank)
    std::cout << clearTerm << "Enter path to calibration files (leave blank for default: ../datafiles) : ";
    std::getline(std::cin, calibrationPath);
    if (calibrationPath == "")
    {
        calibrationPath = defaultCalibrationPath;
    }

    std::cout << clearTerm << "Enter calibration files extension (leave blank for default: .map) : ";
    std::getline(std::cin, calibrationExt);
    if (calibrationExt == "")
    {
        calibrationExt = defaultCalibrationExt;
    }

    std::cout << clearTerm << "Enter path to simulation files (leave blank for default: ../datafiles) : ";
    std::getline(std::cin, simulationPath);
    if (simulationPath == "")
    {
        simulationPath = defaultSimulationPath;
    }

    std::cout << clearTerm << "Enter simulation files extension (leave blank for default: .sim) : ";
    std::getline(std::cin, simulationExt);
    if (simulationExt == "")
    {
        simulationExt = defaultSimulationExt;
    }

    std::cout << clearTerm;

    //Get all files of correct types
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

    std::cout << "\n" << "Starting Simulations:" << "\n";

    std::vector<Result> bestResults; //A place to store the fastest calibration through each simulation
    
    //The calibrations for each simulation start up in seperate threads to speed up data processing and to simulate an asyncronous race.
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

        bestResults.push_back(SingleBestResult(simResults));
    }
    
    std::cout << "\n" << "Winners:" << "\n";
    std::cout << "--------" << "\n";
    std::cout << "Simulation <--------------------> Calibration" << "\n";
    for (int i = 0; i < bestResults.size(); i++)
    {
        std::cout << bestResults[i].simFile << " : " << bestResults[i].calFile << "\n";
    }

    std::string theWinner = Winner(bestResults);

    std::cout << "\n" << "The calibration which performs the best in the majority of simulations is...    " << theWinner << "\n";
    std::cout << theWinner << "\n";

    return 0;
}