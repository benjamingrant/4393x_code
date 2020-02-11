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

    ControlState() : timeStamp{0} {
        std::vector<int> zeros{0,0,0,0,0,0,0,0};
        motorVoltages = zeros;
    };
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

// returns opened log file ("/usd/log-[logNumber].txt")
std::ifstream getLogfile(int logNumber);

// set motors to a ControlState from selected log selected log file
void executeControlState(ControlState c);

// parse selected log file and execute ControlStates
void executeLogfile(std::ifstream logfile);

#endif
