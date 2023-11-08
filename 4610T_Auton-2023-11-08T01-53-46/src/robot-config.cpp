#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorsMotorA = motor(PORT8, ratio6_1, true);
motor leftMotorsMotorB = motor(PORT6, ratio6_1, true);
motor_group leftMotors = motor_group(leftMotorsMotorA, leftMotorsMotorB);
motor rightMotorsMotorA = motor(PORT5, ratio6_1, false);
motor rightMotorsMotorB = motor(PORT7, ratio6_1, false);
motor_group rightMotors = motor_group(rightMotorsMotorA, rightMotorsMotorB);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}