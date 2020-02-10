#include "replay.h"
#include "globals.h"
#include "main.h"
#include "display_.h"

void ControlState::writeTolog(){
    replay_log << pros::millis() << "ms - state{";
    replay_log << "driveBL: " << motorVoltages[0] << ", ";
    replay_log << "driveBR: " << motorVoltages[1] << ", ";
    replay_log << "driveFL: " << motorVoltages[2] << ", ";
    replay_log << "driveFR: " << motorVoltages[3] << ", ";
    replay_log << "intakeL: " << motorVoltages[4] << ", ";
    replay_log << "intakeR: " << motorVoltages[5] << ", ";
        replay_log << "arm: " << motorVoltages[6] << ", ";
     replay_log << "angler: " << motorVoltages[7] << "};\n";
}

void logCurrentControlState(){
    // make vector of motor voltages
    std::vector<pros::Motor> motors{driveBL, driveBR, driveFL, driveFR, intakeL, intakeR, arm, angler};
    std::vector<int> motorVoltages;
    for(pros::Motor m : motors){
        motorVoltages.push_back(m.get_voltage());
    }

    // create current control state
    ControlState c{pros::millis(), motorVoltages};

    c.writeTolog();
}

// returns new log file created on the micro sd
std::fstream selectLogFile(){
    std::fstream outfile;
    std::fstream master_log;
    master_log.open("/usd/master_log.txt", std::fstream::in);

    // write to the end of /usd/fuckup_dump.txt if something goes wrong
    if(!master_log.is_open()){
        master_log.close();
        displayControllerError("could not open master_log");
        outfile.open("/usd/logs/fuckup_dump.txt", std::ios::app);
        return outfile;
    }

    // create new file and name it according to (int) numLogs stored in /usd/master_log.txt
    std::string path = "/usd/logs/log-";
    int numLogs;
    master_log >> numLogs;
    master_log.close();
    path += std::to_string(numLogs + 1);
    outfile.open(path);

    // write new value of numLogs to /usd/master_log.txt
    master_log.open("/usd/logs/master_log.txt", std::fstream::trunc);
    master_log << "numLogs = " << (numLogs + 1);

    master_log.close();

    return outfile;
}
