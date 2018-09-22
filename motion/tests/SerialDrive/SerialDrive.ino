#include "MotionSetup.h"

//Declare test variables
float power;
int pct;

void setup()
{
    Serial.begin(115200);

    //Initialize test vars
    power = 0.0f;
    pct = 0;

    motionSetup();
}

void loop()
{
    if(Serial.available() > 0)
    {
        pct = Serial.parseInt();
    }

    if(pct > 100)
    {
        pct = 100;
    }
    else if(pct < -100)
    {
        pct = -100;
    }

    power = (float)(pct) / 100.0f;

    drivetrain.setPower(power);

    delay(100);
}