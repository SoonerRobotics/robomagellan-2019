#include "GPSModule.h"
#include "GPSQueue.h"
#include "IMU.h"
#include "LocalizationSetup.h"

void setup() {
    localizationSetup();
}

void intellectualWait(unsigned long ms) {
    unsigned long startTime = millis();
    while (millis() - startTime < ms) {
        gps.update();
        imu0.update();
    }
}

void loop() {
    Serial.print("GPS coord lat, long: ");
    Serial.print(gps.getLat());
    Serial.print(", ");
    Serial.print(gps.getLong());
    
  if (imu0.calibrated()) {

    Serial.print("Distance, Heading: ");
    Serial.print(queue.getDistToCur());
    Serial.print(", ");
    Serial.println(queue.getCurHeading());

    Serial.print("Orient x, y, z: ");
    Serial.print(imu0.getOrientX());
    Serial.print(", ");
    Serial.print(imu0.getOrientY());
    Serial.print(", ");
    Serial.println(imu0.getOrientZ());

    Serial.print("Accel x, y, z: ");
    Serial.print(imu0.getAccelX());
    Serial.print(", ");
    Serial.print(imu0.getAccelY());
    Serial.print(", ");
    Serial.println(imu0.getAccelZ());
  }
    
    intellectualWait(500);
}
