#ifndef ROMA_SERVO_H
#define ROMA_SERVO_H

#include <Arduino.h>
#include <RobotLib.h>

class RomaServo 
{
    public:
        RomaServo();
        RomaServo(Motor m, int potPin, float speed);

        void begin(Motor m, int potPin, float speed);

        void writeToAngle(float angle);

    private:
        Motor servoMotor;
        AnalogDevice potentiometer;
        float motorSpeed;
};

#endif