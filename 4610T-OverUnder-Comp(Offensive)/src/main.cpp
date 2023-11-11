/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ashwinkannan                                              */
/*    Created:      11/7/2023, 9:26:26 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RightFrontMotor = motor(PORT5, ratio6_1, false);
motor LeftFrontMotor = motor(PORT6, ratio6_1, true);
motor RightBackMotor = motor(PORT7, ratio6_1, false);
motor LeftBackMotor = motor(PORT8, ratio6_1, true);
motor_group leftMotors = motor_group(frontLeft, backLeft);
motor_group rightMotors = motor_group(frontRight, backRight);
motor intake = motor(PORT9, ratio18_1, false);
motor cata = motor(PORT11, ratio36_1, false);
digital_out pistonR = digital_out(Brain.ThreeWirePort.A);
digital_out pistonL = digital_out(Brain.ThreeWirePort.B);
inertial InertialA = inertial(PORT12);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

void brainDisplay(){
  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("InertialA: %f",InertialA.rotation(degrees));
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print("LeftFrontMotor: %f",LeftFrontMotor.position(degrees));
    // Allow other tasks to run
    this_thread::sleep_for(10);  
    }
}
void controllerDisplay(){
  while(true){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("InertialA: %f",InertialA.rotation(degrees));
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("LeftFrontMotor: %f",LeftFrontMotor.position(degrees));
    // Allow other tasks to run
    this_thread::sleep_for(10);
  }
}
void intialize() {
    //Calibrate Intertial Sensors
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("InertialA: Calibrating");

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("InertialA: Calibrating");

    InertialA.calibrate();
    // waits for the Inertial Sensor to calibrate
    while (InertialA.isCalibrating()) {
        wait(100, msec);
    }

    //Start Monitoring
    thread t1(brainDisplay);
    thread t2(controllerDisplay);
}

void driveCode() {
  leftMotors.spin(forward, (Controller1.Axis3.value() + Controller1.Axis1.value()), percent);
  rightMotors.spin(forward, (Controller1.Axis3.value() - Controller1.Axis1.value()), percent);
  
}

void driveForwardPH(double distance) {    //inches
    //Drive Forward with Proportional Stop and Proportional Heading Correction
    double heading = InertialA.rotation(degrees); //save heading

    LeftFrontMotor.resetPosition();
  
    double w_radius = 4.0 / 2.0; //wheel
    double r_conv = 3.14159 / 180.0; //radian conversion
    double gear_ratio = 48.0 / 72.0; //drive train gear ratio
    double target = distance / (r_conv * w_radius * gear_ratio);

    while(LeftFrontMotor.position(degrees) < target) {
        //adjust speed to slow down to the target
        double proportion = target - LeftFrontMotor.position(degrees); 
        double kp_d = .05;
        double min_speed = 1;
        double max_speed = 100;
        double speed = proportion * kp_d + min_speed; //one way to break out of the loop

        //adjust to drive straight
        double error = heading-InertialA.rotation(degrees);
        double kp_s = 1;
        double output = error*kp_s;

        double leftSpeed = speed-output;
        double rightSpeed = speed+output;

        if (leftSpeed > 100) leftSpeed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (leftSpeed > max_speed) leftSpeed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (rightSpeed > 100) rightSpeed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (rightSpeed > max_speed) rightSpeed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)

        LeftFrontMotor.spin(fwd, leftSpeed, pct);
        RightFrontMotor.spin(fwd, rightSpeed, pct);
        LeftBackMotor.spin(fwd, leftSpeed, pct);
        RightBackMotor.spin(fwd, rightSpeed, pct);
    }

    //stopping with break may allow kp and/or minspeed to be higher
    LeftFrontMotor.setStopping(brake);
    RightFrontMotor.setStopping(brake);
    LeftBackMotor.setStopping(brake);
    RightBackMotor.setStopping(brake);

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);

    LeftFrontMotor.setStopping(coast);
    RightFrontMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
}
void driveReversePH(double distance) {    //inches
    //Drive Reverse with Proportional Stop and Proportional Heading Correction
    double heading = InertialA.rotation(degrees); //save heading

    LeftFrontMotor.resetPosition();

    double w_radius = 4.0 / 2.0; //wheel
    double r_conv = 3.14159 / 180.0; //radian conversion
    double gear_ratio = 48.0 / 72.0; //drive train gear ratio
    double target = -distance / (r_conv * w_radius * gear_ratio); // reverse the distance

    while(LeftFrontMotor.position(degrees) > target) {
        //adjust speed to slow down to the target
        double proportion = LeftFrontMotor.position(degrees) - target; // reverse the proportion
        double kp_d = .05;
        double min_speed = 1;
        double max_speed = 100;
        double speed = proportion * kp_d + min_speed; //one way to break out of the loop

        //adjust to drive straight
        double error = heading - InertialA.rotation(degrees);
        double kp_s = 1;
        double output = error * kp_s;

        double leftSpeed = speed - output;
        double rightSpeed = speed + output;

        if (leftSpeed > 100) leftSpeed = 100; 
        if (leftSpeed < -max_speed) leftSpeed = -max_speed; // reverse the condition
        if (rightSpeed > 100) rightSpeed = 100;
        if (rightSpeed < -max_speed) rightSpeed = -max_speed; // reverse the condition

        LeftFrontMotor.spin(reverse, leftSpeed, pct); // reverse the direction
        RightFrontMotor.spin(reverse, rightSpeed, pct); // reverse the direction
        LeftBackMotor.spin(reverse, leftSpeed, pct); // reverse the direction
        RightBackMotor.spin(reverse, rightSpeed, pct); // reverse the direction
    }

    //stopping with break may allow kp and/or minspeed to be higher
    LeftFrontMotor.setStopping(brake);
    RightFrontMotor.setStopping(brake);
    LeftBackMotor.setStopping(brake);
    RightBackMotor.setStopping(brake);

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
    //put breaking back to coast after hanging out
    wait(25, msec);

    LeftFrontMotor.setStopping(coast);
    RightFrontMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
}

void turnLeftP(double target) {   
    //Propotional Turn Left
    InertialA.resetRotation();
    wait(.25, sec); //Intertial Sensors may take some time to settle
    
    //set a timeout for the loop
    double timeout = 5;
    time_t endtime = time(0) + timeout;
    
    while(InertialA.rotation(degrees) > -target) {
        double proportion = target + InertialA.rotation(degrees); 
        double kp = .35;
        double min_speed = .25;
        double speed = proportion * kp + min_speed; //one way to break out of the loop

        LeftFrontMotor.spin(reverse, speed, pct);
        RightFrontMotor.spin(fwd, speed, pct);
        LeftBackMotor.spin(reverse, speed, pct);
        RightBackMotor.spin(fwd, speed, pct);

        if (time(NULL) > endtime) break; //break out of loop
    }

    //stopping with break may allow kp and/or minspeed to be higher
    LeftFrontMotor.setStopping(brake);
    RightFrontMotor.setStopping(brake);
    LeftBackMotor.setStopping(brake);
    RightBackMotor.setStopping(brake);

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);
    
    LeftFrontMotor.setStopping(coast);
    RightFrontMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
}
void turnRightP(double target) {   
    //Propotional Turn Left
    InertialA.resetRotation();
    wait(.25, sec); //Intertial Sensors may take some time to settle
    
    //set a timeout for the loop
    double timeout = 5;
    time_t endtime = time(0) + timeout;
    
    while(InertialA.rotation(degrees) < target) {
        double proportion = target + InertialA.rotation(degrees); 
        double kp = .35;
        double min_speed = .25;
        double speed = proportion * kp + min_speed; //one way to break out of the loop

        LeftFrontMotor.spin(fwd, speed, pct);
        RightFrontMotor.spin(reverse, speed, pct);
        LeftBackMotor.spin(fwd, speed, pct);
        RightBackMotor.spin(reverse, speed, pct);

        if (time(NULL) > endtime) break; //break out of loop
    }

    //stopping with break may allow kp and/or minspeed to be higher
    LeftFrontMotor.setStopping(brake);
    RightFrontMotor.setStopping(brake);
    LeftBackMotor.setStopping(brake);
    RightBackMotor.setStopping(brake);

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);
    
    LeftFrontMotor.setStopping(coast);
    RightFrontMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
}


void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void autonomous(void) {
  initialize();
  driveForwardPH (?);
  turnLeftP (?);
  driveForwardPH (?);
  intake.spin(forward, 100, pct);
  wait (1 sec);
  intake.stop();
  driveBackwardPH (?);
  turnLeftP (?)
  driveForwardPH(?);
  turnLeftP (?);
  intake.spin(forward,100, pct);
  wait(1, sec);
  intake.stop();
  driveBackwardPH(?);
  turnRightP(?);
  driveForwardPH(?);
  driveBackwardPH(?);
  turnLeftP(?);
  driveBackwardPH(?);
  turnLeftP(?);
  driveForwardPH(?);

}
void usercontrol(void) {
  // User control code here, inside the loop
  while (1)
    intialize()
    {thread driveThread(driveCode);  

    //intake
    
    if (Controller1.ButtonL1.pressing()) {
      intake.spin(forward, 100, percent);
    }
    else if (Controller1.ButtonL2.pressing()) {
      intake.spin(reverse, 100, percent);
    }
    else {
      intake.stop(coast);
     }

    //cata

    if (Controller1.ButtonA.pressing()) {
      cata.spin(forward, 100, percent);
    }
    else {
      cata.stop(hold);
    }


    //pullups

    if (Controller1.ButtonB.pressing()) {
      //pullup function...
    }

    //piston

    if (Controller1.ButtonR1.PRESSED) {
      pistonR.set(true);
      pistonL.set(true);
    }
    

    if (Controller1.ButtonR2.PRESSED) {
      pistonL.set(false);
      pistonR.set(false);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
