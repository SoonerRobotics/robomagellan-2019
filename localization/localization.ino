#include "GPSModule.h"
#include "GPSQueue.h"
#include "IMU.h"

GPSModule gps(3, 4);
GPSQueue queue(&gps);

IMU imu0; //apparently imu already exists

void setup() {
    Serial.begin(9600);

    queue.addPoint(35.210605, -97.443412); //a bit under Carson
}

void intellectualWait(unsigned long ms) {
    unsigned long startTime = millis();
    while (millis() - startTime < ms) {
        gps.update();
        imu0.read();
    }
}

void loop() {

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
    
    intellectualWait(500);
}
