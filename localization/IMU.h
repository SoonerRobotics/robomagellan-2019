#ifndef IMU
#define IMU

//https://github.com/adafruit/Adafruit_BNO055
#include <Adafruit_BNO055>


//Code for using the BN055 GPS
/* This class doesn't automatically pull new data from sensor 
   for get X,Y,Z to ensure they are synced. To read the current 
   data into what XYZ pull from call read*/
class IMU {
public:
	IMU();
	bool connected();
	bool calibrated();
	float getX();
	float getY();
	float getZ();
	void read() :
    adafruit_bno055_offsets_t getOffset(); 
private:
	Adafruit_BNO055 bno;
	sensors_event_t event;
};
#endif