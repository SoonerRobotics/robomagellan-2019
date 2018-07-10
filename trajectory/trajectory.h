#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <fstream>
#include <sstream>
#include <string>
#include "waypoint.h"

class Trajectory
{
    public:
        /* Default constructor */
        Trajectory();

        /* Initialize the trajectory by reading the waypoints file */
        Trajectory(const std::string& filename);

        /* Append waypoints onto the current trajectory */
        void appendWaypoints(const std::string& filename);

        /* Output to Google Earth for debugging the path */
        void generateKMLOutput(const std::string& filename);

        /* Move to the next trajectoryNode in the list. */
        /* Used to advance past required waypoints      */
        void advanceToNextPoint();

        /* Get the information for the active waypoint on the course */
        Waypoint* getActivePoint();

        /* Get the information for the next waypoint on the course */
        Waypoint* getNextPoint();

        /* Activates the nearest node that has not been visited yet, */
        /* while also ensuring no required waypoints are skipped     */
        void activateNearestNode(float robotLatitude, float robotLongitude);

        /* Detects if the robot has passed or touched the active waypoint */
        bool isPastWaypoint();

        /* Determines if the robot is within the region of the active point */
        bool inRangeofActivePoint();

    private:
        /* Load all the desired waypoints from a file */
        void loadWaypoints(const std::string& filename);

        /* Convert from degrees-minutes to decimal */
        float convertCoordinate(char c, float degree, float minute);

        /* Find the type of waypoint given a char from a file */
        WaypointType decodeWaypointType(char abbreviation);

        void push(Waypoint wpt);

        /* Add data into the path to make a trajectory */
        void buildTrajectory();

        std::string getWptKMLCoords(int i);
        std::string getWptKMLComponent(int i, bool lat);

        /* Array of waypoints in the trajectory */
        Waypoint waypoints[200];
        int numWaypoints;
        int currentWpt;
};

#endif
