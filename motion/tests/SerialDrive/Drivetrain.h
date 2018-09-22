#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Arduino.h>
#include <RobotLib.h>
#include <Servo.h>

class Drivetrain
{
    public:
        Drivetrain();
        Drivetrain(Motor driveMotor, int turnServoPin);

        void begin(Motor driveMotor, int turnServoPin);

        void setPower(float power);
        void setTurn(float angle);

    private:
        Motor driveMotor;

        Servo turnServo;
};

#endif