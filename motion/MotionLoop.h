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

//Servo timing variables
unsigned long servoTime = 0;
unsigned long lastServoUpdate = 0;

//Declare system loops
void drivetrainLoop(float power);
void servoLoop(float servoAngle);

void motionLoop()
{
    currentTime = millis();

    /*
    //Drivetrain update loop
    if((currentTime - lastDrivetrainUpdate) >= DT_UPDATE_EPS
    || lastDrivetrainUpdate == 0)
    {
        drivetrainLoop();
    }

    //Servo update loop
    if((currentTime - lastServoUpdate) >= SERVO_UPDATE_EPS
    || lastServoUpdate == 0)
    {
        servoLoop();
    }*/

    /* Drivetrain Update */
    drivetrainLoop(0.22);

    /* Servo Update */
    if (newestArdRead.nearCone)
    {
        //Use the error calculations from newestPiRead
        //Also need to initiate read but idk how to even start that

        if(newestPiRead.error > (0 + DEGREES_OFF_ALLOWED))
        {
            servoLoop(-10);
        }
        else if (newestPiRead.error < (0 - DEGREES_OFF_ALLOWED))
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

        // Faster to head left
        if (LHT < RHT - DEGREES_OFF_ALLOWED)
        {
            servoLoop(-10);
        }
        // Faster to head right
        else if (RHT < LHT - DEGREES_OFF_ALLOWED)
        {
            servoLoop(10);
        }
        // On target
        else
        {
            servoLoop(0);
        }
    }
}

/**********************
    SYSTEM LOOPS
**********************/
void drivetrainLoop(float power)
{
    if (curData.curHeading == 0 && curData.destHeading == 0)
    {
        drivetrain.setPower(0);
        drivetrain.setTurn(0);
        return;
    }

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

/**********************
      ROUTINES
 **********************/

/**
 * Routine to run when the robot needs to revese away from an obsticle
 */
void reverseRoutine()
{

    //Reverse the motor
    drivetrain.setPower(-0.22);
    
    //Wait for 1 second
    intellectualWait(1000);

    //Stop the reverse to avoid anything silly
    drivetrain.setPower(0);
}
#endif