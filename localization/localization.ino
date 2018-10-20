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

static void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
}

void loop() 
{
    //Output the debug data for GPS coordinates
    if(IS_DEBUG)
    {
        Serial.print("Location: ");
        print_float(gps.getLat(), 1000, 8, 6);

        Serial.print(", ");
        print_float(gps.getLong(), 1000, 8, 6);

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

    /* Uncomment this code when I2C is actually connected, ty

    if (gps.getLat() > 90 || gps.getLong() > 90) { //GPS Hasn't found fix yet
        intellectualWait(500);
        return;
    }

    DataPacket packet;

    if (queue.getDistToCur() < 5) {
        if (queue.hasNext()) {
            queue.getNext();
            packet.curHeading = imu0.getX();
            packet.destHeading = queue.getCurHeading();
        } else {
            packet.curHeading = 0;
            packet.destHeading = 0;
        }
    } else {
        packet.curHeading = imu0.getX();
        packet.destHeading = queue.getCurHeading();
    }

    Wire.beginTransmission(MOTION_ADDR);
    I2C_writeAnything(packet);
    Wire.endTransmission();

    */

    // Wait intellectually
    intellectualWait(500);
}
