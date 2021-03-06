#include "IMU.h"

void IMU::begin() {

	if (!bno.begin(bno.OPERATION_MODE_CONFIG))
	{
		/* There was a problem detecting the BNO055 ... check your connections */
		//throw new Exception("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"); no exceptions in arduino lul
		Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
	}
	calibrate();

  bno.setMode(bno.OPERATION_MODE_NDOF);

	//Use the external 32.768KHz crystal
	bno.setExtCrystalUse(true);
}

void IMU::calibrate() {
  adafruit_bno055_offsets_t configvals;

	configvals.accel_offset_x = 0;
	configvals.accel_offset_y = -1;
	configvals.accel_offset_z = -23;

	configvals.mag_offset_x = -1;
	configvals.mag_offset_y = 2;
	configvals.mag_offset_z = -1;

	configvals.gyro_offset_x = -105;
	configvals.gyro_offset_y = 90;
	configvals.gyro_offset_z = -32;

	configvals.accel_radius = 1000;
	configvals.mag_radius = 680;

	bno.setSensorOffsets(configvals);
}

bool IMU::connected() {
	return bno.begin();
}


bool IMU::calibrated() {

	uint8_t sys = 0;
	uint8_t gyro = 0;
	uint8_t accel = 0;
	uint8_t mag = 0;
	bno.getCalibration(&sys, &gyro, &accel, &mag);
  Serial.println("Calibs: ");
  Serial.println(sys);
  Serial.println(gyro);
  Serial.println(accel);
  Serial.println(mag);
	return (gyro == 3 && accel == 3 && mag == 3);
}

float IMU::getOrientX(){
    return event.orientation.x;
}

float IMU::getOrientY() {
	return event.orientation.y;
}

float IMU::getOrientZ() {
	return event.orientation.z;
}

imu::Vector<3> IMU::getAccel() {
  return bno.getVector(bno.VECTOR_ACCELEROMETER);
}


void IMU::update() {
	bno.getEvent(&event);
}
