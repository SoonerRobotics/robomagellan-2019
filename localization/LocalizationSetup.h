#ifndef LOCALIZATION_SETUP_H
#define LOCALIZATION_SETUP_H

GPSModule gps(3, 4);

IMU imu0; //apparently the name imu already exists

void localizationSetup()
{
    imu0.begin();
}

#endif
