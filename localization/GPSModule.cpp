#include "GPSModule.h"

GPSModule::GPSModule(uint8_t receivePin, uint8_t transmitPin) {
    ss = new SoftwareSerial(receivePin, transmitPin);
    ss->begin(9600);
}

GPSModule::GPSModule(uint8_t receivePin, uint8_t transmitPin, long baud) {
    ss = new SoftwareSerial(receivePin, transmitPin);
    ss->begin(baud);
}

GPSModule::~GPSModule() {
    delete ss;
}

int GPSModule::available() {
    return ss->available();
}

void GPSModule::update() {
    while (ss->available())
        gps.encode(ss->read());
}

float GPSModule::getLat() {
    gps.f_get_position(&lat, &lon, &age);
    return lat;
}

float GPSModule::getLong() {
    gps.f_get_position(&lat, &lon, &age);
    return lon;
}

float GPSModule::getAlt() {
    return gps.f_altitude();
}

float GPSModule::getCourse() {
    return gps.f_course();
}

float GPSModule::getSpeed() {
    return gps.f_speed_mph();
}
