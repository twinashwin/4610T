using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern digital_out piston;
extern motor intake;
extern motor cata;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );