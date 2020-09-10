#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <memory>
#include <vector>
#include <mutex>
#include "Calibration.h"
#include "Result.h"

class Simulation
{
public:
Simulation(std::string);

Result StartSimulation(std::shared_ptr<Calibration>);

private:
void LoadSimulation();
int DriveSector(float endDistance, float accelRate, int torqueProduced, int torqueRequired);


std::string _simulationPath;
std::vector<int> _triggersPerSecond;
std::vector<float> _tpsVoltage;
std::vector<float> _distance;
std::vector<int> _torqueRequired;
std::mutex _mutex;
float _Speed;
};

#endif /* SIMULATION_H_ */