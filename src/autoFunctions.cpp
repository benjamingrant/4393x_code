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
double target = 4.2;
double targetError = 0.03;
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
    std::stringstream ss;
    ss << time;
    displayControllerMessage(ss.str());
    // </debug>

    return time;
}

//****************************************//
// autoStack Function (Run in a New Task) //
//****************************************//

void autoStack(){
    // PID loop to control the angler motor (i. e. bring the tray to 90º)
    PIDController<double> anglerPID(p, i, d, getAnglerPosition, setAnglerMovement);
    // setup
    anglerPID.setEnabled(true);
    anglerPID.registerTimeFunction(getV5Time);
    anglerPID.setTarget(target);
    anglerPID.setOutputBounds(-117.0, 117.0);

    // <debug>
    displayControllerMessage(anglerPID.getError());
    // </debug>

    // PID loop
    while(std::abs(anglerPID.getError()) >= targetError){
        anglerPID.tick(); // this is what actually does the PID controlling
        pros::delay(100);              // delay 100ms so the smartbrain can think
    }

    autoStackRunning = false;
    master.rumble("--");
}
