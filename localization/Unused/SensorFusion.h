#include "GPSModule.h"
#include "IMU.h"

#ifndef SensorFusion_H
#define SensorFusion_H

class SensorFusion {
public:
	SensorFusion(GPSModule gps, IMU imu0);
  void printIMU();

private:
	int heading = 0;
	float lat = 0;
	float lon = 0;
	IMU imu0;
	GPSModule gps;
	void updateIMU();
  float prevLat = 9999;
  float prevLon = 9999;
  float prevHeading = 9999;
};
#endif
