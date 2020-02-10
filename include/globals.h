#ifndef GLOBALS
#define GLOBALS

#include "main.h"
#include "replay.h"

//******************//
// PORT DEFINITIONS //
//******************//

const int driveBLPort = 1;
const int driveBRPort = 2;
const int driveFLPort = 9;
const int driveFRPort = 10;
const int intakeLPort = 16;
const int intakeRPort = 7;
const int armPort = 15;
const int anglerPort = 8;

//***********************//
// CONTROLLER DEFINITION //
//***********************//

inline pros::Controller master(pros::E_CONTROLLER_MASTER);

//*******************//
// MOTOR DEFINITIONS //
//*******************//

inline pros::Motor driveBL(driveBLPort);
inline pros::Motor driveBR(driveBRPort, true);
inline pros::Motor driveFL(driveFLPort);
inline pros::Motor driveFR(driveFRPort, true);
inline pros::Motor intakeL(intakeLPort);
inline pros::Motor intakeR(intakeRPort, true);
inline pros::Motor arm(armPort, true);
inline pros::Motor angler(anglerPort);

//************//
// AUTONOMOUS //
//************//

inline int autonomousPreSet = 0;
inline bool controlStateLogging = false;
inline std::fstream replay_log;

//**********************//
// RUNNING autoFunctions //
//**********************//

inline bool autoStackRunning = false;

#endif
