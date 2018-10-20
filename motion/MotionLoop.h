#ifndef MOTION_LOOP_H
#define MOTION_LOOP_H

//General state constants
#define IDLE 0

//Servo state constants
#define SERVO_UPDATE 1
#define SERVO_MOVE   2

//DELETE THESE EVENTUALLY
int testInt = 0;


//State tracking variables
int servoState = IDLE;

//General Timing variables
unsigned long currentTime;

//Drivetrain timing variables
unsigned long lastDrivetrainUpdate;

//Servo timing variables
unsigned long servoTime       = 0;
unsigned long lastServoUpdate = 0;

//Forward Declare system loops
void drivetrainLoop();
void servoLoop();

//Forward declare data updates
float getServoTarget();

void motionLoop()
{
    currentTime = millis();

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
    }
}

/**********************
    SYSTEM LOOPS
**********************/
void drivetrainLoop()
{
    
    //TODO: make a real loop for the drivetrain
    if(testInt == 0)
    {
        drivetrain.setPower(-0.1625f);
    }
    else if(testInt == 1)
    {
        drivetrain.setPower(-0.1875f);
    }
    else if(testInt == 2)
    {
        drivetrain.setPower(-0.2f);
    }
    else if(testInt == 3)
    {
        drivetrain.setPower(-0.25f);
    }
    else if(testInt == 4)
    {
        drivetrain.setPower(-0.2f);
    }
    else
    {
        drivetrain.setPower(-0.1625f);
    }
}


void servoLoop()
{
    float servoAngle = getServoTarget();
    Serial.print(servoAngle);
    Serial.print("\t");
    Serial.println(drivetrain.getTurnAngle());
    switch(servoState)
    {
        case IDLE:
            //Keep current position
            drivetrain.holdTurnPosition();

            //Check to see if the servo needs to move
            if(abs(drivetrain.getTurnAngle() - servoAngle) > TURN_TOLERANCE)
            {
                servoState = SERVO_UPDATE;
            }
            
            break;

        case SERVO_UPDATE:
        case SERVO_MOVE:
            //Start the timer for servo timeouts.
            if(servoState == SERVO_UPDATE)
            {
                servoTime = millis();
                servoState = SERVO_MOVE;
            }

            //Set the servo turn angle
            drivetrain.setTurn(servoAngle);

            //Turn off the servo after an amount of time has passed
            if((millis() - servoTime) > SERVO_MOVE_TIMEOUT
            || abs(drivetrain.getTurnAngle() - servoAngle) <= TURN_TOLERANCE)
            {
                servoState = IDLE;
                drivetrain.holdTurnPosition();
                testInt++;
                if(testInt == 4)
                {
                    testInt = 0;
                }

                delay(4000);
            }

            break;
        
        default:
            servoState = IDLE;  
            break;
    }
}


/**********************
      DATA LOOPS
**********************/

float getServoTarget()
{
    return 30.0f;
    
    //TODO: calculate servo angle from position data
    if(testInt == 0)
    {
        return 30.0f;
    }
    else if(testInt == 1)
    {
        return 30.0f;
    }
    else if(testInt == 2)
    {
        return 30.0f;
    }
    else if(testInt == 3)
    {
        return 30.0f;
    }
    
}

#endif