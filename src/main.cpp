#include "main.h"
#include "globals.h"
#include <sstream>

using namespace pros;

 void printAnglerPos(){
     std::stringstream ss1;
     ss1 << "Angler motor displacement from 0:";
     std::stringstream ss2;
     ss2 << angler.get_position() << " rotations";

     pros::lcd::set_text(1, ss1.str());
     pros::lcd::set_text(3, ss2.str());
 }

void initialize() {
	pros::lcd::initialize();
	printAnglerPos();

	pros::lcd::register_btn1_cb(printAnglerPos);

	//******************//
	// SET MOTOR BRAKES //
	//******************//

	intakeL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	intakeR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	angler.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	angler.set_encoder_units(E_MOTOR_ENCODER_ROTATIONS);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
