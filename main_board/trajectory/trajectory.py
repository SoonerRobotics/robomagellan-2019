# This class constructs a trajectory for the robot to follow

# Import the point class
from point import point
import os

class trajectory:

    # Initialize the trajectory builder
    def __init__(self):
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
        decimal = degree + (minute / 60) * dirs.get(direction, 1)
        return decimal

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
            self.kml.write("\t\t\t<color>ffff0000</color>\n")
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
            self.kml.write("\t\t\t<range>2000</range>\n")
            self.kml.write("\t\t</LookAt>\n")
            self.kml.write("\t\t<styleUrl>#SCR</styleUrl>\n")
            self.kml.write("\t\t\t<LineString>\n")
            self.kml.write("\t\t\t\t<extrude>1</extrude>\n")
            self.kml.write("\t\t\t\t<tessellate>1</tessellate>\n")
            self.kml.write("\t\t\t\t <altitudeMode> relativeToGround </altitudeMode>\n")
            self.kml.write("\t\t\t\t<coordinates>\n")

            # Write all current coordinates here in the file
            for i in range(0, len(self.points)):
                coord = "\t\t\t\t" + str(self.points[i].getLat()) + ", " + str(self.points[i].getLon()) + ", 2000\n"
                self.kml.write(coord)

            # Finish writing to the file
            self.kml.write("\t\t\t\t</coordinates>\n")
            self.kml.write("\t\t\t</LineString>\n")
            self.kml.write("\t\t</Placemark>\n")
            self.kml.write("\t</Document>\n")
            self.kml.write("</kml>\n")

            # Close the KML export file
            self.kml.close()