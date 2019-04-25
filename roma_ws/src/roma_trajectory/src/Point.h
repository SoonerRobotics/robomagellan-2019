// Point.h
#ifndef POINT_H
#define POINT_H

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
	Point(double latitude, double longitude, double heading);

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
	double calcTurnTo(Point next);
};

#endif //!POINT_H