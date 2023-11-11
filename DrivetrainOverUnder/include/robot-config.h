using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor frontRight;
extern motor frontLeft;
extern motor backRight;
extern motor backLeft;
extern motor intake;
extern motor cata;
extern digital_out pistonL;
extern digital_out pistonR;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );