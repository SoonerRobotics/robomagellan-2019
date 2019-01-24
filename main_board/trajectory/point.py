# This is the point class for a trajectory on the course.

class point:

    # Initialize the point as a location on the map
    def __init__(self, lat, lon, mode):
        self.lat = lat
        self.lon = lon
        self.mode = mode
        self.heading = 0
        self.velocity = 0
        self.status = False

    def getHeadingTo(self, otherPoint):
        lat1 = math.radians(self.getLat())
        lat2 = math.radians(otherPoint.getLat())

        diffLong = math.radians(otherPoint.getLon() - self.getLon())

        x = math.sin(diffLong) * math.cos(lat2)
        y = math.cos(lat1) * math.sin(lat2) - (math.sin(lat1)
                * math.cos(lat2) * math.cos(diffLong))

        initial_bearing = math.atan2(x, y)

        # Now we have the initial bearing but math.atan2 return values
        # from -180° to + 180° which is not what we want for a compass bearing
        # The solution is to normalize the initial bearing as shown below
        initial_bearing = math.degrees(initial_bearing)
        compass_bearing = (initial_bearing + 360) % 360
        return compass_bearing
    
    def getDistanceTo(self, otherPoint):
        # approximate radius of earth in km
        R = 6373.0

        lat1 = self.getLat()
        lon1 = self.getLon()
        lat2 = otherPoint.getLat()
        lon2 = otherPoint.getLon()

        dlon = lon2 - lon1
        dlat = lat2 - lat1

        a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlon / 2)**2
        c = 2 * atan2(sqrt(a), sqrt(1 - a))

        distance = R * c
        return abs(distance) #should this be abs?

    #################
    #    Getters    #
    #################

    # Get latitude
    def getLat(self):
        return self.lat
    
    # Get longitude
    def getLon(self):
        return self.lon

    # Get mode (or type) of the point
    # Possibilities: drive-over, cone, trajectory point, obstacle, endpoint
    def getMode(self):
        return self.mode

    # Get the heading coming off this point
    def getHeading(self):
        return self.heading

    # Get the velocity at this point
    def getVelocity(self):
        return self.velocity
    
    # Get the status (enroute or not?)
    def getStatus(self):
        return self.velocity

    
    #################
    #    Setters    #
    #################
    
    # Set a new latitude
    def setLat(self, newLat):
        self.lat = newLat

    # Set a new longitude
    def setLon(self, newLon):
        self.lon = newLon

    # Set a new mode for the point
    # Refer to possibilities above
    def setMode(self, mode):
        self.mode = mode

    # Set the heading at this point
    def setHeading(self, heading):
        self.heading = heading

    # Set the velocity
    def setVelocity(self, velocity):
        self.velocity = velocity

    # Set the status of the point
    def setStatus(self, status):
        self.status = status
