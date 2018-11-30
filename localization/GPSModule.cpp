#include "GPSModule.h"

GPSModule::GPSModule(uint8_t receivePin, uint8_t transmitPin) {
   GPSModule(receivePin,transmitPin,baud);
}

GPSModule::GPSModule(uint8_t receivePin, uint8_t transmitPin, long baud) {
    ss = new SoftwareSerial(receivePin, transmitPin);
    ss->begin(baud);
    this->receivePin = receivePin;
    this->transmitPin = transmitPin;
    this->baud = baud;
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
    float lat_temp = 0;
    float lon_temp = 0;

    gps.f_get_position(&lat_temp, &lon_temp, &age);

    lat = 0.9 * lat + 0.1 * lat_temp;
    lon = 0.9 * lon + 0.1 * lon_temp;

    return lat;
}

float GPSModule::getLong() {
    float lat_temp = 0;
    float lon_temp = 0;

    gps.f_get_position(&lat_temp, &lon_temp, &age);

    lat = 0.9 * lat + 0.1 * lat_temp;
    lon = 0.9 * lon + 0.1 * lon_temp;
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


GPSModule GPSModule::operator=(const GPSModule& gps){
  GPSModule newGPS(gps.receivePin,gps.transmitPin,gps.baud);
  return newGPS;
}
