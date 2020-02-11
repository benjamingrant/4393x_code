#ifndef DISPLAY_
#define DISPLAY_

#include "main.h"
#include "globals.h"

//********************//
// CONTROLLER DISPLAY //
//********************//
const char* formatDataForController(std::string prefix, std::string str){
    std::stringstream ss;
    ss << str;
    std::string _str = ss.str();
    _str.insert(0, prefix);
    return _str.c_str();
}
const char* formatDataForController(std::string prefix, double value){
    std::stringstream ss;
    ss << value;
    std::string _value = ss.str();
    _value.insert(0, prefix);
    return _value.c_str();
}
const char* formatDataForController(std::string prefix, int value){
    std::stringstream ss;
    ss << value;
    std::string _value = ss.str();
    _value.insert(0, prefix);
    return _value.c_str();
}
const char* formatDataForController(std::string prefix, unsigned long value){
    std::stringstream ss;
    ss << value;
    std::string _value = ss.str();
    _value.insert(0, prefix);
    return _value.c_str();
}

void displayControllerMessage(std::string value, int line = 0){
    master.clear();
    pros::delay(60);
    master.print(line, 0, formatDataForController("M: ", value));
}
void displayControllerMessage(double value, int line = 0){
    master.clear();
    pros::delay(60);
    master.print(line, 0, formatDataForController("M: ", value));
}
void displayControllerMessage(int value, int line = 0){
    master.clear();
    pros::delay(60);
    master.print(line, 0, formatDataForController("M: ", value));
}
void displayControllerMessage(unsigned long value, int line = 0){
    master.clear();
    pros::delay(60);
    master.print(line, 0, formatDataForController("M: ", value));
}
void displayControllerError(std::string value, int line = 0){
    master.clear();
    pros::delay(60);
    master.print(line, 0, formatDataForController("E: ", value));
}


#endif
