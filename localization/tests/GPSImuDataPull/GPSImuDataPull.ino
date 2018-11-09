#include "GPSModule.h"
#include "GPSQueue.h"
#include "IMU.h"
#include "LocalizationSetup.h"

void setup() {
    localizationSetup();
    Serial.print("Latitude, Longitude, Distance, Heading, Orient(x, y, z), Accel(x, y, z)");
}

void intellectualWait(unsigned long ms) {
    unsigned long startTime = millis();
    while (millis() - startTime < ms) {
        gps.update();
        imu0.update();
    }
}

void loop() {
    Serial.print(millis());
    Serial.print(", ");
    Serial.print(gps.getLat());
    Serial.print(", ");
    Serial.print(gps.getLong());
    Serial.print(", ");
  if (imu0.calibrated()) {

    Serial.print(queue.getDistToCur());
    Serial.print(", ");
    Serial.println(queue.getCurHeading());

    Serial.print(imu0.getOrientX());
    Serial.print(", ");
    Serial.print(imu0.getOrientY());
    Serial.print(", ");
    Serial.println(imu0.getOrientZ());

    imu::Vector<3> accel = imu0.getAccel();

    Serial.print(accel.x());
    Serial.print(", ");
    Serial.print(accel.y());
    Serial.print(", ");
    Serial.println(accel.z());
  }
  else {
    Serial.print("X");
    Serial.print(", ");
    Serial.println("X");

    Serial.print("X");
    Serial.print(", ");
    Serial.print("X");
    Serial.print(", ");
    Serial.println("X");

    imu::Vector<3> accel = imu0.getAccel();

    Serial.print("X");
    Serial.print(", ");
    Serial.print("X");
    Serial.print(", ");
    Serial.println("X");
 }
    
    intellectualWait(500);
}
