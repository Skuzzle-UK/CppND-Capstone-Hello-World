#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <memory>
#include <vector>
#include "Calibration.h"

class Simulation
{
public:
Simulation(std::string);
~Simulation(); //must return calibrations back to main.cpp unless does this automatically

private:
void LoadSimulation();
float StartSimulation(std::shared_ptr<Calibration>);

std::string _simulationPath;
std::vector<int> _triggersPerSecond;
std::vector<float> _tpsVoltage;
std::vector<float> _distance;
std::vector<int> _torqueRequired;
};

#endif /* SIMULATION_H_ */