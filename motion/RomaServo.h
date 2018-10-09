#ifndef ROMA_SERVO_H
#define ROMA_SERVO_H

#include <Arduino.h>
#include <RobotLib.h>

#define POT_MIDPOINT    512 //Midpoint of the analogRead
#define MAX_TURN_ANGLE  30  //Maximum servo turn angle in degrees

class RomaServo 
{
    public:
        RomaServo();
        RomaServo(Motor m, int potPin, float maxPower);

        void begin(Motor m, int potPin, float maxPower);

        void setPID(float kp, float ki, float kd);

        void writeToAngle(float angle);

    private:
        Motor servoMotor;
        AnalogDevice potentiometer;
        PIDController pidControl;

        float motorOutput;
        float maxMotorPower;

        float potAngle;

        void processPot();
};

#endif