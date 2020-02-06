#include "replay.h"
#include "globals.h"

void ControlState::log(){
    // --------------------------------------
    // place file writing (fstream) code here
    // --------------------------------------
}

void logCurrentControlState(){
    // make vector of motor voltages
    std::vector<pros::Motor> motors{driveBL, driveBR, driveFL, driveFR, intakeL, intakeR, arm, angler};
    std::vector<int> motorVoltages;
    for(int i = 0; i < motors.size(); i++){
        motorVoltages.push_back(motors[i].get_voltage());
    }

    // create current control state
    ControlState c{pros::millis(), motorVoltages};

    c.log();
}
