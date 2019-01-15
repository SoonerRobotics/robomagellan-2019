from main_board.com.serial_device import *
from main_board.com.com import SerialController
import time

if __name__ == '__main__':
	controller = SerialController()
	motion = MotionSerial("/dev/ttyUSB0", 115200)
	controller.add_device(motion)
	localization = LocalizationSerial("/dev/ttyUSB1", 115200)
	controller.add_device(localization)
	controller.start()

	def f(feed):
		j = json.loads(feed)
		if 'event' in j:
			return j['event'] == 'heading'
		return False
	controller.setup_passthrough(localization, motion, f)

	time.sleep(5)
	for d in controller.devices:
		controller.tx(d, "Fucking christ")
