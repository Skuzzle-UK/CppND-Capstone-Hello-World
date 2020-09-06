#ifndef SIMULATION_H_
#define SIMULATION_H_


class Simulation
{
public:
Simulation(std::string);
~Simulation();

private:
void LoadSimulation();

std::string _simulationPath;
};

#endif /* SIMULATION_H_ */