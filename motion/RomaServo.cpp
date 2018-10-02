#include "RomaServo.h"

RomaServo::RomaServo()
{

}

RomaServo::RomaServo(Motor m, int potPin, float maxPower)
{
    this->servoMotor = m;
    this->potentiometer.begin(potPin, INPUT);
    this->maxMotorPower = maxPower;
}

void RomaServo::begin(Motor m, int potPin, float maxPower)
{
    this->servoMotor = m;
    this->potentiometer.begin(potPin, INPUT);
    this->maxMotorPower = maxPower;
}

void RomaServo::setPID(float kp, float ki, float kd)
{
    pidControl.initialize(this->potAngle, kp, ki, kd);
    pidControl.setOutputRange(this->motorSpeed, -this->motorSpeed);
}

void RomaServo::writeToAngle(float angle)
{
    processPot();
    this->motorPower = pidControl.getOutput(angle, this->potAngle);
    this->servoMotor.output(this->motorPower);
}

/************************
    Private variables
*************************/
void RomaServo::processPot()
{
    this->potAngle = this->potentiometer.read();

    this->potAngle = ((this->potAngle - POT_MIDPOINT) / POT_MIDPOINT) * MAX_TURN_ANGLE;
}