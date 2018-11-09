#ifndef IMU_H
#define IMU_H

//https://github.com/adafruit/Adafruit_BNO055
#include <Adafruit_BNO055.h>


//Code for using the BN055 GPS
/* This class doesn't automatically pull new data from sensor 
   for get X,Y,Z to ensure they are synced. To read the current 
   data into what XYZ pull from call read*/
class IMU {
public:
	void begin();
	bool connected();

	bool calibrated();
	
	float getOrientX();
	float getOrientY();
	float getOrientZ();

    imu::Vector<3> IMU::getAccel();

	void update();
private:
	Adafruit_BNO055 bno;
	sensors_event_t event;

	void calibrate();
};
#endif
