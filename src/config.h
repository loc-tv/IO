
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

const unsigned numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
float X_Coordinate = 15;
float Y_Coordinate = 0;
float Z_Coordinate = 15;

float scale = 1.0; // used to adjust scale of X,Y input to real world distance
float scaleZ = 1.0; // adjust Z scaling

float endX; // variable for parsed G2/G3 move data
float endY;
float cX; // aka I
float cY; // aka J
float I;
float J;

float dir; // 0 or 1
float x1;
float y1;
float x2;
float y2;

float R = 15; // some reasonable values to start with so that after first parse there are past values for G1 move
float S = 0;
float T = 15;

float AngleThetaOne;
float AngleThetaTwo;
float AngleThetaThree;
char gCode[numChars] = {0};

int StepsPerDegreeOne = 89; //calibrate steps per degree of Theta One
int StepsPerDegreeTwo = 89; // calibrate steps per degree for Theta Two
int StepsPerDegreeThree = 89; // calibrate steps per degree for Theta Three

float X_newPosition = 0; // stepper count for J1 position
float Y_newPosition = 0;
float Z_newPosition = 0;

int F = 0, f;
float Q1, W1, E1;
float Q0, Q4, W0, W4, E2;
float Q3, W3, E3;

bool newData = false;
bool executedOk = false;  // boolean variable to check if move is completed

// end #1

AccelStepper X_Axis(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper Y_Axis(1, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper Z_Axis(1, Z_STEP_PIN, Z_DIR_PIN);

MultiStepper steppers;

int X_move_finished = 1; // Usgithubed to check if move is completed - DOESN'T SEEM TO BE USED
long X_initial_homing = -1; // Used to Home Stepper at startup

int Y_move_finished = 1; // Used to check if move is completed - DOESN'T SEEM TO BE USED
long Y_initial_homing = -1; // Used to Home Stepper at startup

int Z_move_finished = 1; // Used to check if move is completed - DOESN'T SEEM TO BE USED
long Z_initial_homing = -1; // Used to Home Stepper at startup

#endif