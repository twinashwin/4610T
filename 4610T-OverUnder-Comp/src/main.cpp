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
motor frontRight = motor(PORT5, ratio6_1, false);
motor frontLeft = motor(PORT6, ratio6_1, true);
motor backRight = motor(PORT7, ratio6_1, false);
motor backLeft = motor(PORT8, ratio6_1, true);
motor_group leftMotors = motor_group(frontLeft, backLeft);
motor_group rightMotors = motor_group(frontRight, backRight);
motor intake = motor(PORT9, ratio18_1, false);
motor cata = motor(PORT11, ratio36_1, false);
digital_out pistonR = digital_out(Brain.ThreeWirePort.A);
digital_out pistonL = digital_out(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

void driveCode() {
  backLeft.spin(forward, (Controller1.Axis3.value() + Controller1.Axis1.value()), percent);
  frontLeft.spin(forward, (Controller1.Axis3.value() + Controller1.Axis1.value()), percent);
  backRight.spin(forward, (Controller1.Axis3.value() - Controller1.Axis1.value()), percent);
  frontRight.spin(forward, (Controller1.Axis3.value() - Controller1.Axis1.value()), percent);
  
}
void driveForward (int amount) {
  while (leftMotors.position(turns)<amount/18.125){
    leftMotors.spin(forward,100,pct);
    rightMotors.spin(forward,100, pct);
    wait(10,msec);
  }
  leftMotors.stop(coast);
  rightMotors.stop(coast);
}

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  driveForward (1);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1)
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

//
// Main will set up the competition functions and callbacks.
//
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
