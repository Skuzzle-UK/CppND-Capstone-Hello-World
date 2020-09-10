#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <chrono>
#include <thread>
#include "Simulation.h"
#include "Result.h"

Simulation::Simulation(std::string simulationPath) : _Speed{0.0}, _simulationPath{simulationPath}
{
    LoadSimulation(); //Loads the simulation data file on construction
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


//Method that runs the simulation
Result Simulation::StartSimulation(std::shared_ptr<Calibration> calibration)
{
    Result thisResult;
    thisResult.calFile = calibration->GetCalibrationPath();
    thisResult.simFile = _simulationPath;
    for(int i = 0; i < _triggersPerSecond.size(); i++)
    {
        if(_Speed != -1) //check calibration hasn't already failed test
        {
            int torqueProduced = calibration->GetTorque(calibration->GetRpm(_triggersPerSecond[i]), calibration->GetTps(_tpsVoltage[i]));
            thisResult.time += DriveSector(_distance[i], calibration->GetAccelRate(), torqueProduced, _torqueRequired[i]);
        }
    }

    if(_Speed != -1) //Calibration passed test
    {
        _mutex.lock();
        std::cout << "Simulation " << thisResult.simFile << " calibration " << thisResult.calFile << " " << " took : " << thisResult.time << "\n";
        _mutex.unlock();
        return thisResult;
    }
    else //Calibration failed test
    {
        thisResult.time = 0;
        _mutex.lock();
        std::cout << "Simulation " << thisResult.simFile << " calibration " << thisResult.calFile << " " << " FAILED! " << "\n";
        _mutex.unlock();
        return thisResult;
    }
}


//Method tests that the vehicle can complete the sector and returns the time taken (time as arbitrary value from simTime constant).
int Simulation::DriveSector(float endDistance, float accelRate, int torqueProduced, int torqueRequired)
{
    const int simTime = 1; //Just a sensibly chosen value for sim time constant - could represent 1 second, 1 minute etc
    int time = 0;
    float speed = _Speed;
    float distance = 0.0;
    while (distance < endDistance)
    {
        int effort = torqueProduced - torqueRequired;
        float accel = effort * (accelRate / 1000);
        speed += accel;
        distance += speed;
        time += simTime;
        std::this_thread::sleep_for(std::chrono::milliseconds(2)); //Change value to change speed of simulation
        if (speed <= 0)
        {
            break;
        }
    }

    //Check if sector failed because vehicle speed reduced to a complete stop or started rolling backwards (negative values)
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