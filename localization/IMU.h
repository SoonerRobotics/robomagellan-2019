#ifndef IMU_H
#define IMU_H

//https://github.com/adafruit/Adafruit_BNO055
#include <IMU_BNO055.h>

//Code for using the BN055 GPS
/* This class doesn't automatically pull new data from sensor 
   for get X,Y,Z to ensure they are synced. To read the current 
   data into what XYZ pull from call read*/
class IMU {
public:
	void begin();
	bool connected();

	bool calibrated();
  void zero();

	float getOrientX();
	float getOrientY();
	float getOrientZ();
	float getAccelX();
	float getAccelY();
	float getAccelZ();

    float getVelocityX();
    float getVelocityY();

	void update();
private:
    //Velocity vector
    typedef struct velocity_t
    {
        float x;
        float y;
        float lat;
        float lon;
    } velocity;

    float dT; //time difference in update

	IMU_BNO055 bno;
	scr_sensors_event_t orientation; //the current orinetation
	scr_sensors_event_t acceleration; //the current acceleration
  float accel_offset_x = 0;
  float accel_offset_y = 0;
  float accel_offset_z = 0;
	scr_sensors_event_t prev_acceleration; //the acceleration one time step back
    velocity _vel;   //velocity vector

	void calibrate();
};
#endif
