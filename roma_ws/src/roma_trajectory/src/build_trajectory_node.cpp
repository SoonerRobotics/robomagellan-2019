// TODO: need to be tested
// build_trajectory_node.cpp file
/*
Finding next point
http://www.movable-type.co.uk/scripts/latlong.html
*/

// include ROS
#include <ros/ros.h>

// include messages
#include <roma_msgs/kalman_state.h> // for current position
#include <roma_msgs/obstacles.h> // to create new trajectory if obstacle(s) is present
#include <roma_msgs/motion_cmds.h>

// include libraries
#include "roma_trajectory/Point.h"
#include <queue>
#include <math.h>

// motion publisher & message
ros::Publisher motion_pub;
roma_msgs::motion_cmds motion_cmd;

// Note: PI and EARTHRADIUS is define in Point.h

// global variables for queues and point
std::queue<Point> startToEndQueue;	// queue from start point to each cone point
std::queue<Point> currToConeQueue;	// queue from current position to targeted cone
Point currBotPos;					// current position of the bot
Point currTargetCone;				// current targeted cone

// TESTING NEEDED
// build trajectory from current position to the next 
// this function will create three coordinates between the current point and "next" point
// in our case, the next point shoud be a specified cone point
// in main, this function should be called such that 
// it will build trajectory from start to first cone, first cone to second cone, second cone to last cone
std::queue<Point> buildTrajectory(Point curr, Point next) {
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
		double delta = distPoint[i] * currDist / EARTHRADIUS;
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
std::queue<Point> findShortestConePath(Point start, Point* cones) {
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
	
	// build all the possible paths 
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

	// variables for shortest path and distance
	std::queue<Point> minPath;
	double currentMinDist = totalDist[0];

	// find the minimum total distance 
	for (int i = 1; i < 6; i++) {
		if (totalDist[i] < currentMinDist) {
			// update shortest path and distance
			currentMinDist = totalDist[i];
			minPath = paths[i];
		}
	}

	return minPath;
}

// TODO: get update from LIDAR when the bot is within the threshold distance
// update to the next point once the robot is within 5 metres of its target point
void ekfCallback(const roma_msgs::kalman_state::ConstPtr& filtered_state)
{
	// motion_cmd.power, motion_pub.publish(motion_cmd), motion_cmd.steer_ang and motion_cmd.steer_ang from Noah's code. Thank you, Noah :)
	// https://github.com/Sooner-Competitive-Robotics/robomagellan-2019/blob/ros/roma_ws/src/roma_trajectory/src/trajectory_node.cpp

	// first callback, currToConeQueue is the current queue, which from start to first cone with 3 waypoints in between from buildTrajectory function
	motion_cmd.power = 0.3;

	// update current position of the bot
	currBotPos.setLat(filtered_state->latitude);
	currBotPos.setLong(filtered_state->longitude);

	// get the target point from the currToConeQueue queue
	Point currTargetPoint = currToConeQueue.front();
	// set a 5 metres distance threshold
	double distThreshold = 5.0;

	if (currBotPos.calcDistanceTo(currTargetPoint) < distThreshold) {
		// TODO: need to go to LIDAR and make sure to actually 
		// get to cone before point is pop from queue

		currToConeQueue.pop();
		if (currToConeQueue.empty()) { // already touch the cone, need to build new trajectory
			startToEndQueue.pop(); // update to the next point of the course
			if (!startToEndQueue.empty()) { // have yet to finish the course
				currTargetCone = startToEndQueue.front(); // update target cone

				// build the new 3 waypoints between current position to the target cone
				currToConeQueue = buildTrajectory(currBotPos, currTargetCone);
			}
			else { // end of the course
				   //TODO: decide what to do when it reach the last cone
			}
		}
	}

	currTargetPoint = currToConeQueue.front(); // update current target point
	// calculate the steering angle of the bot
	motion_cmd.steer_ang = currBotPos.calcHeading(currTargetPoint) - filtered_state->heading;
	motion_cmd.steer_ang = motion_cmd.steer_ang > 180.0 ? motion_cmd.steer_ang - 360.0 : motion_cmd.steer_ang;
	// publish the result
	motion_pub.publish(motion_cmd);
}


int main(int argc, char** argv) {
	// initialiaze the node
	ros::init(argc, argv, "buildtrajectory_node");
	// setup the node
	ros::NodeHandle build_trajectory_node;

	//Create the publisher for the obstacle message
	motion_pub = trajectory_node.advertise<roma_msgs::motion_cmds>(trajectory_node.resolveName("/roma_motion/cmd"), 10);

	//Create the subscribers
	ros::Subscriber ekf_sub = trajectory_node.subscribe(trajectory_node.resolveName("/roma_kalman/state"), 10, &ekfCallback);

	// Coordinates at OU South Oval
	// cooridantes of the cones
	Point coneA = Point(35.03750000, -97.34583333);
	Point coneB = Point(35.20416667, -97.44611111);
	Point coneC = Point(35.03750000, -97.24683333);
	Point* cones[3];
	cones[0] = coneA;
	cones[1] = coneB;
	cones[2] = coneC;

	// get the current(start) position from kalman_state data
	// TODO: test if this part actually okay 
	const roma_msgs::kalman_state::ConstPtr& kalman_state;

	Point start;
	start.setLat(kalman_state->latitude);
	start.setLong(kalman_state->longitude);

	// find the shortest path
	startToEndQueue = findShortestConePath(start, cones);

	// build the first 3 points between start position to the first cone
	startToEndQueue.pop(); // we already know the start position	
	currTargetCone = startToEndQueue.front(); // coodinates point of the first cone
	
	currToConeQueue = buildTrajectory(start, currTargetCone);

	// automatically handle callback
	ros::spin();
	return 0;
}