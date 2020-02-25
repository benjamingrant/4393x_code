#include "replay.h"
#include "globals.h"
#include "main.h"
#include "display_.h"

//*********//
// Logging //
//*********//

void ControlState::writeToLogfile(){
    /*
    example line:
         time  driveBL  driveBR  driveFL  driveFR  intakeL  intakeR      arm   angler
           20        0    10000        0    10000    12000    12000     2000        0
    */

    replay_log << std::setw(9) << pros::millis();


    for(int v : motorVoltages){
        replay_log << std::setw(9) << v;
    }

    replay_log << std::endl;

    // replay_log << pros::millis() << "ms - controlState{";
    // replay_log << "driveBL: " << motorVoltages[0] << ", ";
    // replay_log << "driveBR: " << motorVoltages[1] << ", ";
    // replay_log << "driveFL: " << motorVoltages[2] << ", ";
    // replay_log << "driveFR: " << motorVoltages[3] << ", ";
    // replay_log << "intakeL: " << motorVoltages[4] << ", ";
    // replay_log << "intakeR: " << motorVoltages[5] << ", ";
    //     replay_log << "arm: " << motorVoltages[6] << ", ";
    //  replay_log << "angler: " << motorVoltages[7] << "};\n";
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
std::fstream newLogFile(){
    std::stringstream outfilePath;
    std::fstream outfile;

    // open /usd/master_log.txt, which contains number of active logs
    std::ifstream input_master_log;
    input_master_log.open("/usd/master_log.txt", std::ios::in);

    // write to /usd/fuckup_dump.txt if something goes wrong
    if(!input_master_log.is_open()){
        displayControllerError("could not open master_log");
        outfile.open("/usd/fuckup_dump.txt", std::ios::out | std::ios::trunc);
        return outfile;
    }

    // create new file and name it according to (int) numLogs stored in /usd/master_log.txt
    int numLogs;
    input_master_log >> numLogs;
    numLogs = numLogs + 1;
    input_master_log.close();
    outfilePath << "/usd/log-" << numLogs << ".txt";
    displayControllerMessage(outfilePath.str());
    outfile.open(outfilePath.str().c_str(), std::ios::out | std::ios::trunc);

    // write [header/legend] at the top
    outfile << "time  driveBL  driveBR  driveFL  driveFR  intakeL  intakeR      arm   angler" << std::endl;

    // write new value of numLogs to /usd/master_log.txt
    std::ofstream output_master_log;
    output_master_log.open("/usd/master_log.txt", std::ios::trunc);
    output_master_log << numLogs << std::endl;
    output_master_log.close();

    return outfile;
}

// returns (new) or (old, truncated) file on the micro sd
std::fstream getLogFile(int logNumber){
    std::stringstream outfilePath;
    std::fstream outfile;

    // create file path from logNumber
    outfilePath << "/usd/log-" << logNumber << ".txt";

    // open and erase the file
    outfile.open(outfilePath.str().c_str(), std::ios::out | std::ios::trunc);

    // write [header/legend] at the top
    outfile << "time  driveBL  driveBR  driveFL  driveFR  intakeL  intakeR      arm   angler" << std::endl;

    return outfile;
}

//********//
// Replay //
//********//

// returns opened log file ("/usd/log-[logNumber].txt")
const char * getLogfilePath(int logNumber){
    std::stringstream logfilePath;
    std::fstream logfile;

    // open specified log file
    logfilePath << "/usd/log-" << logNumber << ".txt";

    return logfilePath.str().c_str();
}

// set motors to a ControlState from selected log selected log file
void executeControlState(ControlState c){
    // putting the global motor objects in a vector for easy looping
    std::vector<pros::Motor> motors{driveBL, driveBR, driveFL, driveFR, intakeL, intakeR, arm, angler};

    // iterate through the robot's motors, setting each's voltage from the cunt-roll state
    for(int i = 0; i < motors.size(); i++){
        motors[i].move_voltage(c.getMotorVoltages()[i]);
    }
}

// parse selected log file and execute its ControlStates
void executeReplay(int logfileNumber){
    // open exectutionLog
    exectutionLog.open(getLogfilePath(logfileNumber), std::ios::in);

    // error
    if(!exectutionLog.is_open()){
        std::stringstream ss;
        ss << "exlog " << logfileNumber << " not open" ;
        displayControllerError(ss.str());
        return;
    }

    uint32_t t0 = pros::millis();

    // get rid of header
    std::string header;
    std::getline(exectutionLog, header);

    // holds a line from the log file
    std::string currentControlState;

    // iterates over every line in the log file
    while(std::getline(exectutionLog, currentControlState)){
        std::istringstream iss(currentControlState);

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

        // set motors' voltages from the controlState
        executeControlState(currentControlState);

        // delay 22 ms
        pros::delay(31);
    }

    uint32_t t1 = pros:: millis();

    // close file and give a status vibration
    exectutionLog.close();
//master.rumble("._.");
    std::stringstream ss;
    ss << (t1 - t0);
    displayControllerMessage(ss.str());
}
