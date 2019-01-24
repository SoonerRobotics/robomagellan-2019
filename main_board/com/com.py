import serial
from main_board.com.serial_device import SerialDevice
from main_board.com.serial_device import SerialPassthrough
import time
import multiprocessing
import queue

# Main communications class
# Author: Colton Sandvik
# Allows the creation of serial devices and passthroughs
# Manages serial traffic for parent program
# Serial Device IDs:
# 0 - Main Board
# 1 - Motion
# TODO Make birth packets go off whenever we receive birth packet from parent device, register id
# TODO Also... make it dynamically change the device...

class SerialController:

	def __init__(self, process_rate=50):
		self.logging.Formatter.converter = time.gmtime
		self.logging.basicConfig(filename="/var/log/serial_communication.log", level=self.logging.INFO, format='%(asctime)s:%(message)s ')
		self.devices = list()
		self.passthrough = list()
		self.process_rate = process_rate
		self.process = None
		self.stop = False
		self.buffer = queue()

	# Main process for looping automatically, runs at process rate defined in controller instantiation, default is 50ms
	def loop_forever(self):
		while not self.stop:
			self.handle_serial(remove_from_queue=True)
			time.sleep(self.process_rate/1000)

	# Starts loop
	def start(self):
		self.stop = False
		for d in self.devices:
			d.close()
			s = d.open()
			# d.ser.reset_output_buffer()
			if not s:
				try:
					self.devices.remove(d)
				except Exception as e:
					self.logging.info(e)
			try:
				d.tx(d.birth_packet)
			except Exception as e:
				self.logging.info(e)
		self.process = multiprocessing.Process(target=self.loop_forever)
		self.process.start()

	# Stops loop
	def stop(self):
		self.stop = True

	# Loops just once in cases of manual looping elsewhere
	def loop(self):
		try:
			self.handle_serial()
		except Exception as e:
			self.logging.info(e)

	# Receives data for all devices and pass through any setup passthroughs
	def handle_serial(self, remove_from_queue=False):
		for d in self.devices:
			try:
				d.execute_commands()
				msg = d.rx(remove_from_queue=remove_from_queue)
				d.parse_rx(msg)
			except Exception as e:
				self.logging.info(e)

		for p in self.passthrough:
			try:
				p.passthrough()
			except Exception as e:
				self.logging.info(e)

	# Transmit data for device; can also be done on the device itself
	def tx(self, device, writtable):
		try:
			device.tx(writtable)
		except Exception as e:
			self.logging.info(e)

	# Adds device to serial controller and returns device
	def add_device(self, d):
		if d.ser is not None:
			self.devices.append(d)
		return d

	# Gets serial device based on it's address
	def get_device(self, address):
		for d in self.devices:
			if d.address == address:
				return d
		return None

	# Removes serial device from serial controller
	def remove_device(self, device):
		try:
			self.devices.remove(device)
		except Exception as e:
			self.logging.info(e)

	# Establishes serial passthrough from one device to another
	# Params:
	# from_device: device that data is received from (uses the most recent serial data pull)
	# to_device: destination of serial passthrough
	# condition (optional): function that controls whether data is passed through (must return True or False for a given
	# line read by from_device)
	# Note: best works with devices of the same baud rate will replicate data or truncate data
	# from_device baud > to_device baud --> truncates data
	# from device baud < to device baud --> replicates data
	def setup_passthrough(self, from_device, to_device, condition=None):
		try:
			p = SerialPassthrough(from_device, to_device, condition)
		except Exception as e:
			self.logging.info(e)
		self.passthrough.append(p)
		return p
