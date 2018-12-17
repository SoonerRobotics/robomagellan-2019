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
