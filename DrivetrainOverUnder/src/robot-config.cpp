#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor frontRight = motor(PORT1, ratio6_1, true);
motor frontLeft = motor(PORT2, ratio6_1, false);
motor backRight = motor(PORT3, ratio6_1, true);
motor backLeft = motor(PORT4, ratio6_1, false);
motor intake = motor(PORT5, ratio18_1, false);
motor cata = motor(PORT6, ratio18_1, false);
digital_out piston = digital_out(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}