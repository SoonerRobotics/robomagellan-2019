#ifndef MOTION_GLOBALS_H
#define MOTION_GLOBALS_H

//Decision Configuration
#define DEGREES_OFF_ALLOWED 20
#define OPENCV_ALLOWED_ERROR 25

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
#define MAX_TURN_ANGLE      35                  //Maximum servo turn angle in degrees
#define MAX_TURN_POWER      (float)(0.4)
#define SERVO_KP            (float)(0.2)
#define SERVO_KI            (float)(0.001)
#define SERVO_KD            (float)(0.004)
#define TURN_TOLERANCE      (float)(0.5)        //Most error allowed in turn angle
#define SERVO_MOVE_TIMEOUT  (float)(1250)       //milliseconds before giving up on servo turn

//Switches
#define LIMIT_PIN 9   //Pin with limit switch for cone contact on it

//Default power
#define DEFAULT_POWER 0.22

//Debug flags
#define IS_DEBUG 1

//System update constants
#define SERVO_UPDATE_EPS    50
#define DT_UPDATE_EPS       20

//JSON constants
#define MOTION_DEVICE_ID    1                                               //Device ID for initial serial packets
#define STD_BAUD_RATE       115200                                          //Baud rate of all devices

//Serial update
#define SERIAL_UPDATE_RATE 100  //100 Hz update rate

//Radio message types
#define MSG_KILL 1
#define MSG_START 2
#define MSG_PAUSE 3

//Robot operation states
#define RUN_STATE 1
#define PAUSE_STATE 2

#endif
