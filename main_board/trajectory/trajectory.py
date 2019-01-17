# This class constructs a trajectory for the robot to follow

# Import the point class
from point import point
from math import sin, cos, sqrt, atan2, radians
import numpy as np
import os

class trajectory:

    # Max Deviation allowed off of paths (in meters)
    PATH_DEVIATION_ALLOWED = 2

    # Accepted closeness to point to accept as "reached" (in meters)
    # This only applies to non-cone points. Cone points must be touched
    ACCEPTED_DISTANCE_WITHIN_GOAL = 1

    # Initialize the trajectory builder
    def __init__(self):
        self.curLocation = (0,0)
        self.numPoints = 0
        self.curPoint = 0
        self.points = []

    # Load the base waypoints from a file
    def loadWaypoints(self, filename, convert):        
        # Open the file
        self.file = open(filename, 'r')

        # If opening was successful, read the file
        if self.file.mode == 'r':
            # Read the file line by line
            while True:
                # Read a line
                line = self.file.readline()

                # Stop reading on EOF
                if line == '':
                    break
                # Parse input if not EOF
                else:
                    # Get the position data for the path
                    data = line.split(' ')
                    
                    # Convert the position data to decimal coords if needed
                    if convert == True:
                        lat = self.convertCoordinate(data[0], float(data[1]), float(data[2]))
                        lon = self.convertCoordinate(data[3], float(data[4]), float(data[5]))
                        mode = data[6]
                    # Otherwise, everything is in decimal already
                    else:
                        lat = data[0]
                        lon = float(data[1])
                        mode = float(data[2])

                    # Add a waypoint to the trajectory
                    newPoint = point(lat, lon, mode)
                    self.points.append(newPoint)

            numPoints = len(points)

            # Close the file
            self.file.close()

    # Converts DMS coordinates to decimals
    def convertCoordinate(self, direction, degree, minute):
        # Dictionary defining sign of coordinate system
        dirs = {
            'N': 1,
            'n': 1,
            'E': 1,
            'e': 1,
            'S': -1,
            's': -1,
            'W': -1,
            'w': -1
        }

        # Convert DMS to decimal
        decimal = (degree + (minute / 60)) * dirs.get(direction, 1)
        return decimal

    # Get the distance between a point and a coordinate pair
    def getDistance(lat, lon, point):
        # approximate radius of earth in km
        R = 6373.0

        lat1 = lat
        lon1 = lon
        lat2 = point.getLat()
        lon2 = point.getLon()

        dlon = lon2 - lon1
        dlat = lat2 - lat1

        a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlon / 2)**2
        c = 2 * atan2(sqrt(a), sqrt(1 - a))

        distance = R * c
        return distance

    # Update position
    def updatePosition(self, lat, lon):
        self.curLocation = (lat, lon)
        if self.getDistance(lat, lon, self.point[self.curPoint]) < self.ACCEPTED_DISTANCE_WITHIN_GOAL:
            curPoint++
            return

        p1 = (self.points[self.curPoint-1].getLat(), self.points[self.curPoint-1].getLon())
        p2 = (self.points[self.curPoint].getLat(), self.points[self.curPoint].getLon())
        if np.abs(np.cross(p2-p1, p1-self.curLocation)) / norm(p2-p1)) > self.PATH_DEVIATION_ALLOWED:
            #TODO We have deviated too far, do we need to path intelligently back on, or can we just go straight to next point?

    # Get next point
    def getHeading(self):
        #TODO: Calculate the heading we need to travel at to reach the next point. This should take into account self.curLocation and the current point

    # Get desired speed
    def getPower(self):
        #TODO: Calculate the power (speed) we should travel at to reach the next point

    # Export the current trajectory to KML format
    def exportToKML(self, kml):
        # Open a file for writing
        self.kml = open(kml, 'w')

        # If the file opened successfully
        if self.kml.mode == 'w':
            # Write the KML header stuff:
            self.kml.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
            self.kml.write("<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n")
            self.kml.write("\t<Document>\n")
            self.kml.write("\t<Style id=\"SCR\">\n")
            self.kml.write("\t\t<LineStyle>\n")
            self.kml.write("\t\t\t<color>ff0000ff</color>\n")
            self.kml.write("\t\t\t<width>1</width>\n")
            self.kml.write("\t\t</LineStyle>\n")
            self.kml.write("\t\t<PolyStyle>\n")
            self.kml.write("\t\t\t<color>ff0000ff</color>\n")
            self.kml.write("\t\t</PolyStyle>\n")
            self.kml.write("\t</Style>\n")
            self.kml.write("\t\t<Placemark>\n")
            self.kml.write("\t\t\t<name>Robot Path</name>\n")
            self.kml.write("\t\t\t<visibility>1</visibility>\n")
            self.kml.write("\t\t<LookAt>\n")

            # Write the first point to the look-at property
            coord = "\t\t\t<latitude>" + str(self.points[0].getLat()) + "</latitude>\n\t\t\t<longitude>" + str(self.points[0].getLon()) + "</longitude>\n"
            self.kml.write(coord)

            # Continue writing setup markup
            self.kml.write("\t\t\t<altitude>0</altitude>\n")
            self.kml.write("\t\t\t<heading>0</heading>\n")
            self.kml.write("\t\t\t<tilt>0</tilt>\n")
            self.kml.write("\t\t\t<range>200</range>\n")
            self.kml.write("\t\t</LookAt>\n")
            self.kml.write("\t\t<styleUrl>#SCR</styleUrl>\n")
            self.kml.write("\t\t\t<LineString>\n")
            self.kml.write("\t\t\t\t<extrude>1</extrude>\n")
            self.kml.write("\t\t\t\t<tessellate>1</tessellate>\n")
            self.kml.write("\t\t\t\t<altitudeMode> relativeToGround </altitudeMode>\n")
            self.kml.write("\t\t\t\t<coordinates>\n")

            # Write all current coordinates here in the file
            for i in range(0, len(self.points)):
                #This MUST be lon, lat because that's what google earth expects
                coord = "\t\t\t\t" + str(self.points[i].getLon()) + "," + str(self.points[i].getLat()) + ",20\n"
                self.kml.write(coord)

            # Finish writing to the file
            self.kml.write("\t\t\t\t</coordinates>\n")
            self.kml.write("\t\t\t</LineString>\n")
            self.kml.write("\t\t</Placemark>\n")

            #Place markers to show info about points on path
            for i in range(0, len(self.points)):
                #Place a marker at the point
                self.kml.write("\t\t\t\t<Placemark>\n\t\t\t\t\t<Point>\n\t\t\t\t\t\t<coordinates>\n")

                #This MUST be lon, lat because that's what google earth expects
                coord = "\t\t\t\t\t\t" + str(self.points[i].getLon()) + "," + str(self.points[i].getLat()) + ",20\n"
                self.kml.write(coord)

                self.kml.write("\t\t\t\t\t\t</coordinates>\n\t\t\t\t\t</Point>\n\t\t\t\t</Placemark>\n")

            self.kml.write("\t</Document>\n")
            self.kml.write("</kml>\n")

            # Close the KML export file
            self.kml.close()