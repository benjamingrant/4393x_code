#ifndef REPLAY_H
#define REPLAY_H

#include "main.h"

//*********//
// Logging //
//*********//

// contains all of the motor movement voltages at a given pros::millis() timestamp
class ControlState{
private:
    std::uint32_t timeStamp;
    std::vector<int> motorVoltages;
public:
    ControlState(std::uint32_t timeStamp, std::vector<int> motorVoltages) : timeStamp{timeStamp}, motorVoltages{motorVoltages} {};
public:
    std::uint32_t getTimeStamp(){return timeStamp;};
    std::vector<int> getMotorVoltages(){return motorVoltages;};
    void writeToLogfile();
};

// writes to the current replay log file
ControlState getCurrentControlState();

// returns new log file created on the micro sd ("/usd/log-[logNumber].txt")
std::fstream generateLogFile();

//******************//
// Replay Execution //
//******************//

// returns log file address ("/usd/log-[logNumber].txt")
const char * getLogfilePath(int logNumber);

// set motors to a ControlState from selected log selected log file
void executeControlState(ControlState c);

// parse current execution logfile and execute ControlStates
void executeReplay(int logfileNumber);

#endif
