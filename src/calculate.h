#ifndef _CALCULATE_H_
#define _CALCULATE_H_

#include <math.h>
#include "config.h"
// #define PI 3.14159265358979323846

float atan3(float dy, float dx) {
  float a = atan2f(dy, dx);
  if (a < 0) a = (PI * 2.0f) + a;
  return a;
}

void calculateAngles(float R, float S, float T) 
{ //from R=X coordinate, S=Y coordinate, T=Z coordinate

  //"The Angle Theta One"
  Q1 = S / R;
  W1 = atan(Q1) / (180.0 / PI);

  if (R >= 0 && S >= 0) {
    f = W1 / 0.1;   
    AngleThetaOne = W1;
  }
  else if (R <= 0 && S >= 0) {
    E1 = 180 + W1;
    f = E1 / 0.1;
    AngleThetaOne = E1;
  }
  else if (R <= 0 && S <= 0) {
    E1 = 180 + W1;
    f = E1 / 0.1;
    AngleThetaOne = E1;
  }
  else {
    E1 = 360 + W1;
    f = E1 / 0.1;
    AngleThetaOne = E1;
  }

  // The Angle Theta 2
  Q0 = (T - 10) / (sqrt((R * R) + (S * S)));
  W0 = atan(Q0) / (180.0 / PI);
  Q4 = ((13.5 * 13.5) + (R * R) + (S * S) + ((T - 10) * (T - 10)) - (16 * 16)) / (2 * 13.5 * sqrt((R * R) + (S * S) + ((T - 10) * (T - 10))));
  W4 = acos(Q4) / (180.0 / PI);
  E2 = W0 + W4;
  AngleThetaTwo = E2;
  if (AngleThetaTwo <= 36)  {
    AngleThetaTwo = 36; // limits AngleThetaTwo to its mechanical limit of 23 degrees
    Serial.println ("Link 2 Angle limit reached");
  }  // limits AngleThetaTwo to 40 degrees or more

  // The Angle Theta 3
  Q3 = ((R * R) + (S * S) + ((T - 10) * (T - 10)) - (13.5 * 13.5) - (16 * 16)) / (2 * 13.5 * 16);
  W3 = acos(Q3) / (180.0 / PI);
  E3 = -1 * W3;
  AngleThetaThree = E3;
  if (AngleThetaThree > -50) {
    AngleThetaThree = -50; // limits AngleThetaThree to -50 degrees or less
    Serial.print("Link 3 Angle limit reached"); Serial.println (E3);
  }
}

void calcMoveSteps () 
{  
  // Firstly for base motor X
  if (AngleThetaOne <= 180) 
    X_newPosition = (110 - AngleThetaOne) * StepsPerDegreeOne;

  if (AngleThetaOne > 180)
    X_newPosition = (470 - AngleThetaOne) * StepsPerDegreeOne;

  X_newPosition = round(X_newPosition);
  // end code for base motor X

  // Secondly for Y
  Y_newPosition = (91 - AngleThetaTwo) * StepsPerDegreeTwo; // initial angle for J2
  Y_newPosition = round(Y_newPosition);
  // end code for Y

  // code for Z
  Z_newPosition = ((abs(AngleThetaThree) - 93 ) * StepsPerDegreeThree) + Y_newPosition;
  Z_newPosition = round(Z_newPosition);
  // end code for J3
}

#endif