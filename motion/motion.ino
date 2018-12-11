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
  motionLoop();
}

