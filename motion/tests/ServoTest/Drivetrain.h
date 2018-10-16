#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Arduino.h>
#include <RobotLib.h>
#include "RomaServo.h"

class Drivetrain
{
    public:
        Drivetrain();
        Drivetrain(Motor driveMotor, RomaServo servo);

        void begin(Motor driveMotor, RomaServo servo);

        void setPower(float power);
        void setTurn(float angle);
        
        float getTurnAngle();
        int   getRawTurnValue();

    private:
        Motor driveMotor;

        RomaServo turnServo;
};

#endif