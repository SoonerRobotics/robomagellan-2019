from com.serial_device import *
from com.com import SerialController

import configparser
import numpy as np
import time
from lidar.mapper import Mapper
import multiprocessing

# EKF
from kalman.kalman_filter import kalman_filter

if __name__ == '__main__':
    # Open the pipes for the main process
	daddy_pipe, com_pipe = multiprocessing.Pipe()
	controller = SerialController(daddy_pipe)
    
    # Get the robot configuration data
	config = configparser.ConfigParser()
	config.read('config.ini')

	# Addresses to check, will probably automate this list at some point
	addresses = ["/dev/ttyUSB1", "/dev/ttyUSB2"]
	controller.start(addresses)

	lying_camera = Mapper()
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
	# MAP_dict = {'event':'mapping_init', 'data': lying_camera.getPipe()}

	# Run the separate process as long as the first element in the queue is not 'exit'
	while True:
	    # Send data to the EKF process
	    # NOTE: data should be a dict of sensor data
	    pass

	proc.join()
