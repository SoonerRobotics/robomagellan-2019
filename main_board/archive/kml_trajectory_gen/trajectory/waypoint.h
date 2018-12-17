#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "waypoint_type.h"

class Waypoint
{
    public:
        Waypoint();

        /* Full Initialization */
        Waypoint(float latitude, float longitude, WaypointType type, float heading, float velocity, bool enroute);
        void init(float latitude, float longitude, WaypointType type, float heading, float velocity, bool enroute);

        /* Setters */
        void setLatitude(const float lat);
        void setLongitude(const float lon);
        void setType(const WaypointType type);
        void setHeading(const float heading);
        void setVelocity(const float velocity);
        void setEnrouteStatus(const bool enroute);

        /* Getters */
        float getLatitude();
        float getLongitude();
        WaypointType getType();
        float getHeading();
        float getVelocity();
        bool isPointEnroute();

        /* Reset/Destruct */
        void reset();

    private:
        float latitude;
        float longitude;
        WaypointType type;
        float heading;      /* Heading at the waypoint */
        float velocity;     /* Velocity at the waypoint */
        bool enroute;       /* Is the robot yet to arrive at this point in the trajectory? */

};

#endif
