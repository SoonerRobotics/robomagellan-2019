#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <TinyGPS.h>
#include <SoftwareSerial.h>

class GPSModule{

public:
    
    GPSModule(uint8_t receivePin, uint8_t transmitPin);
    GPSModule(uint8_t receivePin, uint8_t transmitPin, long baud);
    ~GPSModule();

    void update();

    int available();

    float getLat();
    float getLong();
    float getAlt();
    float getCourse();
    float getSpeed();

private:

    TinyGPS gps;
    SoftwareSerial* ss = nullptr;

    float lat;
    float lon;
    unsigned long age;

};

#endif
