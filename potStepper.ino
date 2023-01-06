/*To control the speed of a stepper motor with a potentiometer,
you will need to connect the potentiometer to an analog input pin on the Arduino.
Then, you can use the Arduino's analogRead() function to read the value of
the potentiometer and use that value to set the speed of the stepper motor.

You can use the Arduino analogWrite() function to
 control the speed of the stepper motor by connecting
 the motor to one of the Arduino's PWM (pulse-width modulation) output pins
 . The analogWrite() function takes a value between 0 and 255, with 0 representing 0%
  duty cycle and 255 representing 100% duty cycle.

To make the stepper motor turn in one direction, you will
need to use a stepper motor driver that can control the direction of the motor
. You can use the Arduino to send a
signal to the driver to change the direction of the motor.*/
// https://github.com/laurb9/StepperDriver
/*
 * Using accelerated motion ("linear speed") in nonblocking mode
 *
 * Copyright (C)2015-2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
// Target RPM for cruise speed
#define RPM 120
// Acceleration and deceleration values are always in FULL steps / s^2
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000

// Microstepping mode. If you hardwired it to save pins, set to the same value here.
#define MICROSTEPS 16

#define DIR 8
#define STEP 9
#define SLEEP 13 // optional (just delete SLEEP from everywhere if not used)

/*
 * Choose one of the sections below that match your board
 */

// #include "DRV8834.h"
// #define M0 10
// #define M1 11
// DRV8834 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, M0, M1);

#include "A4988.h"
#define MS1 10
#define MS2 11
#define MS3 12
A4988 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, MS1, MS2, MS3);

// #include "DRV8825.h"
// #define MODE0 10
// #define MODE1 11
// #define MODE2 12
// DRV8825 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, MODE0, MODE1, MODE2);

// #include "DRV8880.h"
// #define M0 10
// #define M1 11
// #define TRQ0 6
// #define TRQ1 7
// DRV8880 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, M0, M1, TRQ0, TRQ1);

// #include "BasicStepperDriver.h" // generic
// BasicStepperDriver stepper(DIR, STEP);
const int potentiometerPin = A0; // analog input pin for the potentiometer

void setup()
{
  Serial.begin(115200);

  stepper.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  // stepper.setEnableActiveState(LOW);
  stepper.enable();
  // set current level (for DRV8880 only). Valid percent values are 25, 50, 75 or 100.
  // stepper.setCurrent(100);

  /*
   * Set LINEAR_SPEED (accelerated) profile.
   */
  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

  Serial.println("START");
  /*
   * Using non-blocking mode to print out the step intervals.
   * We could have just as easily replace everything below this line with
   * stepper.rotate(360);
   */
  stepper.startRotate(360);
}

void loop()
{
  static int step = 0;
  int potentiometerValue = analogRead(potentiometerPin); // read the value of the potentiometer
  int speed = map(potentiometerValue, 0, 1023, 0, 100);  // map the potentiometer value to a range of 0-100
  unsigned wait_time = stepper.nextAction();
  if (wait_time)
  {
    Serial.print("  step=");
    Serial.print(step++);
    Serial.print("  dt=");
    Serial.print(wait_time);
    Serial.print("  rpm=");
    Serial.print(stepper.getCurrentRPM());
    Serial.println();
  }
  else
  {
    // stepper.disable();
    // Serial.println("END");
    // delay(3600000);
  }
}
