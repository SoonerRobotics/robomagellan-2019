#include "SensorFusion.h"

SensorFusion::SensorFusion(GPSModule gps, IMU imu0) {
	this->imu0 = imu0;
	this->gps = gps;

}

void SensorFusion::updateIMU() {
	//Check available sensors
	bool useGps = false;
	if (gps.available() != 0)
		useGps = true;
	bool useIMU = imu0.calibrated();

	//Set Prior State
	prevLat = lat;
	prevLon = lon;
	prevHeading = heading;

	//Set Current State
	if (useGps) {
		lat = gps.getLat();
		longi = gps.getLong();
	}
	if(useIMU)
		heading = imu0.getOrientX();

}

void SensorFusion::printIMU() {
    updateIMU();
    //Print out data, unfinished
 }
