#ifndef MOTION_LOOP_H
#define MOTION_LOOP_H

#include "MotionSetup.h"

//General state constants
#define IDLE 0

//Servo state constants
#define SERVO_UPDATE 1
#define SERVO_MOVE 2

//State tracking variables
int servoState = IDLE;

//General Timing variables
unsigned long currentTime;

//Drivetrain timing variables
unsigned long lastDrivetrainUpdate;
unsigned long lastSerialUpdate;

//Servo timing variables
unsigned long servoTime = 0;
unsigned long lastServoUpdate = 0;

//Declare system loops
void drivetrainLoop(float power);
void servoLoop(float servoAngle);
void rosLoop();

void motionLoop()
{
    /* TIME UPADTE */
    currentTime = millis();

    //Check if we're near the next cone
	if (curData.nearCone)
	{
		/* DRIVETRAIN UPADTE */
		drivetrainLoop(DEFAULT_POWER / 2);

			if (curData.canSeeCone)
			{
				//We can see the cone
				if (curData.opencv_error > (0 + OPENCV_ALLOWED_ERROR))
				{
					//I'm not sure what data opencv_error contains but this should probably be not 10 and some sort of open cv calculation
					servoLoop(-10);
				}
				else if (curData.opencv_error < (0 - OPENCV_ALLOWED_ERROR))
				{
					servoLoop(10);
				}
				else
				{
					servoLoop(0);
				}
			}
			else
			{
				//We have passed the cone and should turn around, Justin has a more complicated
				// algorithmic idea for this, until then hopefully 
				// turning 45 degrees we can see the cone again in a cycle or two
				servoLoop(45);
			}
	}
    else
    {
        /* DRIVETRAIN UPADTE */
        drivetrainLoop(curData.power);

        //servoLoop(curData.steeringAngle);
    }

    //Send steering angle feedback data
    rosLoop();

	//Update ROS callbacks
	motion_node.spinOnce();
}

/**********************
    SYSTEM LOOPS
**********************/
void drivetrainLoop(float power)
{
    drivetrain.setPower(power);
}

void servoLoop(float servoAngle)
{
    switch (servoState)
    {
    case IDLE:
        //Keep current position
        drivetrain.holdTurnPosition();

        //Check to see if the servo needs to move
        if (abs(drivetrain.getTurnAngle() - servoAngle) > TURN_TOLERANCE)
        {
            servoState = SERVO_UPDATE;
        }

        break;

    case SERVO_UPDATE:
    case SERVO_MOVE:
        //Start the timer for servo timeouts.
        if (servoState == SERVO_UPDATE)
        {
            servoTime = millis();
            servoState = SERVO_MOVE;
        }

        //Set the servo turn angle
        drivetrain.setTurn(servoAngle);

        //Turn off the servo after an amount of time has passed
        if ((millis() - servoTime) > SERVO_MOVE_TIMEOUT || abs(drivetrain.getTurnAngle() - servoAngle) <= TURN_TOLERANCE)
        {
            servoState = IDLE;
            drivetrain.holdTurnPosition();
        }

        break;

    default:
        servoState = IDLE;
        break;
    }
}

/**
 * ROS topic update loop for steering angle feedback. Runs at a timed rate
 */
void rosLoop()
{
    if((currentTime - lastSerialUpdate) > (1000 / SERIAL_UPDATE_RATE))
    {
		lastSerialUpdate = currentTime;
        sendMotionData();
    }
}

#endif