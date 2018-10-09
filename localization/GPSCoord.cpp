// GPSCoord.cpp file
/* https://www.sunearthtools.com/dp/tools/conversion.php?lang=en
   GPS accuracy
   places	decimal		deg.		degrees	distance
	 0		1.0			1񲞪"		111.319 km
	 1		0.1			0񴔲"		11.132 km
	 2		0.01		0񲞭6"		1.113 km
	 3		0.001		0񲞭.6"	111.3 m
	 4		0.0001		0񲞪.36"	11.13 m
	 5		0.00001		0񲞪.036"	1.11 m
*/

// include libraries and header(s)
#include <iostream>
#include <string>
#include "GPSCoord.h"
#include <cmath>


static const double PI = 3.14159265358979323846;			// Pi 
static const double earthDiameterMeters = 6372.795477598;	// in KiloMeters

// constructs GPS with default coordinates
GPSCoord::GPSCoord() {
	this->latitude = 0.00;
	this->longitude = 0.00;
}

// constructs GPS with latitude and longitude coordinates
GPSCoord::GPSCoord(double latitude, double longitude) {
	this->latitude = latitude;
	this->longitude = longitude;
}

// frees array space as object is deleted
GPSCoord::~GPSCoord() {
}

// return latitude coordinate
double GPSCoord::getLat() {
	return this->latitude;
}

// return longitude coordinate
double GPSCoord::getLong() {
	return this->longitude;
}

// set latitude coordinate 
void GPSCoord::setLat(double latitudeCoord) {
	this->latitude = latitudeCoord;
}

// set longitude coordinate
void GPSCoord::setLong(double longitudeCoord) {
	this->longitude = longitudeCoord;
}

// read degree, minute, and second integers of GPS and convert to Decimal Degrees coordinate format
// possibly change the parameters in int to double??
double GPSCoord::convertGPS(int deg, int min, double sec) {
	double gpsCoord = 0.00;
	gpsCoord = (double)deg + ((min + (sec / 60.0)) / 60.0);

	return gpsCoord;
}

// read GPS and convert to Decimal Degrees coordinate format
double GPSCoord::convertGPS(std::string gpsInput) {
	double gpsCoord = 0.00;

	// Find non-integers index - degree, min, sec symbols
	int degreeIndex = -1;
	int nonIntegerCounter = 0;
	int nonIntegerArray[4]; // possible symbols: degree symbol, minute ( " ), period ( . ), second ( ' )

	// Check and store non-integer indexes
	for (int i = 0; i < gpsInput.length(); i++){
		// ASCII 48 is "0" & 57 is "9"
		for (int j = 48; j < 58; j++){
			if ( gpsInput[i] != j){
				nonIntegerArray[nonIntegerCounter] = i;
				nonIntegerCounter++;
			}
		}
	}
	
	// the length of string for seconds 
	int secStrLength = (gpsInput.length() - 1) - (nonIntegerArray[1] + 1);
	
	// getting the numbers 
	std::string degreeStr = gpsInput.substr(-1, nonIntegerArray[0] - 1);
	std::string minStr = gpsInput.substr(nonIntegerArray[0], 2);
	std::string secStr = gpsInput.substr(nonIntegerArray[1], secStrLength);
	
	int degreeInt, minInt;
	double secDouble;

	// convert all the strings into integers and double accordingly
	degreeInt = std::stoi(degreeStr);
	minInt = std::stoi(minStr);
	secDouble = std::stod(secStr);

	// convert into Decimal Degrees Coordinate format (i.e. 50.1234 degree)
	gpsCoord = convertGPS(degreeInt, minInt, secDouble);

	return gpsCoord;
}

// Caculate the distance from current position to destination

/*
https://www.sunearthtools.com/tools/distance.php

Calculating the distance between two geographical points
The formula used to determine the shortest distance between two points on the land (geodesic), 
approximates the geoid to a sphere of radius R = 6372.795477598 km (radius quadric medium), 
so the calculation could have a distance error of 0.3%, particularly in the polar extremes, 
and for long distances through various parallel. Given two points A and B on the sphere expressed by 
latitude (lat) and longitude (lon) you will have: 

distance (A, B) = R * arccos (sin(latA) * sin(latB) + cos(latA) * cos(latB) * cos(lonA-lonB)) 

The angles used are expressed in radians, converting between degrees and radians is obtained by 
multiplying the angle by pi and dividing by 180.

*/
double GPSCoord::calculateDistance(GPSCoord currentPos, GPSCoord destination) {
	double distance; // the distance the rover will need to travel

	// current position, dest -destination
	// Lat - latitude , Long - Longitude
	double currentLat, currentLong, destLat, destLong;

	// convert all degree to radian -> degree * PI / 180
	currentLat = currentPos.getLat() * PI / 180;
	currentLong = currentPos.getLong() * PI / 180;

	destLat = currentPos.getLat() * PI / 180;
	destLong = currentPos.getLong() * PI / 180;

	distance = earthDiameterMeters * acos( sin(currentLat) * sin(destLat) + 
		cos(currentLat) * cos(destLat) * cos(currentLong - destLong) );

	return distance;
}

// Caculate the bearings from current position to destination

/*
https://www.sunearthtools.com/tools/distance.php
Calculation of direction between two geographical points
To determine the direction from the starting point between two points on the earth, use the following formula:

deltaTheta = ln( tan( latB / 2 + PI / 4 ) / tan( latA / 2 + PI / 4) )
deltaLon = abs( lonA - lonB )
bearing :  theta = atan2( deltaLon ,  deltaTheta )

Note: 1) ln = natural log      2) if deltaLon > 180 degree  then   deltaLon = deltaLon (mod 180).
	  3) operation a mod n     4) function atan2(y, x)      5) the angles are in radians
*/

double GPSCoord::calculateBearings(GPSCoord currentPos, GPSCoord destination) {
	// all angles are in radian except specified
	double bearings, bearingsInDegrees, deltaTheta, deltaLong;

	// current position, dest -destination
	// Lat - latitude , Long - Longitude
	double currentLat, currentLong, destLat, destLong;

	// convert all degree to radian -> degree * PI / 180
	currentLat = currentPos.getLat() * PI / 180;
	currentLong = currentPos.getLong() * PI / 180;

	destLat = currentPos.getLat() * PI / 180;
	destLong = currentPos.getLong() * PI / 180;
	
	// log - natural log 
	deltaTheta = log(tan(destLat / 2 + PI / 4) / tan(currentLat / 2 + PI / 4));

	// if deltaLon > 180�  then   deltaLon = deltaLon (mod 180).
	if (deltaLong = (abs(currentLong - destLong) * 180 / PI) > 180) {
		// CHECK VALUE.. casting to int might NOT give an accurate result
		deltaLong = (int) abs(currentLong - destLong) % 180;
	}
	else {
		deltaLong = abs(currentLong - destLong);
	}
		
	bearings = atan2(deltaLong, deltaTheta);	// the result is in radian
	bearingsInDegrees = bearings * 180 / PI;	// convert result to degree

	return bearings;
}