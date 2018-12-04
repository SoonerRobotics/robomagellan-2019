#include "GPSModule.h"
#include "IMU.h"
#include "LocalizationGlobals.h"
#include "LocalizationSetup.h"
#include <ArduinoJson.h>

const int capacity = JSON_OBJECT_SIZE(7);
StaticJsonBuffer<capacity> jb;
JsonObject& obj = jb.createObject();

void setup() {
    localizationSetup();

    intellectualWait(1000);

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

    obj["gps_lat"] = gps.getLat();
    obj["gps_lon"] = gps.getLong();
    obj["imu_heading"] = imu0.getOrientX();
    obj["imu_accel_x"] = imu0.getAccelX();
    obj["imu_accel_y"] = imu0.getAccelY();
    obj["encoder_dx"] = 0;
    obj["encoder_dt"] = 0;

    obj.printTo(Serial);
    Serial.write("\n");

    intellectualWait(1000 / SERIAL_SEND_RATE);
}
