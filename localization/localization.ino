#include "GPSModule.h"
#include "IMU.h"
#include "LocalizationGlobals.h"
#include "LocalizationSetup.h"
#include <ArduinoJson.h>

const int capacity = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(7);
StaticJsonBuffer<capacity> jb;
JsonObject& root = jb.createObject();
JsonObject& dataArray = root.createNestedObject("data");
 
void setup() {

    //Set device ID and default event name
    root["id"] = 2;
    root["event"] = "full_update";
  
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

void loop() 
{
  
    //TODO: Add more functionality than full update (i.e. add variable update times based on sensor frequency)
    dataArray["gps_lat"] = gps.getLat();
    dataArray["gps_lon"] = gps.getLong();
    dataArray["imu_heading"] = imu0.getOrientX();
    dataArray["imu_accel_x"] = imu0.getAccelX();
    dataArray["imu_accel_y"] = imu0.getAccelY();
    dataArray["encoder_dx"] = 0;
    dataArray["encoder_dt"] = 0;


    root.printTo(Serial);
    Serial.write("\n");

    intellectualWait(1000 / SERIAL_SEND_RATE);
}
