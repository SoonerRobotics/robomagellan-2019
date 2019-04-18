#include "RomaServo.h"

RomaServo::RomaServo()
{
    this->rawAngle = 0;
    this->potAngle = 0;
    this->motorOutput = 0;
}

RomaServo::RomaServo(Motor m, int potPin, float maxPower)
{
    this->servoMotor = m;
    pinMode(potPin, INPUT);
    this->maxMotorPower = maxPower;
    this->rawAngle = 0;
    this->potAngle = 0;
    this->motorOutput = 0;
}

void RomaServo::operator=(const RomaServo& servo)
{
    this->servoMotor = servo.servoMotor;
	pinMode(TURN_POT_PIN, INPUT);
    this->maxMotorPower = servo.maxMotorPower;
    this->potAngle = servo.potAngle;
    this->pidControl = servo.pidControl;
}

void RomaServo::begin(Motor m, int potPin, float maxPower)
{
    this->servoMotor = m;
    pinMode(potPin, INPUT);
    this->maxMotorPower = maxPower;
}

void RomaServo::setPID(float kp, float ki, float kd)
{
    processPot();
    pidControl.initialize(this->potAngle, kp, ki, kd);
    pidControl.setOutputRange(this->maxMotorPower, -this->maxMotorPower);
}

void RomaServo::holdPosition()
{
    this->servoMotor.outputBool(0);
}

void RomaServo::writeToAngle(float angle)
{
    processPot();
    this->motorOutput = pidControl.getOutput(angle, this->potAngle);
    this->servoMotor.output(this->motorOutput);
}

float RomaServo::getAngle()
{
    processPot();
    return this->potAngle;
}

int RomaServo::getRawAngle()
{
    processPot();
    return this->rawAngle;
}

/************************
    Private variables
*************************/
void RomaServo::processPot()
{
    this->rawAngle = analogRead(TURN_POT_PIN);//this->potentiometer.read();
    this->potAngle = (((float)(this->rawAngle) - POT_MIDPOINT) / (POT_MAX - POT_MIDPOINT)) * MAX_TURN_ANGLE;
}