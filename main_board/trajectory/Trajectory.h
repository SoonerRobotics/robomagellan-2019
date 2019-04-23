// Trajectory.h
#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "Point.h"
#include <queue>

class Trajectory: public Point {
private:
	Point currPos; // current coordinate position

public:
	// constructors
	Trajectory(Point currPos);

	// getters
	Point getCurrPos();
	
	// setters
	void setCurrPos(Point currPoss);
	
	// functions
	// build trajectory from current position to the next 
	std::queue<Point> buildTrajectoryTo(Point curr, Point next);
	// find the shortest path from starting point to all 3 cones
	std::queue<Point> findShortestConePath(Point start, Point* cones);

};

#endif //!TRAJECTORY_H