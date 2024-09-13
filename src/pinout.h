// #ifndeft PINOUT_H_ //if not defined
#ifndef PINOUT_H_
#define PINOUT_H_  //header guard
/*
  *RAMPS 1.4 PINOUT
  *soure: http://reprap.org/wiki/RAMPS1.4
*/


//X_STEPPER
#define X_STEP_PIN A0
#define X_DIR_PIN A1
#define X_ENABLE_PIN 38
#define X_MIN_PIN 3
#define X_MAX_PIN 2

//Y_STEPPER
#define Y_STEP_PIN A6
#define Y_DIR_PIN A7
#define Y_ENABLE_PIN 56
#define Y_MIN_PIN 14
#define Y_MAX_PIN 15

//Z_STEPPER
#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62
#define Z_MIN_PIN 18
#define Z_MAX_PIN 19

#endif
