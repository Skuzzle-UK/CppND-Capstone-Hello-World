#include <fstream>
#include <sstream>
#include <iostream>
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

void Simulation::LoadSimulation(){ //Read simulation data from file into vectors
    std::string line;
    std::string key;
    std::ifstream simulationFile(_simulationPath);
    
    if (simulationFile.is_open()) {
        while(key != "#START_SIM")
        {
            std::getline(simulationFile, line);
            std::istringstream linestream(line);
            linestream >> key;
        }
        std::cout << "Loading simulation" << _simulationPath << " ... \n";
        while (key != "#END_SIM")
        {
            int triggersPerSecond, torqueRequired;
            float tpsVoltage, distance;
            std::getline(simulationFile, line);
            std::istringstream linestream(line);
            linestream >> key >> triggersPerSecond >> tpsVoltage >> distance >> torqueRequired;
            if (key != "#END_SIM")
            {
                _triggersPerSecond.emplace_back(tpsVoltage);
                _tpsVoltage.emplace_back(tpsVoltage);
                _distance.emplace_back(distance);
                _torqueRequired.emplace_back(torqueRequired);
            }
        }
        std::cout << "Simulation " << _simulationPath << " loaded!" << "\n";
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