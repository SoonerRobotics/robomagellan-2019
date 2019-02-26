#ifndef ROMA_SERVO_H
#define ROMA_SERVO_H

#include <Arduino.h>
#include <RobotLib.h>
#include "MotionGlobals.h"

#define POT_MIN         301    //Min value of the analogRead
#define POT_MAX         733    //Max value of analogRead
#define POT_MIDPOINT    (float)((POT_MAX + POT_MIN) / 2.0f)
                                //Middle point of the analogRead

class RomaServo 
{
    public:
        RomaServo();
        RomaServo(Motor m, int potPin, float maxPower);

        void operator=(const RomaServo& servo);

        void begin(Motor m, int potPin, float maxPower);

        void setPID(float kp, float ki, float kd);

        void writeToAngle(float angle);
        void holdPosition();
		void disableOutput();
		void enableOutput();

        float getAngle();
        int getRawAngle();

    private:
        Motor servoMotor;
        AnalogDevice potentiometer;
        PIDController pidControl;

        float motorOutput;
        float maxMotorPower;

        float potAngle;
        int   rawAngle;

        void processPot();
};

#endif
