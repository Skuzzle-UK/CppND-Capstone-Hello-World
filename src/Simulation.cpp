#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <chrono>
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
                _triggersPerSecond.emplace_back(triggersPerSecond);
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
    
    float timeToComplete = 0.0;
    //@TODO write code that iterates through each item of all data vectors
    //Drive vehicle through sim based on each item of data vectors
    //Check vehicle reaches end of course or rpm zero so fails
    //Record time between lines to create total time take for sim

    for(int i = 0; i < _triggersPerSecond.size(); i++) //read in some detail so far - loads to go, plus actual sim race physics
    {
        int rpm = calibration->GetRpm(_triggersPerSecond[i]);
        float tps = calibration->GetTps(_tpsVoltage[i]);
        _mutex.lock();
        std::cout << "Simulation " << _simulationPath << " calibration at memory location " << calibration << " " << " rpm : " << rpm << "\n";
        std::cout << "Simulation " << _simulationPath << " calibration at memory location " << calibration << " " << " tps : " << tps << "\n";
        _mutex.unlock();
    }
    return timeToComplete;
}