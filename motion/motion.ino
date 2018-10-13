#include <Wire.h>
#include <RobotLib.h>
#include "MotionSetup.h"

void setup() {    
    motionSetup();
}

void loop() {

    //Either we haven't received our first packets from I2C
    //or we received that we are at our final destination.
    if (curData.curHeading == 0 && curData.destHeading == 0) {
        drivetrain.setPower(0);
        drivetrain.setTurn(0);
        return;
    }

    if (LHT < RHT - DEGREES_OFF_ALLOWED) { // Faster to head left

    } else if (RHT < LHT - DEGREES_OFF_ALLOWED) { // Faster to head right
        
    } else { // On target
        
    }

    delay(50);
}