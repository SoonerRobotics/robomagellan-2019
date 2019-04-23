// Trajectory.cpp file
/*
Finding next point
http://www.movable-type.co.uk/scripts/latlong.html
*/
#include "Trajectory.h"
#include <math.h>
#include <queue>
#include <list>

static const double PI = 3.14159265358979323846;	// Pi 
static const double earthRadius = 6371 * 1000;		// mean radius in Meters

// constructors
Trajectory::Trajectory(Point currPos) {
	this->currPos = currPos;
}

// getters
Point Trajectory::getCurrPos() {
	return currPos;
}

// setters
void Trajectory::setCurrPos(Point currPoss) {
	this->currPos = currPos;
}

// functions

// TESTING NEEDED
// build trajectory from current position to the next 
// this function will create three coordinates between the current point and "next" point
// in our case, the next point shoud be a specified cone point
// in main, this function should be called such that 
// it will build trajectory from start to first cone, first cone to second cone, second cone to last cone
std::queue<Point> Trajectory::buildTrajectoryTo(Point curr, Point next) {
	double totalDist = 0;
	// build 3 coordinates points with 1/4, 1/2, 3/4 of total distance of the next point
	std::queue<Point> trajeQueue;
	
	// getting the current and next's latitude and longitude
	double currLat = curr.getLat();
	double currLong = curr.getLong();
	double nextLat = next.getLat();
	double nextLong = next.getLong();

	// heading needs to be clockwise from north for the distance eq. to be correct
	double currHeading = curr.calcHeadingTo(next);

	// find the total distance from current location to next cone
	double currDist = curr.calcDistanceTo(next);

	Point quarterPoint, halfwayPoint, threeQuarterPoint;
	
	double distPoint[] = { 0.25, 0.5, 0.75 };
	double latitude[] = { 0,0,0 };
	double longitude[] = { 0,0,0 };

	for (int i = 0; i < 3; i++) {
		double delta = distPoint[i] * currDist / earthRadius;
		latitude[i] = asin(sin(currLat)*cos(delta) +
			cos(currLat)*sin(delta)*cos(currHeading));
		longitude[i] = currLong + atan2(sin(currHeading)*sin(delta)*cos(currLat),
			cos(delta) - sin(currLat)*sin(nextLat));
	}

	// set the quarter point coordinate
	quarterPoint.setLat(latitude[0]);
	quarterPoint.setLong(longitude[0]);
	trajeQueue.push(quarterPoint);

	// set the halfway point coordinate
	halfwayPoint.setLat(latitude[1]);
	halfwayPoint.setLong(longitude[1]);
	trajeQueue.push(halfwayPoint);

	// set the three quarter point coordinate
	threeQuarterPoint.setLat(latitude[2]);
	threeQuarterPoint.setLong(longitude[2]);
	trajeQueue.push(threeQuarterPoint);

	// return all 3 coordinates in a queue 
	return trajeQueue;}

// TODO
// find the shortest path from starting point to all 3 cones
std::queue<Point> Trajectory::findShortestConePath(Point start, Point* cones) {
	// A, B, C are cones' point, A = 0, B = 1, C = 2
	double totalDist = 0; // total path distance
	double currDist = 0; // current distance

	std::queue<Point> conesQueue;
	
	// start -> A -> B -> C

	// start -> A -> C -> B

	// start -> B -> A -> C

	// start -> B -> C -> A

	// start -> C -> A -> B

	// start -> C -> B -> A

	return conesQueue;
}