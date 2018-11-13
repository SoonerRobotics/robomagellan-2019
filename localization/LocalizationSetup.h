#ifndef LOCALIZATION_SETUP_H
#define LOCALIZATION_SETUP_H

GPSModule gps(3, 4);
GPSQueue queue(&gps);

IMU imu0; //apparently the name imu already exists

void localizationSetup()
{
    Serial.begin(9600);

    imu0.begin();

    queue.addPoint(35.210605, -97.443412); //a bit under Carson
}

#endif
