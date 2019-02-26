#ifndef MOTION_SETUP_H
#define MOTION_SETUP_H

#include <Wire.h>
#include <SPI.h>
#include "RF24.h"
#include "MotionGlobals.h"
#include "Drivetrain.h"
#include "ArduinoJson.h"

//Full serial data packet
typedef struct DataPacket_u
{
    //GPS Location Stuff
    bool nearCone;          //true if near cone, false if not
    float power;            //power to the drive motor
    float steeringAngle;    //steering angle

    //OpenCV Stuff
    float opencv_error;     //error between center screen and percieved cone
    bool canSeeCone;        //tells if the cone is in the viewport of the camera
} DataPacket;

//Declare systems
Drivetrain drivetrain;

//Most recent data from the raspberry pi
DataPacket curData;

//Radio control cutoff switch
RF24 radio(9, 10);

//Robot operation state
int robot_state;

//Size of the data strings
const int json_str_size_in = NUM_JSON_VALUES_IN;
const int json_str_size_out = NUM_JSON_VALUES_OUT;

//Forward Declare Functions as needed
void sendMotionSerialData(bool birth_packet);
void reverseRoutine();
void receive();


//Radio configuration
byte addressesi[][6] = {"1Node","2Node"};

void motionSetup()
{
    //Declare local variables
    Motor motor;
    Motor servo;
    RomaServo romaServo;

    //Start serial for input
    //Note: this baud rate must be standard across devices
    Serial.begin(STD_BAUD_RATE);

	//Setup the radio
	radio.begin();

	//Configure the radio
	radio.setPALevel(RF24_PA_LOW);
	radio.maskIRQ(1,1,0);
	radio.openWritingPipe(addressesi[0]);
	radio.openReadingPipe(0,addressesi[1]);
	radio.startListening();

	//Attach the interrupt for radio receive
	attachInterrupt(0, receive, FALLING);

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

	//Disable the drivetrain and set the operation to paused
	drivetrain.disable();
	robot_state = PAUSE_STATE;

    //Wait until the raspberry pi has booted up
    while(Serial.peek() == -1)
    { 
        //Send messsages into the void
        sendMotionSerialData(true);
        delay(500); 
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
    DynamicJsonBuffer jsonBuffer(json_str_size_in);
    
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
    if(root.success())
    {
        curData.nearCone        = root["data"]["gps_near_cone"].as<bool>();
        curData.power           = root["data"]["traj_power"].as<float>();
        curData.steeringAngle   = root["data"]["steer_ang"].as<float>();
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
    DynamicJsonBuffer jsonBuffer(json_str_size_out);
    JsonObject& root = jsonBuffer.createObject();

    //Set the device ID
    root["id"] = MOTION_DEVICE_ID;

    //For regular operation, send the robot's status
    if(!birth_packet)
    {
        //Indicate normal operations
        root["event"] = "feedback";

        //Make the data array
        JsonObject& dataArray = root.createNestedObject("data");
        dataArray["steer_ang"] = drivetrain.getTurnAngle();
    }
    else
    {
        //Indicate normal operations
        root["event"] = "birth";

        //Make the data array
        JsonObject& dataArray = root.createNestedObject("data");
        dataArray["steer_ang"] = drivetrain.getTurnAngle();
    }

    //Send data to the main board
    root.printTo(Serial);
    Serial.write("\n");
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


/**
 * 
 */
void receive()
{
	//Message to read over the air
	unsigned long message;

	//If the radio has info for us...
	if(radio.available()) 
	{
		//Read the message
		while(radio.available()) 
		{
			radio.read(&message, sizeof(unsigned long));
		}

		//Send confirmation of message
		radio.stopListening();
		radio.write(&message, sizeof(unsigned long));
		radio.startListening();

		//If a kill message is sent, disable movement and end the program
		if(message == MSG_KILL) 
		{
			//Disable the drivetrain
			drivetrain.disable();

			//Run an infinite loop
			while(true){}
		}
		//If a start message is sent, start the robot
		else if(message == MSG_START) 
		{
			drivetrain.enable();
			robot_state = RUN_STATE;
		}
		//If the message is a pause message, toggle run state
		else if(message == MSG_PAUSE) 
		{
			if(robot_state == RUN_STATE) 
			{
				drivetrain.disable();
				robot_state = PAUSE_STATE;
			}
			else if(robot_state == PAUSE_STATE) 
			{
				drivetrain.enable();
				robot_state = RUN_STATE;
			}
		}
	}
}

#endif
