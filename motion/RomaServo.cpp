#include "RomaServo.h"

RomaServo::RomaServo()
{

}

RomaServo::RomaServo(Motor m, int potPin, float maxPower)
{
    this->servoMotor = m;
    this->potentiometer.update(potPin, INPUT);
    this->maxMotorPower = maxPower;
}

void RomaServo::operator=(const RomaServo& servo)
{
    this->servoMotor = servo.servoMotor;
    this->potentiometer = servo.potentiometer;
    this->maxMotorPower = servo.maxMotorPower;
    this->potAngle = servo.potAngle;
    this->pidControl = servo.pidControl;
}

void RomaServo::begin(Motor m, int potPin, float maxPower)
{
    this->servoMotor = m;
    this->potentiometer.update(potPin, INPUT);
    this->maxMotorPower = maxPower;
}

void RomaServo::setPID(float kp, float ki, float kd)
{
    pidControl.initialize(this->potAngle, kp, ki, kd);
    pidControl.setOutputRange(this->maxMotorPower, -this->maxMotorPower);
}

void RomaServo::writeToAngle(float angle)
{
    processPot();
    this->motorOutput = pidControl.getOutput(angle, this->potAngle);
    this->servoMotor.output(this->motorOutput);
}

/************************
    Private variables
*************************/
void RomaServo::processPot()
{
    this->potAngle = this->potentiometer.read();

    this->potAngle = ((this->potAngle - POT_MIDPOINT) / POT_MIDPOINT) * MAX_TURN_ANGLE;
}