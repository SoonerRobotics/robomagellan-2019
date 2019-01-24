from main_board.com.serial_device import *
from main_board.com.com import SerialController
import time
from main_board.lidar.mapper import Mapper

if __name__ == '__main__':
	controller = SerialController()
	# Addresses to check, will probably automate this list at some point
	addresses = ["/dev/tty0", "/dev/tty1"]
	controller.start(addresses)

	lying_camera = Mapper()
	lying_camera.start()
