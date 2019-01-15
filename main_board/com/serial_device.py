import serial
import json

# Serial Device and Passthrough Classes
# Author: Colton Sandvik


class SerialDevice:

	def __init__(self, address, baud):
		self.address = address
		self.baud = baud
		self.read_queue = list()
		self.status = "Closed"
		self.id = 0
		self.birth_packet = """
		{
			device_id: 0,
			name: "Main board",
			event: "birth",
			data: []
		}
		"""
		try:
			self.ser = serial.Serial(
				port=self.address,
				baudrate=baud,
				parity=serial.PARITY_NONE,
				stopbits=serial.STOPBITS_ONE,
				bytesize=serial.EIGHTBITS,
				timeout=1,
				write_timeout=10
			)
		except Exception as e:
			raise e
			self.ser = None

	def open(self):
		try:
			self.ser.open()
			self.status = "Opened"
			self.tx(self.birth_packet)
			return True
		except Exception as e:
			raise e
			return False

	def close(self):
		try:
			self.ser.close()
			self.status = "Closed"
			return True
		except Exception as e:
			raise e
			return False

	# Reads line already pulled from device and stored in queue
	def readline(self, release=True):
		if len(self.read_queue) != 0:
			t = self.read_queue[0]
			if release:
				self.finish_read()
			return t
		else:
			return ""

	# Releases data from queue, by default is done after readline
	def finish_read(self):
		if len(self.read_queue) != 0:
			del self.read_queue[0]

	# Receives data and returns if queue is to be skipped
	def rx(self, remove_from_queue=False):
		try:
			l = self.ser.readline()
			if not remove_from_queue:
				self.read_queue.append(l)
			else:
				return l
		except serial.SerialException as e:
			raise e

	# Transmits data down device pipeline can take any object, no conversions necessary
	def tx(self, writtable):
		if isinstance(writtable, dict):
			try:
				self.ser.write(json.dumps(writtable) + '\n')
			except serial.SerialException as e:
				raise e
		elif isinstance(writtable, str):
			try:
				self.ser.write(writtable.encode('ascii'))
				print("Transmitting to %s: %s" % (self.address, writtable))
			except serial.SerialException as e:
				raise e
		else:
			try:
				self.ser.write(bytes(str(writtable) + '\n', 'ascii'))
			except serial.SerialException as e:
				raise e

	def parse_rx(self, msg):
		pass


# Serial Passthrough class
class SerialPassthrough:

	def __init__(self, from_device, to_device, condition=None):
		self.from_device = from_device
		self.to_device = to_device
		if condition is not None:
			self.condition = condition
		else:
			self.condition = lambda feed : True

	# Passes data through without releasing it
	# If condition is set it will only send data to destination if condition is true
	def passthrough(self):
		try:
			feed = self.from_device.readline(release=False)
		except Exception as e:
			raise e
		if self.condition(feed):
			self.to_device.tx(feed)
		return feed

# Creating Communication Endpoint
# Create class that extends the serial_device base class
# Override the parse_rx method to convert the stringified JSON from the device into the standardized JSON command
# structure exampled below:
# {
#	device_id: 0,
#	name: "Motion",
#	event: "motion_collect",
#	data: {
#		x: 20,
#		accel: 0.6
#	}
# }
# This may eventually be automated but is good enough for now.

# WIP Motion Endpoint


class MotionSerial(SerialDevice):

	def __init__(self, address, baud):
		SerialDevice.__init__(self, address, baud)
		self.id = 1

	def parse_rx(self, msg):
		j = json.loads(msg)


class LocalizationSerial(SerialDevice):

	def __init__(self, address, baud):
		SerialDevice.__init__(self, address, baud)
		self.id = 2

	def parse_rx(self, msg):
		j = json.loads(msg)
