#include "waypoint.h"

Waypoint::Waypoint()
{
    this->latitude  = 0.0f;
    this->longitude = 0.0f;
    this->type      = DEFAULT_WAYPOINT;
    this->heading   = 0.0f;
    this->velocity  = 0.0f;
    this->enroute   = false;
}

Waypoint::Waypoint(float latitude, float longitude, WaypointType type, float heading, float velocity, bool enroute)
{
    this->latitude  = latitude;
    this->longitude = longitude;
    this->type      = type;
    this->heading   = heading;
    this->velocity  = velocity;
    this->enroute   = enroute;
}

void Waypoint::init(float latitude, float longitude, WaypointType type, float heading, float velocity, bool enroute)
{
    this->latitude  = latitude;
    this->longitude = longitude;
    this->type      = type;
    this->heading   = heading;
    this->velocity  = velocity;
    this->enroute   = enroute;
}

/* Setters */
void Waypoint::setLatitude(const float lat)
{
    this->latitude = lat;
}

void Waypoint::setLongitude(const float lon)
{
    this->longitude = lon;
}

void Waypoint::setType(const WaypointType type)
{
    this->type = type;
}

void Waypoint::setHeading(const float heading)
{
    this->heading = heading;
}

void Waypoint::setVelocity(const float velocity)
{
    this->velocity = velocity;
}

void Waypoint::setEnrouteStatus(const bool enroute)
{
    this->enroute = enroute;
}

/* End Setters */
/* Getters */

float Waypoint::getLatitude()
{
    return this->latitude;
}

float Waypoint::getLongitude()
{
    return this->longitude;
}

WaypointType Waypoint::getType()
{
    return this->type;
}

float Waypoint::getHeading()
{
    return this->heading;
}

float Waypoint::getVelocity()
{
    return this->velocity;
}

bool Waypoint::isPointEnroute()
{
    return this->enroute;
}

/* End Getters*/

/* Resetter */
void Waypoint::reset()
{
    this->latitude  = 0.0f;
    this->longitude = 0.0f;
    this->type      = DEFAULT_WAYPOINT;
    this->heading   = 0.0f;
    this->velocity  = 0.0f;
    this->enroute   = false;
}
/* End Resetter */

/* End Public Functions */
