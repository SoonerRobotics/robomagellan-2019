#include "MotionSetup.h"

int state = 0;

void setup()
{
    motionSetup();
}

void loop()
{
    //Serial.println("Turning!");
    if(state == 0)
    {
        drivetrain.setTurn(-MAX_TURN_ANGLE);
    }
    else if(state == 1)
    {
        drivetrain.setTurn(0);
    }
    else
    {
        state = -1;
        drivetrain.setTurn(MAX_TURN_ANGLE);
    }
    
}