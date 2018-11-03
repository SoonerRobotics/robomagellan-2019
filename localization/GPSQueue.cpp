#include "GPSQueue.h"

GPSQueue::GPSQueue(GPSModule* gps) {
    this->numPoints = 0;
    this->gps = gps;
}

void GPSQueue::addPoint(float lat, float lon) {
    if (numPoints < MAX_POINTS) {
        points_lat[numPoints] = lat;
        points_long[numPoints] = lon;
        numPoints++;
    }
}

float GPSQueue::getDistToCur() {
    if (numPoints == 0) {
        return -1; //need better than this, as distance could be negative?
    }

    return calcDistance(gps->getLat(), gps->getLong(), points_lat[0], points_long[0]);
}

float GPSQueue::getCurHeading() {
    if (numPoints == 0) {
        return -1;
    }

    return calcHeading(gps->getLat(), gps->getLong(), points_lat[0], points_long[0]);
}

// distance & bearings formula from:
// https://www.sunearthtools.com/tools/distance.php

float GPSQueue::calcDistance(double lat1, double long1, double lat2, double long2)
{
    double a = (lat2 - lat1) * 111198.1567; // Works anywhere, probably
    double b = (long2 - long1) * 90850.59978; // This works only in Norman
    double d = sqrt(a*a + b*b); //thank you mr. pythagoras

    return (float)d;
}

float GPSQueue::calcHeading(double lat1, double long1, double lat2, double long2)
{
	double b = lat2 - lat1;
    double a = long2 - long1;

    double theta = atan(b/a) * (180/PI) + (long2 > long1) ? 90 : -270;

	return (float) theta;
}

bool GPSQueue::hasNext() {
    return numPoints > 0;
}

void GPSQueue::getNext() {
    for (int i=0; i<numPoints-1; i++) { //shift everything 1 to the left
        points_lat[i] = points_lat[i+1];
        points_long[i] = points_long[i+1];
    }
    numPoints--;
}
