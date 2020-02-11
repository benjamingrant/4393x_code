#include "replay.h"
#include "globals.h"
#include "main.h"
#include "display_.h"

//*********//
// Logging //
//*********//

void ControlState::writeToLogfile(){
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

ControlState getCurrentControlState(){
    // make vector of motor voltages
    std::vector<pros::Motor> motors{driveBL, driveBR, driveFL, driveFR, intakeL, intakeR, arm, angler};
    std::vector<int> motorVoltages;
    for(pros::Motor m : motors){
        motorVoltages.push_back(m.get_voltage());
    }

    // return current control state
    ControlState c{pros::millis(), motorVoltages};

    return c;
}

// returns new log file created on the micro sd
std::fstream generateLogFile(){
    std::stringstream outfilePath;
    std::fstream outfile;
    std::fstream master_log;

    // open /usd/master_log.txt, which contains number of active logs
    master_log.open("/usd/master_log.txt", std::fstream::in);

    // write to the end of /usd/fuckup_dump.txt if something goes wrong
    if(!master_log.is_open()){
        displayControllerError("could not open master_log");
        outfile.open("/usd/fuckup_dump.txt", std::ios::app);
        return outfile;
    }

    // create new file and name it according to (int) numLogs stored in /usd/master_log.txt
    int numLogs;
    master_log >> numLogs;
    master_log.close();
    outfilePath << "/usd/log-" << (numLogs + 1) << ".txt";
    outfile.open(outfilePath.str());

    // write new value of numLogs to /usd/master_log.txt
    master_log.open("/usd/master_log.txt", std::fstream::trunc);
    master_log << "numLogs = " << (numLogs + 1);

    master_log.close();

    return outfile;
}

//********//
// Replay //
//********//

// returns opened log file ("/usd/log-[logNumber].txt")
std::ifstream getLogfile(int logNumber){
    std::stringstream outfilePath;
    std::ifstream outfile;

    // open specified log file
    outfilePath << "/usd/log-" << logNumber << ".txt";
    outfile.open(outfilePath.str(), std::fstream::trunc);

    return outfile;
}

// set motors to a ControlState from selected log selected log file
void executeControlState(ControlState c){
    std::vector<pros::Motor> motors{driveBL, driveBR, driveFL, driveFR, intakeL, intakeR, arm, angler};

    // iterate through the robot's motors, setting each's voltage to c's corresponding voltage
    for(int i = 0; i < motors.size(); i++){
        motors[i].move_voltage(c.getMotorVoltages()[i]);
    }
}

// parse selected log file and execute its ControlStates
void executeLogfile(std::ifstream logfile){
    // holds a line from the log file
    std::string _currentControlState;

    // iterates over every line in the log file
    while(std::getline(logfile, _currentControlState)){
        std::istringstream iss(_currentControlState);

        std::uint32_t time;

        // gets timestamp from the line
        iss >> time;

        std::vector<int> voltages;

        // gets voltages from the line
        int v;
        while (iss >> v) {
            voltages.push_back(v);
        }

        // generate ControlState from line
        ControlState currentControlState{time, voltages};

        // set motors' voltages
        executeControlState(currentControlState);

        // delay 20 ms
        pros::delay(20);
    }

    logfile.close();
    master.rumble("._.");
}
