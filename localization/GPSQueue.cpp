#include "GPSQueue.h"

GPSQueue::GPSQueue(GPSModule* gps) {
    this->gps = gps;
}

void GPSQueue::addPoint(float lat, float lon) {
    if (numPoints < MAX_POINTS) {
        points_lat[numPoints] == lat;
        points_long[numPoints] == lon;
        numPoints++;
    }
}

float GPSQueue::getDistToCur() {
    if (numPoints == 0) {
        return -1; //need better than this, as distance could be negative?
    }

    return calcDistance(points_lat[0], points_long[0], gps->getLat(), gps->getLong());
}

float GPSQueue::getCurHeading() {
    if (numPoints == 0) {
        return -1;
    }

    return calcHeading(points_lat[0], points_long[0], gps->getLat(), gps->getLong());
}

float GPSQueue::calcDistance(double lat1, double long1, double lat2, double long2)
{
    /*
    double d2r = (PI / 180.0);
    double dlong = (long2 - long1) * d2r;
    double dlat = (lat2 - lat1) * d2r;
    double a = pow(sin(dlat/2.0), 2) + cos(lat1*d2r) * cos(lat2*d2r) * pow(sin(dlong/2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = 6.367 * c;
    */

    //The following numbers are super duper hardcoded, for the convenience of only myself
    //These are found by diving the difference in two coords by the actual distance
    //This assumes that gps coords map onto a flat plane, which is only true for small areas.
    //These will have to be recalculated for different locations, at least until
    //Whatever the code is above is made to actually work. Good luck with that future code editor.
    //With love, Noah.
    double a = (lat2 - lat1) * 111198.1567; // Works anywhere, probably
    double b = (long2 - long1) * 90850.59978; // This works only in Norman
    double d = sqrt(a*a + b*b); //thank you mr. pythagoras


    return (float)d;
}

float GPSQueue::calcHeading(double lat1, double long1, double lat2, double long2)
{
    double d2r = (PI / 180.0); //dont look at the next 4 lines please
    lat1 *= d2r;
    lat2 *= d2r;
    long1 *= d2r;
    long2 *= d2r;

    double y = sin(long2-long1) * cos(lat2);
    double x = cos(lat1)*sin(lat2) - sin(lat1)*cos(lat2) * cos(long2-long1);

    return atan2(y, x) * 1/d2r;
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
