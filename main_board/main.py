from com.serial_device import *
from com.com import SerialController

import time
from lidar.mapper import Mapper
import multiprocessing

if __name__ == '__main__':
	daddy_pipe, com_pipe = multiprocessing.Pipe()
	controller = SerialController(daddy_pipe)
	# Addresses to check, will probably automate this list at some point
	addresses = ["/dev/ttyUSB1", "/dev/ttyUSB2"]
	controller.start(addresses)

	lying_camera = Mapper()
	lying_camera.start()
