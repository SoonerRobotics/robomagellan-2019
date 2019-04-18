#ifndef LOCALIZATION_SETUP_H
#define LOCALIZATION_SETUP_H

#include <Arduino.h>
#include "GPSModule.h"
#include "GPSQueue.h"
#include "IMU.h"

GPSModule gps(3, 4);
GPSQueue queue(&gps);

IMU imu0; //apparently imu already exists

void localizationSetup()
{
	//TODO: do we need this?
    //Serial.begin(9600);

    imu0.begin();

    queue.addPoint(35.210605, -97.443412); //a bit under Carson
}

#endif
