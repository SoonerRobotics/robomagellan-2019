#Errors
#Occasional GPS + IMU location
#Changes in route status (obstacle avoided, re-routing, completed waypoint)
#System data if necessary
#Any E-Stop or pause commands
#Timestamps for each log entry

#logs.py
import logging

logging.basicConfig(filename='logsTest.log', format='%(asctime)s %(levelname)s:%(message)s', datefmt='%m/%d/%Y %I:%M:%S %p', level=logging.DEBUG)
	
def systemError():
	logging.warning('There is a system error!')
	
def gpsError():
	logging.warning('GPS error!')
	
def imuError():
	logging.warning('IMU error!')	
	
def read_GPS():
	logging.info('GPS Coordinates: ')

def read_IMUCoordinates():
	logging.info('IMU Coordinates: ')	

def obstacleFound ():
	logging.info('Obstacle avoided! ')

def rerouting ():
	logging.info('Re-routing!')
	
def routeComplete ():
	logging.info('Waypoint is completed!')

def eStop ():
	logging.warning('E-stop!')

def paused ():
	logging.warning('Robot is on paused!')