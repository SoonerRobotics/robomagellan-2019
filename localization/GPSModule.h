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

    GPSModule operator=(const GPSModule& gps);

    uint8_t receivePin = NULL;
    uint8_t transmitPin = NULL;
    long baud = 9600;

private:

    TinyGPS gps;
    SoftwareSerial* ss = nullptr;
    float lat = 0;
    float lon = 0;
    unsigned long age = 0;

    

};

#endif
