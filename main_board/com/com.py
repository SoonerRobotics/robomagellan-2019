import serial
from serial_device import serial_device
from serial_device import serial_passthrough
import time
import multiprocessing

#Main communications class
#Author: Colton Sandvik
#Allows the creation of serial devices and passthroughs
#Manages serial traffic for parent program

class serial_controller():

	def __init__(self, process_rate = 50):
		self.devices = list()
		self.passthrough = list()
		self.process_rate = process_rate
		self.process = None
		self.stop = False

	#Main process for looping automatically, runs at process rate defined in controller instantiation, default is 50ms
	def loop_forever(self):
		while not stop:
			self.handle_serial()
			time.sleep(process_rate/1000)

	#Starts loop
	def start(self):
		self.stop = False
		for d in devices:
			d.open()
		self.process = multiprocessing.Process(target=self.loop_forever)
		self.process.start()

	#Stops loop
	def stop(self):
		self.stop = True

	#Loops just once in cases of manual looping elsewhere
	def loop(self):
		self.handle_serial()

	#Receives data for all devices and passthrough any setup passthroughs
	def handle_serial(self):
		for d in devices:
			d.rx()
		for p in passthrough:
			p.passthrough()

	#Transmit data for device; can also be done on the device itself
	def tx(self, device, writtable):
			device.tx(writtable)

	#Adds device to serial controller and returns device
	def add_device(self, address, baud):
		d = serial_device(address, baud)
		self.devices.append(d)
		return d

	#Gets serial device based on it's address
	def get_device(self, address):
		for d in self.devices:
			if d.address = address:
				return d
		return None

	#Removes serial device from serial controller
	def remove_device(self, device):
		self.devices.remove(device)

	#Establishes serial passthrough from one device to another
	#Params:
	#from_device: device that data is received from (uses the most recent serial data pull)
	#to_device: destination of serial passthrough
	#condition (optional): function that controls whether data is passed through (must return True or False for a given line read by from_device)
	#Note: best works with devices of the same baud rate will replicate data or truncate data
	# from_device baud > to_device baud --> truncates data
	# from device baud < to device baud --> replicates data
	def setup_passthrough(self, from_device, to_device, condition=None)
		p = serial_passthrough(from_device, to_device, condition)
		self.passthrough.append(p)
		return p