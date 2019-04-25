#ifndef MOTION_SETUP_H
#define MOTION_SETUP_H

#include <ros.h>
#include <roma_msgs/motion_cmds.h>
#include <roma_msgs/motion_feedback.h>

#include <Wire.h>
#include <SPI.h>
#include "RF24.h"
#include "MotionGlobals.h"
#include "Drivetrain.h"

//Set up the ROS node for this code
ros::NodeHandle_<ArduinoHardware, 2, 2, 80, 105> motion_node;

//Full serial data packet
typedef struct DataPacket_u
{
    //GPS Location Stuff
    float power = 0;            //power to the drive motor
    float steeringAngle = 0;    //steering angle

} DataPacket;

//Declare systems
Drivetrain drivetrain;

//Most recent data from the raspberry pi
DataPacket curData;

//Radio control cutoff switch
RF24 radio(9, 10);

//Robot operation state
int robot_state;

//Forward Declare Functions as needed
void command_update(const roma_msgs::motion_cmds& command);
void sendMotionData();
void reverseRoutine();
void receive();


//ROS subscribers
//TODO: choose official topic (this should be good though)
ros::Subscriber<roma_msgs::motion_cmds> cmd_sub("/roma_motion/cmd", &command_update);

//ROS publishers
roma_msgs::motion_feedback feedback_msg;
ros::Publisher feedback_pub("/roma_motion/feedback", &feedback_msg);

//Radio configuration
byte addressesi[][6] = {"1Node","2Node"};

void motionSetup()
{
    //Declare local variables
    Motor motor;
    Motor servo;
    RomaServo romaServo;

	//Initialize ROS and pubs/subs
	motion_node.initNode();
	motion_node.subscribe(cmd_sub);
	motion_node.advertise(feedback_pub);

	//Setup the radio
	radio.begin();

	//Configure the radio
	radio.setPALevel(RF24_PA_HIGH);
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
	//drivetrain.disable();
	//robot_state = PAUSE_STATE;
}

/******************************************
             ROS Callbacks
******************************************/

//Callback for received data
void command_update(const roma_msgs::motion_cmds& command)
{
    curData.power           = command.power;
    curData.steeringAngle   = command.steer_ang;
	
	digitalWrite(13, HIGH);
	delay(100);
	digitalWrite(13, LOW);
	delay(100);
	digitalWrite(13, HIGH);
	delay(100);
	digitalWrite(13, LOW);
}

/**
 * Function that sends data to the main board.
 */
void sendMotionData()
{
	//Form the motion feedback message
    roma_msgs::motion_feedback feedback_data;
	feedback_data.steer_ang = drivetrain.getTurnAngle();
    
	//Publish the feedback data
	feedback_pub.publish(&feedback_data);
}

/**********************
      ROUTINES
 **********************/

/**
 * Routine to run when the robot needs to reverse away from an obstacle
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
 * Routine that is run when the robot receives a command from Syndrome's remote
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
