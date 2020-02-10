#ifndef DISPLAY_
#define DISPLAY_

#include "main.h"

// template <class T>
// void displayControllerText(T data);
void displayControllerText(std::string msg);
void displayControllerText(double value);
void displayControllerText(int value);
void displayControllerText(unsigned long value);
void displayControllerError(std::string msg);


#endif
