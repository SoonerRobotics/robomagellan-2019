import sys
import serial
import json

#Serial Device and Passthrough Classes
#Author: Colton Sandvik

class serial_device():

	def __init__(self, address, baud):
		self.address = address
		self.baud = baud
		self.read_queue = list()
		ser = serial.Serial(
			port=address,
        	baudrate = baud,
        	parity=serial.PARITY_NONE,
        	stopbits=serial.STOPBITS_ONE,
        	bytesize=serial.EIGHTBITS,
        	timeout=1
        )

	#Reads line already pulled from device and stored in queue
	def readline(self, release=True):
		if len(self.read_queue) != 0:
			t = self.read_queue[0]
			if release:
				self.finish_read()
			return self.read_queue[0]
		else:
			return ""

	#Releases data from queue, by default is done after readline
	def finish_read(self):
		if len(self.read_queue) != 0:
			del self.read_queue[0]

	#Receives data and returns if queue is to be skipped
	def rx(self, remove_from_queue=False):
		try:
			l = self.ser.readline(release=False)
			if not remove_from_queue:
				self.read_queue.append(l)
			else:
				return l
		except serial.SerialException as e:
			print(e)

	#Transmits data down device pipeline can take any object, no conversions necessary
	def tx(self, writtable):
		if isinstance(writtable, dict):
			try:
				self.ser.write(json.dumps(writtable) + '\n')
			except serial.SerialException as e:
				print(e)
		elif isinstance(writtable, str):
			try:
				self.ser.write(writtable)
			except serial.SerialException as e:
				print(e)
		else:
			try:
				self.ser.write(str(writtable) + '\n')
			except serial.SerialException as e:
				print(e)


#Serial Passthrough class
class serial_passthrough():

	def __init__(self, from_device, to_device, condition=None):
		self.from_device = from_device
		self.to_device = to_device
		if condition is not None:
			self.condition = condition
		else:
			self.condition = lambda feed : True

	#Passes data through without releasing it
	#If condition is set it will only send data to destination if condition is true
	def passthrough(self):
		feed = self.from_device.readline(release=False)
		if self.condition(feed):
			self.to_device.tx(feed)
		return feed