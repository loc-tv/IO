#ifndef _MOVE_FUNCTION_H_
#define _MOVE_FUNCTION_H_

#include "library.h"
#include "pinout.h"
#include "config.h"
#include "calibrate.h"
#include "calculate.h"
void move() 
{
  long positions[3]; // Array of desired stepper positions

  positions[0] = X_newPosition; //needs positive movement from home CW
  positions[1] = -(Y_newPosition); // needs negative movement from home
  positions[2] = Z_newPosition; // needs negative movement from home
  steppers.moveTo(positions);
  steppers.run(); // preferable to allow checking for reaching limit switches

  // stop movement if end / home switch activated

  if (digitalRead(X_MIN_PIN) == HIGH) {
    X_newPosition = X_Axis.currentPosition() + 50;
    Serial.println ("X limit switch activated");
  }

  if (digitalRead(Y_MIN_PIN) == HIGH) {
    Y_newPosition = -(Y_Axis.currentPosition() - 50);
    Serial.println ("Y limit switch activated");
  }

  if (digitalRead(Z_MIN_PIN) == HIGH)  {
    Z_newPosition = -(Z_Axis.currentPosition() - 100);
    Y_newPosition = -(Y_Axis.currentPosition() - 100); //J2 influences J3
    Serial.println ("Z limit switch activated");
  }
  // stop movement if end / home switch activated
} // end void move

// start move direct blocking

void move2() 
{
  long positions[3]; // Array of desired stepper positions

  positions[0] = X_newPosition; //needs positive movement from home CW
  positions[1] = -(Y_newPosition); // needs negative movement from home
  positions[2] = Z_newPosition; // needs negative movement from home
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // blocking direct move
}

void move3(float x1, float y1) 
{
  float newR = (float)x1 / 100.0;
  float newS = (float)y1 / 100.0;
  calculateAngles(newR, newS, T);
  calcMoveSteps();
  move2();
}

#endif // _MOVE_FUNCTION_H_