#include "autoFunctions.h"
#include "PID.h"
#include "main.h"
#include "globals.h"
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
// input  function
double getAnglerPosition(){
    return angler.get_position();
}
// output function
void setAnglerMovement(double v){
    angler.move(v);
}
// time function
unsigned long getV5Time(){
    return static_cast<unsigned long> (pros::millis());
}

//****************************************//
// autoStack Function (Run in a New Task) //
//****************************************//

void autoStack(){
    PIDController<double> anglerPID(p, i, d, getAnglerPosition, setAnglerMovement);
    anglerPID.registerTimeFunction(getV5Time);
    anglerPID.setTarget(target);
    // set output bounds
    anglerPID.setInputBounded(true);
    anglerPID.setOutputBounds(-117, 117);

    while(fabs(anglerPID.getError()) > 0.03){
        anglerPID.tick(); // this is what actually does the PID controlling
        pros::delay(20);               // delay 20ms so the smartbrain can think
    }

    autoStackRunning = false;
    master.rumble("...");
}
