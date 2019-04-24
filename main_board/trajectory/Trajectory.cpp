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

// TODO: test the function
// find the shortest path from starting point to all 3 cones
std::queue<Point> Trajectory::findShortestConePath(Point start, Point* cones) {
	// A, B, C are cones' points, 
	// cones [0], A is 0; cones[1], B is 1; cones[2], C is 2
	double totalDist[6]; // total path distance
	int tdIndex = 0; // total distance index
	double currDist = 0; // current distance
	
	// have a list of queue for paths
	std::queue<Point> paths[6];
	// var for first and current cones
	Point firstCone;
	Point currCone;
	
	/*
	we know there are 6 possible paths:
	start012, start021,	start102
	start120, start201,	start210
	*/
	
	// build the possible path 
	for (int j = 0; j < 3; j++) {
		// start always the first point
		// start point added to path
		paths[tdIndex].push(start);

		// first cone waypoint added to path
		paths[tdIndex].push(cones[j]);
		
		// reset current distance calculation
		currDist = 0;

		// calculate distance from start to the first cone
		// start0, start1, start2
		currDist += start.calcDistanceTo(cones[j]);
		currCone = cones[j]; // update current cone

		// first, third, fifth path
		// start012, start102, start201
		for (int k = 0; k < 3; k++) {
			int conesCount = 1;
			if (j != k) {
				paths[tdIndex].push(cones[k]);
				// calculate distance from the first cone to second cone or
				// calculate distance from the second cone to third cone
				// start01, start012
				// start10, start102
				// start20, start 201 
				currDist += currCone.calcDistanceTo(cones[k]);
				// update current cone
				currCone = cones[k];
				conesCount++;
				if (conesCount == 3) {
					totalDist[tdIndex] = currDist;
				}
			}
		}

		// new path
		// increment total distance's index
		tdIndex++;
		// reset current distance calculation
		currDist = 0;

		// start always the first point
		// start waypoint added to path
		paths[tdIndex].push(start);
		// first cone waypoint added to path
		paths[tdIndex].push(cones[j]);

		// calculate distance from start to the first cone
		// start0, start1, start2
		currDist += start.calcDistanceTo(cones[j]);
		currCone = cones[j];
		// second, fourth, sixth path
		// start021, start120, start210 
		for (int m = 2; m >= 0; m--) {
			int conesCount = 1;
			if (j != m) {				
				paths[tdIndex].push(cones[m]);				
				// start02, start021
				// start12, start120
				// start21, start210
				currDist += currCone.calcDistanceTo(cones[m]);
				// update current cone & its counter
				currCone = cones[m];
				conesCount++;
				if (conesCount == 3) {
					totalDist[tdIndex] = currDist;
				}
			}
		}
		tdIndex++; // increment total distance index
	}

	std::queue<Point> minPath;
	double currentMinDist = 0.0;
	// find the minimum total distance
	for (int i = 0; i < 6; i++) {
		if (totalDist[i] < currentMinDist) {
			currentMinDist = totalDist[i];
			minPath = paths[i];
		}
	}

	std::queue<Point> minPath;
	double currentMinDist = 0.0;
	// find the minimum total distance
	// 
	for (int i = 0; i < 6; i++) {
		if (totalDist[i] < currentMinDist) {
			currentMinDist = totalDist[i];
			minPath = paths[i];
		}
	}

	return minPath;
}

// TODO: get current position & get update from LIDAR
// update to the next point once the robot is within 5 metres of its target point
void Trajectory::updatePosition(std::queue<Point> currQueue) {
	// get the first point on queue
	Point currTargetPoint = currQueue.front();
	// set a 5 metres distance threshold
	double distThreshold = 5.0; 
	while (!currQueue.empty()) {
		// TODO
		// get the robot's current position
		Point currPos;
		if (currPos.calcDistanceTo(currTargetPoint) < distThreshold) {
			currQueue.pop();
			if (!currQueue.empty()) {
				currTargetPoint = currQueue.front();
			}			
		}
	}
}