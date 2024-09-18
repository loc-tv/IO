#include "config.h"
#include "calibrate.h"
#include "calculate.h"
#include "communications.h"
#include "move_funstion.h"
#include "draw.h"

void setup() 
{
  Serial.begin(9600);
  // my addition to set x,y, z driver enable pins to output

  pinMode (X_ENABLE_PIN, OUTPUT); // x enable pin
  pinMode (Y_ENABLE_PIN, OUTPUT); 
  pinMode (Z_ENABLE_PIN, OUTPUT);  

  digitalWrite (X_ENABLE_PIN, LOW);  // x enable
  digitalWrite (Y_ENABLE_PIN, LOW);
  digitalWrite (Z_ENABLE_PIN, LOW);  

  pinMode(X_MIN_PIN, INPUT_PULLUP);  //sets end switch to pullup
  pinMode(Y_MIN_PIN, INPUT_PULLUP);
  pinMode(Z_MIN_PIN, INPUT_PULLUP);

//Add a steppper to the set of managed steppers
  steppers.addStepper(X_Axis);
  steppers.addStepper(Y_Axis);
  steppers.addStepper(Z_Axis);

  //  Set Max Speed and Acceleration of each Steppers at startup for homing

  X_Axis.setMaxSpeed(2000.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  X_Axis.setAcceleration(1000.0);  // Set Acceleration of Stepper

  Y_Axis.setMaxSpeed(2000.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  Y_Axis.setAcceleration(1000.0);  // Set Acceleration of Stepper

  Z_Axis.setMaxSpeed(2000.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  Z_Axis.setAcceleration(1000.0);  // Set Acceleration of Stepper
  Serial.println("test");

  homing();

}

void loop() 
{
  if (X_Axis.currentPosition() == X_newPosition && Y_Axis.currentPosition() == (-Y_newPosition) && Z_Axis.currentPosition() == (-Z_newPosition) && executedOk == false ) {
    Serial.println ("<ok>");
    executedOk = true;
  }

  recvWithStartEndMarkers();

  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    x1 = R; // stores current X before parse as x1
    y1 = S; // stores current Y before parse as y1
    parseData(); // generates new R,S,T
    //endX = R;
    //endY = S;
    showParsedData();
    calculateAngles (R, S, T); // from R,S,T
    calcMoveSteps ();
    executedOk = false;
  }
  // additional code to run after parsing

  if (strcmp(gCode, "home") == 0) {
    homing();
    strcpy (gCode, "G5"); // needed to terminate loop
  }

  // new addition Bresenham

  if (strcmp(gCode, "G1") == 0) {
    Serial.println ("G1 Bresenham code move");
    Bresenham (x1, y1, R, S);
  }
  // end Bresenham addition

  if (strcmp(gCode, "G2") == 0) {
    dir = 0;
    Serial.println ("G2 code move");
    arc(cX, cY, R, S, dir); // (cX, cY, endX, endY, dir) temporary experiment
  }

  if (strcmp(gCode, "G3") == 0) {
    dir = 1;
    Serial.println ("G3 code move");
    arc(cX, cY, R, S, dir); // (cX, cY, endX, endY, dir) temporary experiment
  }

  // end additional code to run after parsing
  newData = false;

  move();
}
