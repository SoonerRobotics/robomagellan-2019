#ifndef MOTION_SETUP_H
#define MOTION_SETUP_H

#include "MotionGlobals.h"
#include "Drivetrain.h"

Drivetrain drivetrain;

//Forward declare I2C Handler code
void sendData();
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
    Wire.begin(SLAVE_ADDRESS);

    // Initialize individual motors
    motor.begin(DRIVE_MOTOR_A, DRIVE_MOTOR_B, DRIVE_MOTOR_ENB);
    servo.begin(SERVO_MOTOR_A, SERVO_MOTOR_B, SERVO_MOTOR_ENB);

    // Fully set up the RomaServo
    romaServo.begin(servo, TURN_POT_PIN, MAX_TURN_POWER);

    // define callbacks for i2c communication
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);

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
// callback for received data
void receiveData(int byteCount)
{
    //Declare local variables
    int data;
    float motorOutput;

    //Get all available bytes from the i2c buffer
    while(Wire.available()) 
    {
        //Read i2c data
        data = Wire.read();

        //Output i2c debugging data
        if(IS_DEBUG)
        {
            Serial.print("data received: ");
            Serial.println(data);
        }

        //Set drivetrain power based on i2c data
        motorOutput = data / I2C_MAX;
        drivetrain.setPower(motorOutput);
    }
}

// callback for sending data
void sendData()
{
    //TODO: Add functionality for sending data
    Wire.write(0);
}

#endif