#include "display_.h"

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

void displayControllerMessage(std::string value){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatDataForController("M: ", value));
}
void displayControllerMessage(double value){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatDataForController("M: ", value));
}
void displayControllerMessage(int value){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatDataForController("M: ", value));
}
void displayControllerMessage(unsigned long value){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatDataForController("M: ", value));
}
void displayControllerError(std::string value){
    master.clear();
    pros::delay(60);
    master.print(0, 0, formatDataForController("E: ", value));
}

void controllerCountdown(int seconds){
    master.clear();
    for(int i = seconds; i > 0; i--){
        master.rumble(".");
        pros::delay(100);
        displayControllerMessage(i);
        pros::delay(900);
    }
    master.clear();
}
