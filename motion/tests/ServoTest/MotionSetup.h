#ifndef MOTION_SETUP_H
#define MOTION_SETUP_H

#include <Wire.h>
#include "MotionGlobals.h"
#include "Drivetrain.h"

typedef struct DataPacket {
    float curHeading;
    float destHeading;
} DataPacket;

//Declare systems
Drivetrain drivetrain;

DataPacket curData;
float LHT;
float RHT;

//Forward declare I2C Handler code
//void sendData();
void receiveData(int byteCount);

void motionSetup()
{
    //Declare local variables
    Motor motor;
    Motor servo;
    RomaServo romaServo;

    // start serial for output
    if(IS_DEBUG)
    {
        Serial.begin(9600); 
    }

    // initialize i2c as slave
    Wire.begin(MOTION_ADDR);

    // Initialize individual motors
    motor.begin(DRIVE_MOTOR_A, DRIVE_MOTOR_B, DRIVE_MOTOR_ENB);
    servo.begin(SERVO_MOTOR_A, SERVO_MOTOR_B, SERVO_MOTOR_ENB);

    // Fully set up the RomaServo
    romaServo.begin(servo, TURN_POT_PIN, MAX_TURN_POWER);
    romaServo.setPID(SERVO_KP, SERVO_KI, SERVO_KD);

    // define callbacks for i2c communication
    Wire.onReceive(receiveData);
    //Wire.onRequest(sendData);

    // Debug ready output
    if(IS_DEBUG)
    {
        Serial.println("Ready!");
    }

    //Initialize Drivetrain
    drivetrain.begin(motor, romaServo);
}


/******************************************
                I2C Handler
******************************************/

template <typename T>
unsigned int I2C_readAnything(T& value){
    byte * p = (byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
        *p++ = Wire.read();
    return i;
}

// callback for received data
void receiveData(int byteCount)
{
    if (byteCount >= (sizeof(DataPacket))) {
        I2C_readAnything(curData);

        float diff = curData.curHeading - curData.destHeading;

        LHT = (diff) < 0 ? diff + 360 : diff; //Degrees required to move to heading turning left
        RHT = -LHT + 360; //Degrees required to move to heading turning turn
    }
}

#endif
