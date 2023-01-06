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
//https://github.com/laurb9/StepperDriver
#include <A4988.h>

A4988 stepper(200, 2, 3, 4, 5); // initialize the A4988 library with the number of steps, and the pin numbers for the direction, step, and enable pins

const int potentiometerPin = A0; // analog input pin for the potentiometer

void setup() {
  stepper.setSpeed(0); // set the initial speed to 0
}

void loop() {
  int potentiometerValue = analogRead(potentiometerPin); // read the value of the potentiometer
  int speed = map(potentiometerValue, 0, 1023, 0, 100); // map the potentiometer value to a range of 0-100
  stepper.setSpeed(speed); // set the speed of the motor
  stepper.step(200, FORWARD, SINGLE); // move the motor 200 steps in the forward direction
  delay(1000); // delay for 1 second
}
