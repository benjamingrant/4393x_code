#ifndef DISPLAY_
#define DISPLAY_

#include "main.h"
#include "globals.h"

//********************//
// CONTROLLER DISPLAY //
//********************//

void displayControllerMessage(std::string value);
void displayControllerMessage(double value);
void displayControllerMessage(int value);
void displayControllerMessage(unsigned long value);
void displayControllerError(std::string value);


#endif
