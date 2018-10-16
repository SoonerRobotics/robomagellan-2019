#ifndef MOTION_GLOBALS_H
#define MOTION_GLOBALS_H

//Decision Configuration
#define DEGREES_OFF_ALLOWED 20

//Drive motor pins
#define DRIVE_MOTOR_A   4
#define DRIVE_MOTOR_B   5
#define DRIVE_MOTOR_ENB 3

//Servo motor pins
#define SERVO_MOTOR_A   7
#define SERVO_MOTOR_B   8
#define SERVO_MOTOR_ENB 6
#define TURN_POT_PIN A0

//Servo motor constants
#define MAX_TURN_ANGLE  30              //Maximum servo turn angle in degrees
#define MAX_TURN_POWER  (float)(0.6)
#define SERVO_KP        (float)(0.6)
#define SERVO_KI        (float)(0.0)
#define SERVO_KD        (float)(0.001)

//I2C addresses
#define MOTION_ADDR 0x18

//I2C constants
#define I2C_MAX  (float)(255)

//Debug flags
#define IS_DEBUG 1

#endif