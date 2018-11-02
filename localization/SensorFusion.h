#include "GPSModule.h"
#include "IMU.h"

#ifndef SensorFusion_H
#define SensorFusion_H

class SensorFusion {
public:
	SensorFusion(GPSModule gps, IMU imu);
  void print();

private:
	int heading = 0;
	float lat = 0;
	float longi = 0;
	IMU imu;
	GPSModule gps;
	void update();
};
#endif
