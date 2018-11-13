#include "SensorFusion.h"

SensorFusion::SensorFusion(GPSModule gps, IMU imu) {
	this->imu = imu;
	this->gps = gps;

}

void SensorFusion::updateIMU() {
	//Check available sensors
	bool useGps = false;
	if (gps.available != 0)
		useGps = true;
	bool useIMU = imu.calibrated();

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
		heading = imu.getX();

}

void SensorFusion::printIMU() {
    updateIMU();
    //Print out data, unfinished
 }
