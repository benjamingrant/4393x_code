#include "display_.h"
#include "globals.h"

void displayControllerText(std::string msg){
    //master.print(0, 0, NULL);
    master.print(0, 0, "Time: %d", pros::millis());
}
