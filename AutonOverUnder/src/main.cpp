/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ashwinkannan                                              */
/*    Created:      Wed Sep 27 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    2, 4, 1, 3      
// piston               digital_out   A               
// intake               motor         5               
// cata                 motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //initial drive code to get robot at match load zone
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(reverse, 600, mm);


  //match load cata launch

 // cata.srward, 100, percent);pin(fo
  //time is changable
  //wait(30, sec);
  //cata.stop(hold);
  
  Drivetrain.driveFor(forward, 1800, mm);
  Drivetrain.turnFor(right, 45, degrees);
  Drivetrain.driveFor(forward, 600, mm);
  piston.set(true);
  Drivetrain.driveFor(forward, 600, mm);
  Drivetrain.driveFor(reverse, 600, mm);
  Drivetrain.turnFor(right, 20, degrees);
  Drivetrain.driveFor(forward, 600, mm);
  Drivetrain.driveFor(reverse, 600, mm);
  Drivetrain.turnFor(left, 40, degrees);
  Drivetrain.driveFor(forward, 600, mm);
  Drivetrain.driveFor(reverse, 600, mm);
  Drivetrain.turnFor(right, 110, degrees);
  Drivetrain.driveFor(forward,800,mm);
  Drivetrain.turnFor(left, 45, degrees);
  Drivetrain.driveFor(forward, 200, mm);
  Drivetrain.turnFor(left, 45, degrees);
  Drivetrain.driveFor(forward, 250, mm);
  Drivetrain.turnFor(left, 90, degrees);
  Drivetrain.driveFor(forward, 400, mm);
}
