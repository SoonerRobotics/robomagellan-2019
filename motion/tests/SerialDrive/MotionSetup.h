#ifndef MOTION_SETUP_H
#define MOTION_SETUP_H

#include "MotionGlobals.h"
#include "Drivetrain.h"

Drivetrain drivetrain;

void motionSetup()
{
    Motor tmpMotor;

    //Initialize Drivetrain
    tmpMotor.begin(DRIVE_MOTOR_PIN_A, DRIVE_MOTOR_PIN_A);
    drivetrain.begin(tmpMotor, TURN_SERVO_PIN);
}


#endif