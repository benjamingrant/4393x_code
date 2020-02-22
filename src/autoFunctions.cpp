#include "autoFunctions.h"
#include "PID.h"
#include "main.h"
#include "globals.h"
#include "display_.h"

//*********************//
// autoStack PID Setup //
//*********************//

// constants
double p = 0.4;
double i = 0.5;
double d = 1;
double target = 4.2 /*rotations*/;
double targetError = 0.03 /*rotations*/;
// input function
double getAnglerPosition(){
    return angler.get_position();
}
// output function
void setAnglerMovement(double v){
    std::int32_t _v = static_cast<int32_t> (v);
    angler.move(_v);
}
// time function
unsigned long getV5Time(){
    unsigned long time = static_cast<unsigned long> (pros::millis());

    // <debug>
    // std::stringstream ss;
    // ss << time;
    // displayControllerMessage(ss.str());
    // </debug>

    return time;
}

//**********************************************************//
// autoStack PID (not working) Function (Run in a New Task) //
//**********************************************************//

void autoStack(){
    angler.move(127);
    pros::delay(1200);
    angler.move(25);
    pros::delay(1200);
    angler.move(0);
}

// void autoStack(){
//     // PID loop to control the angler motor (i. e. bring the tray to 90º)
//     PIDController<double> anglerPID(p, i, d, getAnglerPosition, setAnglerMovement);
//     // setup
//     anglerPID.setEnabled(true);
//     anglerPID.setFeedbackWrapped(false);
//     anglerPID.registerTimeFunction(getV5Time);
//     anglerPID.setTarget(target);
//     anglerPID.setOutputBounds(-117.0, 117.0);
//     anglerPID.setInputBounds(0, 4.5);
//
//     // <debug>
//     std::stringstream ss;
//     ss << getAnglerPosition() << " : " << anglerPID.getError();
//     displayControllerMessage(ss.str());
//     // pros::delay(1000);
//     // displayControllerMessage(getAnglerPosition(), 2);
//     // </debug>
//
//     // PID loop
//     while(std::abs(anglerPID.getError()) >= targetError){
//         // iterate the PID controller
//         anglerPID.tick();
//         pros::delay(50);
//     }
//
//     autoStackRunning = false;
//     master.rumble(".-.");
// }
