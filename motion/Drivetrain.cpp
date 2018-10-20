#include "Drivetrain.h"

Drivetrain::Drivetrain()
{
}

Drivetrain::Drivetrain(Motor driveMotor, RomaServo servo)
{
    this->driveMotor = driveMotor;
    this->turnServo = servo;
}

void Drivetrain::begin(Motor driveMotor, RomaServo servo)
{
    this->driveMotor = driveMotor;
    this->turnServo = servo;
}

void Drivetrain::setPower(float power)
{
    this->driveMotor.output(power);
}

void Drivetrain::setTurn(float angle)
{
    this->turnServo.writeToAngle(angle);
}

void Drivetrain::holdTurnPosition()
{
    this->turnServo.holdPosition();
}

float Drivetrain::getTurnAngle()
{
    return this->turnServo.getAngle();
}

int Drivetrain::getRawTurnValue()
{
    return this->turnServo.getRawAngle();
}