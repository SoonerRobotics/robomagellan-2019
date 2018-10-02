#include "GPSModule.h"

GPSModule gps(3, 4);

void setup() {
    Serial.begin(9600);
}

void intellectualWait(unsigned long ms) {
    unsigned long startTime = millis();
    while (millis() - startTime < ms) {
        gps.update();
    }
}

void loop() {

    Serial.print("Latitude: ");
    Serial.print(gps.getLat());
    Serial.print(" ");
    Serial.print("Longitude: ");
    Serial.println(gps.getLong());
    
    intellectualWait(1000);
}