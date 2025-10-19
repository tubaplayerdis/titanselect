#include "main.h"
#include "titanselect/titanselect.hpp"
#include "pros/adi.hpp"

ts::selector* selector = ts::selector::get();

void red_left_auton()
{

}

void blue_right_auton()
{

}

void blue_left_auton()
{

}

void red_right_auton()
{

}

ts::auton rl("Red Left", red_left_auton);
ts::auton br("Blue Right", blue_right_auton);
ts::auton rr("Red Right", red_right_auton);
ts::auton bl("Blue Left", blue_left_auton);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//selector = ts::selector::get();
	selector->display();
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
void competition_initialize() 
{
	if(!selector->is_auton_selected())
	{
		//Handle no selected auton
	}
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	selector->run_selected_auton();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master = pros::Controller(pros::E_CONTROLLER_MASTER);
	master.clear();
	std::string selected = selector->get_selected_auton_name();
	while (true)
	{
		selected = selector->get_selected_auton_name();
		master.print(1,0, "TS: %s  ", selected.c_str());

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
		{
			selector->cycle_autons();
		}

		pros::delay(100);
	}
	
}