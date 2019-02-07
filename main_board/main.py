from com.serial_device import *
from com.com import SerialController

import time
from lidar.mapper import Mapper
import multiprocessing
import logging

LOGGING_LEVEL = logging.INFO

if __name__ == '__main__':
	logging.Formatter.converter = time.gmtime
	logging.basicConfig(filename="/var/log/magellan.log", level=LOGGING_LEVEL,
						format='%(asctime)s:%(message)s ')
	daddy_pipe, com_pipe = multiprocessing.Pipe()
	controller = SerialController(daddy_pipe)
	# Addresses to check, will probably automate this list at some point
	addresses = ["/dev/ttyUSB1", "/dev/ttyUSB2"]
	controller.start(addresses)

	daddy_pipe, map_pipe = multiprocessing.Pipe()
	lying_camera = Mapper(daddy_pipe)
	lying_camera.start()
