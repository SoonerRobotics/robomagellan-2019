/* System Includes */
#include <iostream>

/* Project Includes */
#include "trajectory/trajectory.h"


int main()
{
    Trajectory trajectory("./waypoints.txt");

    trajectory.generateKMLOutput("./test.kml");

    return 0;
}
