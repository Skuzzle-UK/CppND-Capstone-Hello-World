#include <iostream>
#include <string>
#include "Calibration.h"

int main() {
    std::string calibrationPath = "./datafiles/calibration1.clb";
    Calibration motor(calibrationPath);
}