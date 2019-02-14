from com.serial_device import *
from com.com import SerialController
import trajectory.trajectory as trajectory
import trajectory.point as point
import configparser
import numpy as np
import time
from lidar.mapper import Mapper
import multiprocessing
import logging

LOGGING_LEVEL = logging.INFO

# EKF
from kalman.kalman_filter import kalman_filter

if __name__ == '__main__':

	logging.Formatter.converter = time.gmtime
	logging.basicConfig(filename="/var/log/magellan.log", level=LOGGING_LEVEL,
						format='%(asctime)s:%(message)s ')

	# Get the robot configuration data
	config = configparser.ConfigParser()
	config.read('config.ini')

	# Build the trajectory
	traj = trajectory.Trajectory(config)
	traj.loadWaypoints('trajectory/waypoints_quad.txt', True)
	traj.build_trajectory()
	traj.exportToKML('trajectory/most_recent_course.kml')

	# Open the pipes for the main process
	daddy_pipe, com_pipe = multiprocessing.Pipe()
	controller = SerialController(daddy_pipe, traj)

	# Addresses to check, will probably automate this list at some point
	addresses = ["/dev/ttyUSB1", "/dev/ttyUSB2"]
	controller.start(addresses)

	daddy_pipe, map_pipe = multiprocessing.Pipe()
	lying_camera = Mapper(daddy_pipe)
	lying_camera.start()

	# Make an initial state
	xo = np.array(config['EKF']['start_lat'], config['EKF']['start_lon'], 0, 0, 0, 0)
	Po = np.eye(6) * 0.2    # TODO: choose an actual initial uncertainty

	# Set up the kalman filter
	EKF = kalman_filter(xo, Po, config)

	# Set up EKF piping system
	main_pipe, ekf_pipe = multiprocessing.Pipe(True)

	# Start the EKF process
	proc = multiprocessing.Process(target = EKF.process_data, args = (ekf_pipe,))
	proc.start()

	# Set the pipe in the main process to be the main pipe declared above
	EKF_dict = {'event':'kalman_init', 'data': main_pipe}
	com_pipe.send(EKF_dict)

	# Set the pipe for the mapper to the main process
	MAP_dict = {'event':'mapping_init', 'data': map_pipe}

	# Run the separate process as long as the first element in the queue is not 'exit'
	while True:
	    # Send data to the EKF process
	    # NOTE: data should be a dict of sensor data
	    pass

	proc.join()
