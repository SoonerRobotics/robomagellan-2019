#include "GPSModule.h"
#include "GPSQueue.h"
#include "IMU.h"

GPSModule gps(3, 4);

IMU imu0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Check available sensors
  bool useGps = false;
  if (gps.availableGPS() != 0)
    useGps = true;
  bool useIMU = imu0.calibrated();
  Serial.print("GPS Good? ");
  Serial.println(useGps);
  Serial.print("IMU Good? ");
  Serial.println(useIMU);

  //Set Current State
  if (useGps) {
    Serial.print("Lat:");
    Serial.println(gps.getLat());
    Serial.print("Long:");
    Serial.println(gps.getLong());
  }
  if(useIMU)
    Serial.print("X:");
    Serial.println(imu0.getX());
    Serial.print("Y:");
    Serial.println(imu0.getY());
    Serial.print("Z:");
    Serial.println(imu0.getZ());
}
