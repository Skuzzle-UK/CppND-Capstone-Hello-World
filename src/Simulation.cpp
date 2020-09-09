#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <chrono>
#include <thread>
#include "Simulation.h"
#include "Result.h"

Simulation::Simulation(std::string simulationPath)
{
    _Speed = 0.0;
    _simulationPath = simulationPath;
    LoadSimulation();
}

Simulation::~Simulation()
{
  //Insert any deconstruction code here
}

//Reads simulation data from file into vectors
void Simulation::LoadSimulation(){
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

Result Simulation::StartSimulation(std::shared_ptr<Calibration> calibration)
{
    Result thisResult;
    thisResult.calFile = calibration->GetCalibrationPath();
    thisResult.simFile = _simulationPath;
    for(int i = 0; i < _triggersPerSecond.size(); i++)
    {
        if(_Speed != -1) //check it hasn't failed test
        {
            int torqueProduced = calibration->GetTorque(calibration->GetRpm(_triggersPerSecond[i]), calibration->GetTps(_tpsVoltage[i]));
            thisResult.time += DriveSector(_distance[i], calibration->GetAccelRate(), torqueProduced, _torqueRequired[i]);

            _mutex.lock();
            std::cout << "Simulation " << thisResult.simFile << " calibration " << thisResult.calFile << " " << " rpm : " << calibration->GetRpm(_triggersPerSecond[i]) << " rpm\n";
            std::cout << "Simulation " << thisResult.simFile << " calibration " << thisResult.calFile << " " << " tps : " << calibration->GetTps(_tpsVoltage[i]) << " %\n";
            std::cout << "Simulation " << thisResult.simFile << " calibration " << thisResult.calFile << " " << "Interpolated torque value : " << torqueProduced << "\n";
            _mutex.unlock();
        }
    }
    if(_Speed != -1)
    {
        return thisResult;
    }
    else
    {
        thisResult.time = 0;
        return thisResult; //failure value
    }
    
}

int Simulation::DriveSector(float endDistance, float accelRate, int torqueProduced, int torqueRequired)
{
    int time = 0;
    float speed = _Speed;
    float distance = 0.0;
    while (distance < endDistance)
    {
        int effort = torqueProduced - torqueRequired;
        float accel = effort * (accelRate / 1000);
        speed += accel;
        distance += speed;
        time += 1; //Just a sensibly chosen value for sim time constant
        //@REMOVE COMMENTS BELOW to add realism to simulation add comments to speed up processing
        //std::this_thread::sleep_for(std::chrono::milliseconds(1)); //Change value to change speed of simulation
        if (speed <= 0)
        {
            break;
        }
    }
    if(speed > 0)
    {
        _Speed = speed;
        return time;
    }
    else
    {
        _Speed = -1; //value for checkfailed;
        return 0;
    } 
}