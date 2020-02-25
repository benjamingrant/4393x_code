#ifndef GLOBALS
#define GLOBALS

#include "main.h"
#include "replay.h"

//******************//
// PORT DEFINITIONS //
//******************//

const int driveBLPort = 1;
const int driveBRPort = 2;
const int driveFLPort = 5;
const int driveFRPort = 19;
const int intakeLPort = 18;
const int intakeRPort = 20;
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
inline pros::Motor intakeL(intakeLPort, true);
inline pros::Motor intakeR(intakeRPort);
inline pros::Motor arm(armPort, true);
inline pros::Motor angler(anglerPort, true);

//************//
// AUTONOMOUS //
//************//

inline int autonomousPreSet = 0;
inline bool controlStateLogging = false;

//***********************//
// RUNNING autoFunctions //
//***********************//

inline bool autoStackRunning = false;

//****************//
// REPLAY Logging //
//****************//

inline uint32_t record_t0;
inline uint32_t record_t1;

inline std::fstream replay_log;
inline std::fstream exectutionLog;

#endif
