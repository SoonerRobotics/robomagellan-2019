#ifndef GPSQUEUE_H
#define GPSQUEUE_H

#include "GPSModule.h"

#define MAX_POINTS 5

class GPSQueue{

public:
    
    GPSQueue(GPSModule* gps);

    void addPoint(float lat, float lon);

    float getDistToCur();
    float getCurHeading();

    bool hasNext();
    void getNext();

private:

    GPSModule* gps;
    
    int numPoints;

    float points_lat[MAX_POINTS];
    float points_long[MAX_POINTS];

    float calcDistance(double lat1, double long1, double lat2, double long2);
    float calcHeading(double lat1, double long1, double lat2, double long2);

};

#endif