#include <fstream>
#include <sstream>
#include <regex>
#include "Simulation.h"

Simulation::Simulation(std::string simulationPath)
{
    _simulationPath = simulationPath;
    LoadSimulation();
}

Simulation::~Simulation()
{
  //Insert abny deconstruction code here  
}

void Simulation::LoadSimulation(){ //Read simulation data from file
    std::string line;
    std::string key;
    std::ifstream simulationFile(_simulationPath);
    
    if (simulationFile.is_open()) {
        //@TODO write code to add each line of sim file into various vectors for each variable as detailed in Simulation1.sim
        while(key != "#START_SIM")
        {
            std::getline(simulationFile, line);
            std::istringstream linestream(line);
            linestream >> key;
        }
        while (key != "#END_SIM")
        {
            std::getline(simulationFile, line);
            std::istringstream linestream(line);
            linestream >> _triggersPerSecond.emplace_back() >> _tpsVoltage.emplace_back() >> _distance.emplace_back() >> _torqueRequired.emplace_back();
        }
        simulationFile.close();
    }
    else {
        throw std::runtime_error("Failed to open file at path : " + _simulationPath);
    }
}

float Simulation::StartSimulation(std::shared_ptr<Calibration> calibration)
{
    float timeToComplete = 0;
    //@TODO write code that iterates through each line of code
    //Drive vehicle through sim base on each line of code
    //Check vehicle reaches end of course or rpm zero so fails
    //Record to between lines to create total time take for sim
    return timeToComplete;
}