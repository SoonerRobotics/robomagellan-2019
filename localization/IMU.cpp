#include "IMU.h"

void IMU::begin() {
	bno = Adafruit_BNO055(0X09);

	if (!bno.begin())
	{
		/* There was a problem detecting the BNO055 ... check your connections */
		//throw new Exception("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"); no exceptions in arduino lul
		Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
	}
	//Use the external 32.768KHz crystal
	bno.setExtCrystalUse(true);
}

bool IMU::connected() {
	return bno.begin();
}


bool IMU::magCalibrated() {

	uint8_t sys = 0;
	uint8_t gyro = 0;
	uint8_t accel = 0;
	uint8_t mag = 0;
	bno.getCalibration(&accel, &gyro, &accel, &mag);
	return (mag == 3);
}

float IMU::getX(){
    return event.orientation.x;
}

float IMU::getY() {
	return event.orientation.y;
}

float IMU::getZ() {
	return event.orientation.z;
}

void IMU::read() {
	bno.getEvent(&event);
}

adafruit_bno055_offsets_t IMU::getOffset() 
{
	adafruit_bno055_offsets_t offsets_type;
	bno.getSensorOffsets(offsets_type);
    return offsets_type;
}

void IMU::setOffset(const uint8_t* calibData) {
	bno.setSensorOffsets(calibData);
}

imu::Vector<3> IMU::accelVector() {
	return bno.getVector(bno.VECTOR_ACCELEROMETER);
}

imu::Vector<3> IMU::eulerVector() {
	return bno.getVector(bno.VECTOR_EULER);
}
