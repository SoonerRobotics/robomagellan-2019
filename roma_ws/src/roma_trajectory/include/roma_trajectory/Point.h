// Point.h
#ifndef POINT_H
#define POINT_H

// include ROS
#include <ros/rosh.h>

// include messagges
#include <roma_msgs/kalman_state.h>
#include <roma_msgs/obstacles.h>
#include <roma_msgs/motion_cmds.h>

//include libraries
#include <math.h>

#define PI 3.14159265358979323846
#define earthRadius 6371000 // in metres

class Point {

private:
	double latitude; // latitude
	double longitude; // longitude
	double heading; // current heading
	double velocity; // current velocity

public:
	// constructors
	Point ();
	Point(double latitude, double longitude);
	Point(const roma_msgs::kalman_state::ConstPtr& kalman_state);

	// getters
	double getLat();
	double getLong();
	double getHeading();
	double getVelocity();

	// setters
	void setLat(double latitude);
	void setLong(double longitude);
	void setHeading(double heading);
	void setVelocity(double velocity);

	// functions
	double calcDistanceTo(Point end);
	double calcHeadingTo(Point end);
};

#endif //!POINT_H