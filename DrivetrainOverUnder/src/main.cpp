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
// Controller1          controller                    
// frontRight           motor         5               
// frontLeft            motor         6               
// backRight            motor         7               
// backLeft             motor         8               
// intake               motor         9               
// cata                 motor         11              
// piston               digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void driveCode() {
  backLeft.spin(forward, (Controller1.Axis3.value() + Controller1.Axis1.value()), percent);
  frontLeft.spin(forward, (Controller1.Axis3.value() + Controller1.Axis1.value()), percent);
  backRight.spin(forward, (Controller1.Axis3.value() - Controller1.Axis1.value()), percent);
  frontRight.spin(forward, (Controller1.Axis3.value() - Controller1.Axis1.value()), percent);
  
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  //drive Code

  
  
  while (true) {
    thread driveThread(driveCode);  

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

    if (Controller1.ButtonR2.pressing()) {
      cata.spin(forward, 100, percent);
    }
    else {
      cata.stop();
    }

    //pullups

    if (Controller1.ButtonR1.pressing()) {
      //pullup function...
    }

    //piston

    if (Controller1.ButtonX.pressing()) {
      piston.set(true);
    }
    if (Controller1.ButtonA.pressing()) {
      piston.set(false);
    }
  }  
  
}
