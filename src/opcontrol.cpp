#include "main.h"
#include "globals.h"
#include "autoFunctions.h"
#include "replay.h"
#include "display_.h"

using namespace pros;
using namespace std;

 //******************//
 // OPERATOR CONTROL //
 //******************//

int quadraticAnalogScale(int stickValue){
    return (stickValue * abs(stickValue)) / 117;
}

int cubicAnalogScale(int stickValue){
    return (stickValue^3) / (117^2);
}

void opcontrol() {
	while (true) {
        // control drivetrain motors from master
        int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);
        int scaledLeft = quadraticAnalogScale(left);    // STICK SCALING (quadratic)
        int scaledRight = quadraticAnalogScale(right);
        // int scaledLeft = cubicAnalogScale(left);    // STICK SCALING (quadratic)
        // int scaledRight = cubicAnalogScale(right);
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

        // vibration test button mapping
        if(master.get_digital(DIGITAL_Y)){
            pros::delay(500);
            displayControllerMessage("test");
            //master.rumble("...");
        }

        // autoStack button mapping
        if(master.get_digital(DIGITAL_DOWN) && !autoStackRunning){
            pros::delay(500);  // delay to eliminate double press
            autoStackRunning = true;
            pros::Task stack(autoStack);
            // stack.get_state();
            setAnglerMovement(50);
            pros::delay(500);
            setAnglerMovement(0);
        }

//*****************************//
// REPLAY (autonomous) LOGGING //
//*****************************//

        // controlStateLogging toggle button mapping
        if(master.get_digital(DIGITAL_X)){
            pros::delay(500); // delay to eliminate double press
            if(!pros::usd::is_installed()){
                displayControllerError("No micro SD inserted!");
            } else {
                if(!controlStateLogging){
                    replay_log = selectLogFile();
                    controlStateLogging = true;
                    displayControllerMessage("Recording started :-)");
                } else {
                    replay_log.close();
                    controlStateLogging = false;
                    displayControllerMessage("Recording ended.");
                }
            }
        }

        // log current ControlState if controlStateLogging is toggled
        if(controlStateLogging){
            logCurrentControlState();
        }

        // wait 20 ms
		pros::delay(20);
	}
}
