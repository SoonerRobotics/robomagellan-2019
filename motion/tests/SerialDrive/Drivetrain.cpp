#include "Drivetrain.h"

Drivetrain::Drivetrain()
{
}

Drivetrain::Drivetrain(Motor driveMotor, int turnServoPin)
{
    this->driveMotor = driveMotor;
    this->turnServo.attach(turnServoPin);
}

void Drivetrain::begin(Motor driveMotor, int turnServoPin)
{
    this->driveMotor = driveMotor;
    this->turnServo.attach(turnServoPin);
}

void Drivetrain::setPower(float power)
{
    this->driveMotor.output2(power);
}

void Drivetrain::setTurn(float angle)
{
    this->turnServo.write(angle);
}