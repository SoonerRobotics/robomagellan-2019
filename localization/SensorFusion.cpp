#include "SensorFusion.h"

SensorFusion::SensorFusion(GPSModule gps, IMU imu) {
	this->imu = imu;
	this->gps = gps;

}

void SensorFusion::update() {
	//Check available sensors
	bool useGps = false;
	if (gps.available != 0)
		useGps = true;
	bool useIMU = imu.calibrated();

	//Set Prior State
	float prevLat = lat;
	float prevLon = longi;
	float prevHeading = heading;

	//Set Current State
	if (useGps) {
		lat = gps.getLat();
		longi = gps.getLong();
	}
	if(useIMU)
		heading = imu.getX();

}

void SensorFusion::print() {
  //Check available sensors
  bool useGps = false;
  if (gps.available != 0)
    useGps = true;
  bool useIMU = imu.calibrated();

  //Set Current State
  if (useGps) {
    Serial.print("Lat:");
    Serial.println(gps.getLat());
    Serial.print("Long:");
    Serial.println(gps.getLong());
  }
  if(useIMU)
    Serial.print("X:");
    Serial.println(imu.getX());
    Serial.print("Y:");
    Serial.println(imu.getY());
    Serial.print("Z:");
    Serial.println(imu.getZ());
}
