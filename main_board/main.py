from com.serial_device import *
from com.com import SerialController

import time
from lidar.mapper import Mapper

if __name__ == '__main__':
	controller = SerialController()
	# Addresses to check, will probably automate this list at some point
	addresses = ["/dev/tty0", "/dev/tty1"]
	controller.start(addresses)

	lying_camera = Mapper()
	lying_camera.start()
