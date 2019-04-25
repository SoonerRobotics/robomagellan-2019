#ifndef LOCALIZATION_SETUP_H
#define LOCALIZATION_SETUP_H

GPSModule gps(3, 4);

IMU imu0; //apparently the name imu already exists

long last_interrupt;
long cur_time;
float deltaT;

float velocity_samples[NUM_SAMPLES];
volatile int vel_idx;

void localizationSetup()
{
	//TODO: do we need this?
    //Serial.begin(9600);

	//Set up the IMU
    imu0.begin();

	//Reset the interrupt timers
	last_interrupt = micros();
	vel_idx = 0;
}


#endif
