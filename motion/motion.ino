#include <Wire.h>
#include <RobotLib.h>
#include "MotionSetup.h"
#include "MotionLoop.h"


void setup() 
{    
  	motionSetup();
}

void loop() 
{
	//If the robot done got kilt, reset it if the raspberry pi says to
	if(robot_state == KILLED_STATE)
	{
		//Reset
		if(digitalRead(A1) == LOW)
		{
			reset_board();
		}
	}
	//Normal operation
	else
	{
		motionLoop();
	}
}

