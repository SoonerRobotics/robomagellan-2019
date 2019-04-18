#include "Drivetrain.h"
#define minservoangle = 0
#define maxservoangle = 180
#define minsteeringangle = -35
#define maxsteeringangle = 35

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
	num = angle + minsteeringangle;
	den = maxsteeringangle - minsteeringangle;
	servorange = maxservoangle - minservoangle;
	
	rat = num / den;

	desired = rat * servorange + minservoangle;
	
	this->turnServo.write(desired);
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
