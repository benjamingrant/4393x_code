#include "display_.h"
#include "globals.h"
#include <string>

void displayControllerText(std::string msg){
    master.print(0, 0, "%d", msg);
}

void displayControllerText(double data){
    master.print(0, 0, "%d", std::to_string(data));
}

void displayControllerText(int data){
    master.print(0, 0, "%d", std::to_string(data));
}

void displayControllerText(unsigned long data){
    master.print(0, 0, "%d", std::to_string(data));
}
