#include "autoFunctions.h"
#include "PID.h"
#include "main.h"
#include "globals.h"
#include "display_.h"
#include <sstream>
#include <cmath>

//*********************//
// autoStack PID Setup //
//*********************//

// constants
double p = 1;
double i = 1;
double d = 1;
double target = 4.2;
double targetError = 0.03;
// input function
double getAnglerPosition(){
    return angler.get_position();
}
// output function
void setAnglerMovement(double v){
    int _v = static_cast<int> (v);
    angler.move(_v);
}
// time function
unsigned long getV5Time(){
    unsigned long time = static_cast<unsigned long> (pros::millis());
    std::stringstream ss;
    ss << time;
    displayControllerText(ss.str());
    return time;
}

//****************************************//
// autoStack Function (Run in a New Task) //
//****************************************//

void autoStack(){
    // PID loop to control the angler motor (bring tray to 90º)
    PIDController<double> anglerPID(p, i, d, getAnglerPosition, setAnglerMovement);
    // setup
    anglerPID.setEnabled(true);
    anglerPID.registerTimeFunction(getV5Time);
    anglerPID.setTarget(target);
    anglerPID.setOutputBounds(-117.0, 117.0);

    // debug
    displayControllerText(anglerPID.getError());

    // PID loop
    while(std::abs(anglerPID.getError()) >= targetError){
        anglerPID.tick(); // this is what actually does the PID controlling
        pros::delay(100);              // delay 100ms so the smartbrain can think
    }

    autoStackRunning = false;
    master.rumble("--");
}
