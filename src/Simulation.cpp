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
    
}

void Simulation::LoadSimulation(){ //Read simulation data from file
    std::string line;
    std::string key;
    std::ifstream simulation(_simulationPath);
    
    if (simulation.is_open()) {
        
        simulation.close();
    }
    else {
        throw std::runtime_error("Failed to open file at path : " + _simulationPath);
    }
}