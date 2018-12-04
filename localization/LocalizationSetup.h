#ifndef LOCALIZATION_SETUP_H
#define LOCALIZATION_SETUP_H

GPSModule gps(3, 4);

IMU imu0; //apparently the name imu already exists

void localizationSetup()
{
    Serial.begin(115200);

    imu0.begin();
}

#endif
