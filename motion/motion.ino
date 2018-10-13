#include <Wire.h>
#include <RobotLib.h>
#include "MotionSetup.h"

void setup() {
    //LED Test code
    pinMode(13, OUTPUT);
    
    motionSetup();
}

void loop() 
{
    delay(100);
}