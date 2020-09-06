# EV Simulation
Created from a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

## Udacity Blurb
The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.
In this project, you can build your own C++ application starting with this repo, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## My take on the Captone Project
I decided this project should be to create something that I am working with on a daily basis, yet to expand on what I do daily.
For this to be the case I have listed a few key focus points:
* Automotive based
* Cutting edge modern and future tech
* Vehicle modification
* ECU calibration
* Tuning

## Description of EV Simulation
EV Simulation is a combination of my daily work, mixed with the future of my industry. As an automotive diagnostic director and well established vehicle tuner I have taken note that the automotive industry is moving away from internal combustion and towards electified vehicles and hybrids.
Being a field in which I have a huge amount of profound knowledge it seemed like a good choice for the Capstone Project.
This project creates a massively simplified electric vehicle motor through the creation of an object of type Calibration (calibration meaning specification of motor operating parameters and sensor calibration).
It then drives this electric motor through a simple simulated course and reports the time from start to finish.

It does this not once, but with several different motor calibrations all being driven through several different simulated scenarios to find the best motor calibration overall under several usage conditions.

## Order of execution
1. Vector of motors is created and loaded with calibration files of type .map found within folder ./datafiles.
2. Vector of simulations is created and loaded with simulation files of type .sim found within folder ./datafiles.
3. Simulation 1 shared_ptr. Simulation 1 method started as thread for each motor calibration (motor passed in as unique_ptr).
4. Wait for simulation 1 to end then write results to terminal for each calibration on 1 line (putting a * infront of the best result).
5. Best calibration for this sim stored in vector.
6. Next simulation starts (loop through all sims displaying result on terminal and storing best in vector).
7. Count number of wins by each calibration.
8. Write to terminal best overall calibration based on which came out top of the most simulations.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./EVSim`

## Source Files - Found within src folder
* main.cpp - `main method. Loads calibrations and simulations. Organises results to display them to terminal`
* AnalogSensor.cpp - `Creates analog sensor object. Can be a voltage between specified min and max. Specifically used for throttle position in this sim`
* DigitalSensor.cpp - `Creates digital sensor object. Can be set to HIGH or LOW. Using for crank position sensor`
* Calibration.cpp - `To build a sim motor. Calibration relies on the sensor.cpp's to create an object that resembles an electric vehicle motor with tps, ckp and "3D" torque map`
* Simulation.cpp - `Creates a simulation environment. Loads sim data and contains methods to run simulation. Returns time vehicle would have taken to complete course`

## Data Files - Found within datafiles folder
* Pay attention to how the data files are created as they are read line by line. The `Key` of each line can be named anything, but suggest name remains the same for continuity and easy visual representation of data that follows.
* Data in files is blank space seperated. For example TPS 0.4 4.7 is ready by the code as variables KEY >> Min >> Max.
* If in doubt don't modify these data files as no checking is done for correct data on each line.
* Don't introduce extra lines including blank space lines into these files.