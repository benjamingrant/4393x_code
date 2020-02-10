#ifndef REPLAY_H
#define REPLAY_H

#include "main.h"

// contains all of the motor movement voltages at a given pros::millis() timestamp
class ControlState{
private:
    std::uint32_t timeStamp;
    std::vector<int> motorVoltages;
public:
    ControlState(std::uint32_t timeStamp, std::vector<int> motorVoltages) : timeStamp{timeStamp}, motorVoltages{motorVoltages} {};
    std::uint32_t getTimeStamp(){return timeStamp;};
    std::vector<int> getMotorVoltages(){return motorVoltages;};
    void writeTolog();
};

// writes to the current replay log file
void logCurrentControlState();

// returns new log file created on the micro sd
std::fstream selectLogFile();

#endif
