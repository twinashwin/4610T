/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Tue Nov 07 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotors           motor_group   8, 6            
// rightMotors          motor_group   5, 7            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
void driveForward (int amount) {
  while (leftMotors.position(turns)<amount/18.125){
    leftMotors.spin(forward,100,pct);
    rightMotors.spin(forward,100, pct);
    wait(10,msec);
  }
  leftMotors.stop(coast);
  rightMotors.stop(coast);
}

int main() {
  //1 turn-7 and 1/8
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  driveForward(1);
  //outake();
  //driveBackward()
}
