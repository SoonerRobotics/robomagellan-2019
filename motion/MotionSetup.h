#ifndef MOTION_SETUP_H
#define MOTION_SETUP_H

#include <Wire.h>
#include "MotionGlobals.h"
#include "Drivetrain.h"
#include "ArduinoJson.h"

//Full serial data packet
typedef struct DataPacket_u
{
    //GPS Location Stuff
    bool nearCone;          //true if near cone, false if not
    float curHeading;       //current robot heading
    float destHeading;      //target robot heading

    //OpenCV Stuff
    float opencv_error;     //error between center screen and percieved cone
    bool canSeeCone;        //tells if the cone is in the viewport of the camera
} DataPacket;

//Declare systems
Drivetrain drivetrain;

//Most recent data from the raspberry pi
DataPacket curData;

//Size of the data string
const int json_str_size = JSON_OBJECT_SIZE(NUM_JSON_VALUES);

//Forward Declare Routines
void reverseRoutine();

void motionSetup()
{
    //Declare local variables
    Motor motor;
    Motor servo;
    RomaServo romaServo;

    //Start serial for input
    //Note: this baud rate must be standard across devices
    Serial.begin(STD_BAUD_RATE);

    //Initialize i2c as slave
    Wire.begin(MOTION_ADDR);

    //Initialize individual motors
    motor.begin(DRIVE_MOTOR_A, DRIVE_MOTOR_B, DRIVE_MOTOR_ENB);
    servo.begin(SERVO_MOTOR_A, SERVO_MOTOR_B, SERVO_MOTOR_ENB);

    //Fully set up the RomaServo
    romaServo.begin(servo, TURN_POT_PIN, MAX_TURN_POWER);
    romaServo.setPID(SERVO_KP, SERVO_KI, SERVO_KD);

    //Initialize Drivetrain
    drivetrain.begin(motor, romaServo);

    //Attach an inturrupt to the limit switch to reverse when pressed
    attachInterrupt(LIMIT_PIN, reverseRoutine, RISING);

    //Wait until the raspberry pi has booted up
    while(Serial.peek() == -1)
    { 
        //Send messsages into the void
        Serial.println("gimme bytes"); 
        delay(20); 
    }

    //Send first acknowledgement
    Serial.println(MOTION_DEVICE_ID);
}

/******************************************
            JSON Serial Handler
******************************************/

//Callback for received data
void serialEvent()
{
    //Declare local variabls
    String rawInput;
    StaticJsonBuffer<json_str_size> jsonBuffer;
    
    //Initialize Local variables
    rawInput = "";

    //Serial output device ID
    Serial.println(MOTION_DEVICE_ID);

    //Read data off the bus
    while(Serial.available())
    {
        //Get a data character and add it to the string
        char data = (char)Serial.read();
        rawInput += data;

        //End transmission on newline
        if(data == '\n')
        {
            break;
        }
    } 

    //Parse the input string
    JsonObject& jsonObject = jsonBuffer.parseObject(rawInput);

    //If the parse was successful, add the data to the struct
    if(jsonObject.success())
    {
        curData.nearCone        = jsonObject["gps_near_cone"].as<bool>();
        curData.curHeading      = jsonObject["gps_heading"].as<float>();
        curData.destHeading     = jsonObject["traj_heading"].as<float>();
        curData.opencv_error    = jsonObject["opencv_error"].as<int>();
        curData.canSeeCone      = jsonObject["opencv_cone_visible"].as<bool>();
    }

    //Serial Test code REMOVE LATER
    //jsonObject.printTo(Serial);
    //Serial.println();
}

/**********************
      ROUTINES
 **********************/

/**
 * Routine to run when the robot needs to revese away from an obstacle
 */
void reverseRoutine()
{
    //Reverse the motor
    drivetrain.setPower(-0.22);
    
    //Wait for 1 second
    delay(1000);

    //Stop the reverse to avoid anything silly
    drivetrain.setPower(0);
}

#endif
