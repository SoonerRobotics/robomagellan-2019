#include "MotionSetup.h"
#include "MotionLoop.h"
int state = 0;

void setup()
{
    motionSetup();
}

void loop()
{
    servoLoop(); 
}