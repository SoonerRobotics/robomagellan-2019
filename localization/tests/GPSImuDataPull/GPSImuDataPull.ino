#include "GPSModule.h"
#include "GPSQueue.h"
#include "IMU.h"
#include "LocalizationSetup.h"

#define VERBOSITY 0

void setup() {
    localizationSetup();

    intellectualWait(10000);

    imu0.zero();
}

void intellectualWait(unsigned long ms) {
    unsigned long startTime = millis();
    while (millis() - startTime < ms) {
        gps.update();
        imu0.update();
    }
}

void loop() {

  if (VERBOSITY) {
    Serial.print("GPS coord lat, long: ");
    Serial.print(gps.getLat() * 1000000);
    Serial.print(", ");
    Serial.print(gps.getLong() * 1000000);
    Serial.println();
    
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
  } else {
    Serial.print(gps.getLat() * 1000000);
    Serial.print(", ");
    Serial.print(gps.getLong() * 1000000);
    Serial.print(", ");
    Serial.print(queue.getDistToCur());
    Serial.print(", ");
    Serial.print(queue.getCurHeading());
    Serial.print(", ");
    Serial.print(imu0.getOrientX());
    Serial.print(", ");
    Serial.print(imu0.getOrientY());
    Serial.print(", ");
    Serial.print(imu0.getOrientZ());
    Serial.print(", ");
    Serial.print(imu0.getAccelX());
    Serial.print(", ");
    Serial.print(imu0.getAccelY());
    Serial.print(", ");
    Serial.print(imu0.getAccelZ());
    Serial.print(", ");
    Serial.print(imu0.getVelocityX());
    Serial.print(", ");
    Serial.println(imu0.getVelocityY());

  }
    
    intellectualWait(500);
}
