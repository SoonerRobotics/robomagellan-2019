#include <Wire.h>
#include <RobotLib.h>
#include "MotionSetup.h"
#include "MotionLoop.h"


void setup() 
{    
  pinMode(13, OUTPUT);
  motionSetup();
}

void loop() 
{
  motionLoop();
}

