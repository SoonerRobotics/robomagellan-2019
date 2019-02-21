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

void Drivetrain::disable()
{
	this->driveMotor.disableOutput();
	this->turnServo.disableOutput();
}

void Drivetrain::enable()
{
	this->driveMotor.enableOutput();
	this->turnServo.enableOutput();
}

float Drivetrain::getTurnAngle()
{
    return this->turnServo.getAngle();
}

int Drivetrain::getRawTurnValue()
{
    return this->turnServo.getRawAngle();
}
