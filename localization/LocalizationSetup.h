#ifndef LOCALIZATION_SETUP_H
#define LOCALIZATION_SETUP_H

#include "GPSModule.h"
#include "GPSQueue.h"
#include "IMU.h"
#include "LocalizationGlobals.h"

GPSModule gps(GPS_RX, GPS_TX);
GPSQueue queue(&gps);

IMU imu0; //apparently imu already exists

// Setup the localization board
void localizationSetup()
{
    if(IS_DEBUG)
    {
        Serial.begin(9600);
    }

    //Add GPS points to the test queue for now
    //TODO: Add these points over I2C from raspberry pi
    queue.addPoint(35.210605, -97.443412); //a bit under Carson
}

#endif