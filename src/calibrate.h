#ifndef CALIBRATE_H_
#define CALIBRATE_H_

#include "pinout.h"
#include "config.h"
#include "calculate.h"
//Define a stepper and the pins it will use

void homing() {
  // Start Homing procedure of Stepper Motor at startup
  Serial.println("<Stepper is Homing . . . . . . . . . . . >");

  // J3 homing
  while (digitalRead(Z_MIN_PIN)) {  // Make the Stepper move CCW until the switch is activated
    Z_Axis.moveTo(Z_initial_homing);  // Set the position to move to
    Z_initial_homing++;  // Decrease by 1 for next move if needed
    Z_Axis.run();  // Start moving the stepper
    delay(5);
  }

  Z_Axis.setCurrentPosition(0);  // Set the current position as zero for now
  Z_Axis.setMaxSpeed(2000.0);      // Set Max Speed of Stepper (Slower to get better accuracY)
  Z_Axis.setAcceleration(1000.0);  // Set Acceleration of Stepper
  Z_initial_homing = 1;

  while (!digitalRead(Z_MIN_PIN)) { // Make the Stepper move CW until the switch is deactivated
    Z_Axis.moveTo(Z_initial_homing);
    Z_Axis.run();
    Z_initial_homing--;
    delay(5);
  }

  Z_Axis.setCurrentPosition(0);
  Serial.println("<J3 Homing Completed>");
  Z_Axis.setMaxSpeed(2000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  Z_Axis.setAcceleration(1000.0);  // Set Acceleration of Stepper

//J2 homing
  while (digitalRead(Y_MIN_PIN)) {  // Make the Stepper move CCW until the switch is activated
    Y_Axis.moveTo(Y_initial_homing);  // Set the position to move to
    Y_initial_homing--;  // Decrease by 1 for next move if needed
    Y_Axis.run();  // Start moving the stepper
    delay(5);
  }

  Y_Axis.setCurrentPosition(0);  // Set the current position as zero for now
  Y_Axis.setMaxSpeed(2000.0);      // Set Max Speed of Stepper (Slower to get better accuracY)
  Y_Axis.setAcceleration(1000.0);  // Set Acceleration of Stepper
  Y_initial_homing = 1;

  while (!digitalRead(Y_MIN_PIN)) { // Make the Stepper move CW until the switch is deactivated
    Y_Axis.moveTo(Y_initial_homing);
  Y_Axis.run();
    Y_initial_homing++;
    delay(5);
  }

  Y_Axis.setCurrentPosition(0);
  Serial.println("<J2 Homing Completed>");
  Y_Axis.setMaxSpeed(2000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  Y_Axis.setAcceleration(1000.0);  // Set Acceleration of Stepper

//J1 homing
  while (digitalRead(X_MIN_PIN)) {  // Make the Stepper move CCW until the switch is activated
    X_Axis.moveTo(X_initial_homing);  // Set the position to move to
    X_initial_homing++;  // increase by 1 for next move if needed
    X_Axis.run();  // Start moving the stepper
     delay(5);
  }

  X_Axis.setCurrentPosition(0);  // Set the current position as zero for now
  X_Axis.setMaxSpeed(2000.0);      // Set Max Speed of Stepper (Slower to get better accuracY)
  X_Axis.setAcceleration(1000.0);  // Set Acceleration of Stepper
  X_initial_homing = 1;

  while (!digitalRead(X_MIN_PIN)) { // Make the Stepper move CW until the switch is deactivated
    X_Axis.moveTo(X_initial_homing);
    X_Axis.run();
    X_initial_homing--;
     delay(5);
  }

  X_Axis.setCurrentPosition(0);
  Serial.println("<J1 Homing Completed>");
  X_Axis.setMaxSpeed(2000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  X_Axis.setAcceleration(1000.0);  // Set Acceleration of Stepper

  //addition
  // after homing, move off home position
  delay (1000);

  X_newPosition = 5600;
  Y_newPosition = 2500;
  Z_newPosition = 2500;
  long positions[3]; // Array of desired stepper positions

  positions[0] = X_newPosition; //needs positive movement from home CW
  positions[1] = -(Y_newPosition); // needs negative movement from home
  positions[2] = Z_newPosition; // needs negative movement from home
  steppers.moveTo(positions);
  //steppers.run(); // preferable to allow checking for reaching limit switches
  steppers.runSpeedToPosition(); // Blocks until all are in position - Can't check limit switches
} // end void homing

#endif