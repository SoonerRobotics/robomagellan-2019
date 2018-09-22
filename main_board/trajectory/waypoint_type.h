#ifndef WAYPOINT_TYPE_H
#define WAYPOINT_TYPE_H

/*******************************************************************
 * Enumeration of the various types of waypoints that could be on
 * the route.
 * START, FINISH and BONUS are all required waypoints.
 * These must be visited before the course is completed.
 * The others are all non-required waypoints, which are used as
 * guideposts along the route
 *******************************************************************/
enum WaypointType
{
    START,
    FINISH,
    BONUS,
    ADJUSTMENT,
    ON_COURSE,

    NUM_WAYPOINT_TYPES,
    DEFAULT_WAYPOINT
};

#endif
