#ifndef MOTION_SETUP_H
#define MOTION_SETUP_H

#include <Wire.h>
#include "MotionGlobals.h"
#include "Drivetrain.h"

//IDs for external I2C communication
#define PI_ID = 0;
#define LOC_ID = 1;

//Pin with limit switch for cone contact on it
#define LIMIT_PIN = 9999;

//Format for data sent from the raspberry pi
typedef struct PiDataPacket_s
{
    float error;    //error between center screen and percieved cone
} PiDataPacket;

//Format for data sent from the localization nano
typedef struct LocationDataPacket_s
{
    bool nearCone;      //TRUE if near cone, FALSE if notF
    float curHeading;   //current robot heading
    float destHeading;  //target robot heading

} LocationDataPacket;

//Full I2C data packet
typedef struct DataPacket_u {
    short ID; //ID of device so we know who's sending it
    
    //Data packet from either the localization 
    typedef union Packet_t
    {
        LocationDataPacket locPack; //Data from the localization device
        PiDataPacket       piPack;  //Data from the raspberry pi (opencv, obstacle detection)
    } Packet;

} DataPacket;

//Declare systems
Drivetrain drivetrain;

//Contains the most recent reads from each computer
DataPacket newestPiRead;
DataPacket newestLocRead;

//Probably replace  curData with newestArdRead in most cases atm
DataPacket curData;

float LHT;
float RHT;

//Forward declare I2C Handler code
//void sendData();
void receiveData(int byteCount);

void motionSetup()
{
    readsSinceLastPiRead = 0;
    readsSinceLastArdRead = 0;
    //Declare local variables
    Motor motor;
    Motor servo;
    RomaServo romaServo;

    // start serial for output
    if (IS_DEBUG)
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
    if (IS_DEBUG)
    {
        Serial.println("Ready!");
    }

    //Initialize Drivetrain
    drivetrain.begin(motor, romaServo);

    //attach an inturrupt to the limit switch to reverse when pressed
    attachInterrupt(LIMIT_PIN, reverseRoutine, RISING);
}

/******************************************
                I2C Handler
******************************************/

template <typename T>
unsigned int I2C_readAnything(T &value)
{
    byte *p = (byte *)&value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
        *p++ = Wire.read();
    return i;
}

// callback for received data
void receiveData(int byteCount)
{

    //It's possible this computation needs to be done elsewhere 
    //for accomidating different types of dataPackets
    if (byteCount >= (sizeof(DataPacket)))
    {
        I2C_readAnything(curData);
        //If we're Receiving data from the pi
        if (curData.ID == PI_ID)
        {
            newestPiRead = curData;
        }
        else
        {
            newestLocRead = curData;
            float diff = curData.curHeading - curData.destHeading;

            LHT = (diff) < 0 ? diff + 360 : diff; //Degrees required to move to heading turning left
            RHT = -LHT + 360;                     //Degrees required to move to heading turning turn
        }
    }
}

#endif
