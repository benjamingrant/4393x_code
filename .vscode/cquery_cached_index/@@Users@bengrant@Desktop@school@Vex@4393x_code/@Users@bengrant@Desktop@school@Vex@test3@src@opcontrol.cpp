#include "main.h"
#include "globals.h"
#include "autoFunctions.h"
#include <cmath>
#include <sstream>

using namespace pros;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

int quadraticAnalogScale(int stickValue){
    return (stickValue * abs(stickValue)) / 117;
}

void opcontrol() {
	while (true) {
        // control drivetrain motors from master
        int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);
        int scaledLeft = quadraticAnalogScale(left);    // STICK SCALING (quadratic)
        int scaledRight = quadraticAnalogScale(right);
        driveBL = scaledLeft;
        driveFL = scaledLeft;
        driveBR = scaledRight;
        driveFR = scaledRight;

        // control arm motor from master
        if(master.get_digital(DIGITAL_R1)){
            arm = 127;
        } else if(master.get_digital(DIGITAL_R2)){
            arm = -127;
        } else {
            arm = 0;
        }

        // control angler motor from master
        if(master.get_digital(DIGITAL_LEFT)){
            angler = -127;
        } else if(master.get_digital(DIGITAL_RIGHT)){
            angler = 127;
        } else {
            angler = 0;
        }

        //control intake motors from master
        if(master.get_digital(DIGITAL_L1)){
            intakeL = 127;
            intakeR = 127;
        } else if(master.get_digital(DIGITAL_L2)){
            intakeL = -127/2;
            intakeR = -127/2;
        } else {
            intakeL = 0;
            intakeR = 0;
        }

        // vibration testing
        if(master.get_digital(DIGITAL_A)){
            master.rumble("...");
        }

        //run autoFunctions in new tasks
        if(master.get_digital(DIGITAL_DOWN) && !autoStackRunning){
            autoStackRunning = true;
            pros::Task my_task(autoStack);
        }

        // wait 20 ms
		pros::delay(20);
	}
}
