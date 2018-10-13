#include "LocalizationSetup.h"

void setup() 
{
    localizationSetup();
}

void intellectualWait(unsigned long ms) 
{
    unsigned long startTime = millis();
    while (millis() - startTime < ms) 
    {
        gps.update();
        imu0.read();
    }
}

void loop() 
{
    //Output the debug data for GPS coordinates
    if(IS_DEBUG)
    {
        Serial.print("Distance | Heading");
        Serial.print(queue.getDistToCur());
        Serial.print(" | ");
        Serial.println(queue.getCurHeading());

        Serial.print("IMU x, y, z");
        Serial.print(imu0.getX());
        Serial.print(", ");
        Serial.print(imu0.getY());
        Serial.print(", ");
        Serial.println(imu0.getZ());
    }

    // Wait intellectually
    intellectualWait(500);
}
