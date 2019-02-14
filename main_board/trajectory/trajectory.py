# This class constructs a trajectory for the robot to follow

# Import the point class
import copy
from config import Config
from trajectory import Point
from math import sin, cos, sqrt, atan2, radians
import numpy as np
from numpy.linalg import norm
import os

class Trajectory:

	# Initialize the trajectory builder
	def __init__(self):
		# TODO: make -1 an invalid point in point()
		self.robotPoint = Point(0, 0, -1)
		self.active_wpt = 0
		self.cur_traj_point = 0 
		self.traj_points = list()
		self.waypoints = list()

		###################
		# Add config vars #
		###################
		cfg = Config()

		# Accepted closeness to point to accept as "reached" (in meters)
		# This only applies to non-cone points. Cone points must be touched
		self.ACCEPTED_DISTANCE_WITHIN_GOAL = cfg['trajectory']['goal_dist_thresh']

		# Max Deviation allowed off of heading while heading to goal (in degrees)
		self.ACCEPTED_HEADING_DEVIATION = cfg['trajectory']['goal_heading_thresh']      

		# Max Deviation allowed off of paths (in meters)
		self.PATH_DEVIATION_ALLOWED = cfg['trajectory']['max_deviation']

		self.MAX_STEER_ANG = cfg['Robot']['max_steer_ang']          

	# There must be a point behind the robot (or on it) for calculations that require a previous trajectory point
	def build_trajectory(self):
		#TODO: This is just rudimentary point-to-point. This needs to use the intelligent curved pathing stuff 
		for wp in self.waypoints:
			tp = wp
			tp.setMode("T")
			self.traj_points.append(tp)

	def update_trajectory(self):
		pass

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
					newPoint = Point(lat, lon, mode)
					self.waypoints.append(newPoint)

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
	def getDistance(self, lat, lon, point):
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

	# Get the distance from point (x0,y0) to a line described by points (x1,y1) and (x2,y2)
	# Possible improvements with dot products, etc.
	def distanceFromPointToLine(self,x1,y1,x2,y2,x0,y0):
		return abs((y2-y1)*x0-(x2-x1)*y0+x2*y1-y2*y1)/(sqrt((y2-y1)**2 + (x2-x1)**2))

	# Update position
	def updatePosition(self, lat, lon, velocity, heading):
		self.robotPoint.setLat(lat)
		self.robotPoint.setLon(lon)
		self.robotPoint.setVelocity(velocity)
		self.robotPoint.setHeading(heading)

		if (self.robotPoint.getDistanceTo(self.traj_points[self.cur_traj_point]) < self.ACCEPTED_DISTANCE_WITHIN_GOAL and
				self.traj_points[self.cur_traj_point].mode not in ["B", "S", "E"] and 
				abs(self.robotPoint.getHeadingTo(self.traj_points[self.cur_traj_point]) - heading) < self.ACCEPTED_HEADING_DEVIATION):
			#all conditions are met to accept a goal
			self.curPoint = self.curPoint + 1
			return

		#calculate distance from path for path deviation
		last_point = self.traj_points[self.cur_traj_point-1]
		cur_point = self.traj_points[self.cur_traj_point]
		if self.distanceFromPointToLine(last_point.getLat(), last_point.getLon(), cur_point.getLat(), cur_point.getLon(), lat, lon) < self.PATH_DEVIATION_ALLOWED:
			#TODO: Decide how to recalculate trajectory if we are off the course too significantly
			pass
		

	# Check LIDAR for obstacles
	def checkLIDAR(self, lidarpoints):
		#TODO: If lidarpoints contains a point in front of us, we need to repath
		pass
	
	# Check Sonar for close obstacles
	def checkSonar(self, distance):
		#TODO: Given sonar distance, do we need to repath?
		pass

	# Check Limit Switch for collisions
	def checkLimitSwitch(self, touched):
		# If we are touching something and we are supposed to head to a cone, we hit it!
		if touched and self.waypoints[self.curPoint].mode in ["B", "S", "E"]:
			self.curPoint = self.curPoint + 1
		# If we are touching something, and it is not the cone, back up and avoid this obstacle
		elif touched:
			# TODO: recalculate route
			pass

	# Get next point
	def getHeading(self):
		return self.robotPoint.getHeadingTo(self.traj_points[self.cur_traj_point])

	# Get steering andgle
	def getSteeringAngle(self, heading, length, vel):
		return min(self.MAX_STEER_ANG, atan2((heading - (self.getHeading()) * length) / (vel)))

	# Get desired speed
	def getPower(self):
		oldVel = self.traj_points[self.curPoint - 1].getVelocity()
		newVel = self.traj_points[self.curPoint].getVelocity()
		distancePercent = (self.traj_points[self.curPoint].getDistanceTo(self.traj_points[self.cur_traj_point-1]) / self.traj_points[self.cur_traj_point - 1].getDistanceTo(self.traj_points[self.cur_traj_point]))
		return ((1 - distancePercent) * oldVel + distancePercent * newVel) / (11.11) # assumes power 1 is 11.11 m/s

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
			coord = "\t\t\t<latitude>" + str(self.traj_points[0].getLat()) + "</latitude>\n\t\t\t<longitude>" + str(self.traj_points[0].getLon()) + "</longitude>\n"
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
			for i in range(0, len(self.traj_points)):
				#This MUST be lon, lat because that's what google earth expects
				coord = "\t\t\t\t" + str(self.traj_points[i].getLon()) + "," + str(self.traj_points[i].getLat()) + ",20\n"
				self.kml.write(coord)

			# Finish writing to the file
			self.kml.write("\t\t\t\t</coordinates>\n")
			self.kml.write("\t\t\t</LineString>\n")
			self.kml.write("\t\t</Placemark>\n")

			#Place markers to show info about points on path
			for i in range(0, len(self.traj_points)):
				#Place a marker at the point
				self.kml.write("\t\t\t\t<Placemark>\n\t\t\t\t\t<Point>\n\t\t\t\t\t\t<coordinates>\n")

				#This MUST be lon, lat because that's what google earth expects
				coord = "\t\t\t\t\t\t" + str(self.traj_points[i].getLon()) + "," + str(self.traj_points[i].getLat()) + ",20\n"
				self.kml.write(coord)

				self.kml.write("\t\t\t\t\t\t</coordinates>\n\t\t\t\t\t</Point>\n\t\t\t\t</Placemark>\n")

			self.kml.write("\t</Document>\n")
			self.kml.write("</kml>\n")

			# Close the KML export file
			self.kml.close()
