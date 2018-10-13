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
        Serial.print("Location: ");
        Serial.print(gps.getLat());

        Serial.print(", ");
        Serial.println(gps.getLong());

        Serial.print("Distance: ");
        Serial.print(queue.getDistToCur());
        Serial.print(" Heading: ");
        Serial.println(queue.getCurHeading());

        Serial.print("Is calibrated? ");
        Serial.println(imu0.magCalibrated() ? "Yes" : "No");

        Serial.print("IMU x, y, z: ");
        Serial.print(imu0.getX());
        Serial.print(", ");
        Serial.print(imu0.getY());
        Serial.print(", ");
        Serial.println(imu0.getZ());
    }

    DataPacket packet;
    packet.curHeading = imu0.getX();
    packet.destHeading = queue.getCurHeading();

    Wire.beginTransmission(MOTION_ADDR);
    I2C_writeAnything(packet);
    Wire.endTransmission();

    // Wait intellectually
    intellectualWait(500);
}
