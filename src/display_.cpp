#include "main.h"
#include "display_.h"
#include "globals.h"

void displayControllerText(std::string msg){
    master.clear();
    master.print(0, 0, "M: %d", msg);
}

void displayControllerText(double data){
    master.clear();
    master.print(0, 0, "%M: %d", std::to_string(data));
}

void displayControllerText(int data){
    master.clear();
    master.print(0, 0, "%M: %d", std::to_string(data));
}

void displayControllerText(unsigned long data){
    master.clear();
    master.print(0, 0, "%M: %d", std::to_string(data));
}

void displayControllerError(std::string msg){
    master.clear();
    master.print(0, 0, "E: %d", msg);
}
