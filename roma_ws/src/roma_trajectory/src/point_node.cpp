// TODO: need to be tested
// point_node.cpp file

// include ROS
#include <ros/ros.h>

// include messages
#include <roma_msgs/kalman_state.h>

// include libraries
#include "roma_trajectory/Point.h"
#include <queue>
#include <math.h>

// define in header
//static const double PI = 3.14159265358979323846;	// Pi 
//static const double earthRadius = 6371 * 1000;		// mean radius in Meters

// constructors
Point::Point() { // should this be empty instead?
	this->latitude = 0;
	this->longitude = 0;
	this->heading = 0;
	this->velocity = 0;
}

Point::Point(double latitude, double longitude) {
	this->latitude = latitude;
	this->longitude = longitude;
	this->heading = 0;
	this->velocity = 0;
}

Point::Point(const roma_msgs::kalman_state::ConstPtr& kalman_state) {
	this->latitude = kalman_state->latitude;
	this->longitude = kalman_state->longitude;
	this->heading = kalman_state->heading;
	this->velocity = kalman_state->velocity;
}

// getters
double Point::getLat() {
	return latitude;
}
double Point::getLong() {
	return longitude;
}
double Point::getHeading() {
	return heading;
}
double Point::getVelocity() {
	return velocity;
}

// setters
void Point::setLat(double latitude) {
	this->latitude = latitude;
}
void Point::setLong(double longitude) {
	this->longitude = longitude;
}
void Point::setHeading(double heading) {
	this->heading = heading;
}
void Point::setVelocity(double velocity) {
	this->velocity = velocity;
}

// functions
//double  Point::calcDistanceTo(Point end) {
double  Point::calcDistanceTo(Point end) {
	// equation from https://www.sunearthtools.com/tools/distance.php
	double d2r = (PI / 180.0); // degree to radian conversion
	
	// convert latitude and longitude degree decimal to radian
	double currentLat = this->latitude * d2r;
	double currentLong = this->longitude * d2r;
	double destLat = end.latitude * d2r;
	double destLong = end.longitude * d2r;

	// calculate distance from current to destination
	double distance = EARTHRADIUS * acos(sin(currentLat) * sin(destLat) +
		cos(currentLat) * cos(destLat) * cos(currentLong - destLong));

	return distance; // in meters
}

// calculate the bearing from current coordinate to end (specified) coordinate
//double  Point::calcHeadingTo(Point end) {	
double  Point::calcHeadingTo(Point end) {
	// github https://github.com/Sooner-Competitive-Robotics/robomagellan-2019/blob/ros/main_board/trajectory/point.py

	double d2r = (PI / 180.0); // degree to radian conversion

	// convert latitudes from degree to radian
	double lat1 = this->latitude * d2r;
	double lat2 = end.latitude * d2r;

	// delta longitude in radian
	double diffLong = (end.longitude - this->longitude) * d2r;

	// calculate the initial bearing
	double x = sin(diffLong) * cos(lat2);
	double y = cos(lat1) * sin(lat2) - (sin(lat1) * cos(lat2) * cos(diffLong));

	double initial_bearing = atan2(x, y);

	// Now we have the initial bearing but atan2 return values
	// from - 180° to + 180° which is not what we want for a compass bearing
	// The solution is to normalize the initial bearing as shown below
	initial_bearing = (initial_bearing) / d2r; // change it to degrees

	// get compass bearing 360 degree north
	double compass_bearing = fmod((initial_bearing + 360), 360);
	
	// std::cout << "initial bearing: " << compass_bearing << std::endl;

	/*
	  won't really need to calculate for close range coordinate points
	  http://www.movable-type.co.uk/scripts/latlong.html
	  For final bearing, simply take the initial bearing 
	  from the end point to the start point and reverse it 
	  (using theta = (theta+180) % 360).	

	*/
	/*
	diffLong = (this->longitude - end.longitude) * d2r;

	x = sin(diffLong) * cos(lat1);
	y = cos(lat2) * sin(lat1) - (sin(lat2) * cos(lat1) * cos(diffLong));
	initial_bearing = atan2(x, y);
	initial_bearing = (initial_bearing) / d2r;

	double final_bearing = fmod(initial_bearing + 180, 360);

	std::cout << "final bearing: " << final_bearing << std::endl;
	//double final_bearing = fmod(compass_bearing + 180, 360);

	double average_bearing = (compass_bearing + final_bearing) / 2;
	*/

	return compass_bearing;
}