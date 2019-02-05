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
    float steeringAngle     //Steering angle

    //OpenCV Stuff
    float opencv_error;     //error between center screen and percieved cone
    bool canSeeCone;        //tells if the cone is in the viewport of the camera
} DataPacket;

//Declare systems
Drivetrain drivetrain;

//Most recent data from the raspberry pi
DataPacket curData;

//Size of the data strings
const int json_str_size_in = NUM_JSON_VALUES_IN;
const int json_str_size_out = NUM_JSON_VALUES_OUT;

//Forward Declare Functions as needed
void sendMotionSerialData(bool birth_packet);
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
        sendMotionSerialData(true);
        delay(100); 
    }

    //Send first acknowledgement
    sendMotionSerialData(true);
}

/******************************************
            JSON Serial Handler
******************************************/

//Callback for received data
void serialEvent()
{
    //Declare local variabls
    String rawInput;
    DyynamicJsonBuffer jsonBuffer(json_str_size_in);
    
    //Initialize Local variables
    rawInput = "";

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
    JsonObject& root = jsonBuffer.parseObject(rawInput);

    //If the parse was successful, add the data to the struct
    if(jsonObject.success())
    {
        curData.nearCone        = root["data"]["gps_near_cone"].as<bool>();
        curData.curHeading      = root["data"]["gps_heading"].as<float>();
        curData.destHeading     = root["data"]["traj_heading"].as<float>();
        curData.power           = root["data"]["traj_power"].as<float>();
        curData.opencv_error    = root["data"]["opencv_error"].as<int>();
        curData.canSeeCone      = root["data"]["opencv_cone_visible"].as<bool>();
    }

    //Serial Test code REMOVE LATER
    //jsonObject.printTo(Serial);
    //Serial.println();
}

/**
 * Function that sends data to the main board. Will also send a birth packet to set up serial communication
 */
void sendMotionSerialData(bool birth_packet)
{
    //Open a JSON buffer and create a root object for the data transfer
    DyynamicJsonBuffer jsonBuffer(json_str_size_out);
    JsonObject& root = jsonBuffer.createObject();

    //Set the device ID
    root["id"] = 1;

    //For regular operation, send the robot's status
    if(!birth_packet)
    {
        //Indicate normal operations
        root["event"] = "feedback";

        //Make the data array
        JsonArray& dataArray = root.createNestedArray("data");
        dataArray["steer_ang"] = drivetrain.getAngle();
    }
    else
    {
        //Indicate normal operations
        root["event"] = "birth";

        //Make the data array
        JsonArray& dataArray = root.createNestedArray("data");
        dataArray["steer_ang"] = drivetrain.getAngle();
    }

    //Send data to the main board
    root.printTo(Serial);
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
