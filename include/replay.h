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
    void log();
};

void logCurrentControlState();

#endif
