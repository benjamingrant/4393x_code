#include "main.h"
#include "display_.h"
#include "globals.h"

const char* formatStringForController(std::string prefix, std::string msg){
    msg.insert(0, prefix);
    const char *retVal = msg.c_str();
    return retVal;
}

void displayControllerText(std::string msg){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatStringForController("M: ", msg));
}

void displayControllerText(double value){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatStringForController("M: ", std::to_string(value)));
}

void displayControllerText(int value){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatStringForController("M: ", std::to_string(value)));
}

void displayControllerText(unsigned long value){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatStringForController("M: ", std::to_string(value)));
}

void displayControllerError(std::string msg){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatStringForController("E: ", msg));
}
