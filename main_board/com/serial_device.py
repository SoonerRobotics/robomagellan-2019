import serial
import json
from multiprocessing import Queue
import logging
# Serial Device and Passthrough Classes
# Author: Colton Sandvik


class SerialDevice:

	def __init__(self, address, baud, s=None):
		self.address = address
		self.baud = baud
		self.read_queue = list()
		self.command_queue = Queue()
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
			if s is not None:
				self.ser = s
			else:
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
			logging.debug("Opened serial port at %s" % self.address)
			self.tx(bytes(self.birth_packet))
			return True
		except Exception as e:
			raise e
			return False

	def close(self):
		try:
			self.ser.close()
			self.status = "Closed"
			logging.debug("Closed serial port at %s" % self.address)
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

	# Must be implemented on a per device basis
	# Executes commands that are in the command queue, executed every time main com thread loops
	def execute_commands(self):
		pass

	# Gets the command queue to send commands/variable data to
	def get_command_queue(self):
		return self.command_queue

	# Releases data from queue, by default is done after readline
	def finish_read(self):
		if len(self.read_queue) != 0:
			del self.read_queue[0]

	# Receives data and returns if queue is to be skipped
	def rx(self, remove_from_queue=False):
		try:
			l = self.ser.readline()
			l = l.decode('ascii')
			logging.debug("Rx %s: %s" % (self.id, l))
			if not remove_from_queue:
				self.read_queue.append(l)
			else:
				return l
		except serial.SerialException as e:
			logging.info(e)
			return None

	# Transmits data down device pipeline can take any object, no conversions necessary
	def tx(self, writtable):
		if isinstance(writtable, dict):
			try:
				logging.debug("Tx %s: %s" % (self.id, str(writtable)))
				self.ser.write(json.dumps(writtable) + '\n')
			except serial.SerialException as e:
				logging.info(e)
		elif isinstance(writtable, str):
			try:
				logging.debug("Tx %s: %s" % (self.id, writtable))
				self.ser.write(writtable.encode('ascii'))
			# print("Transmitting to %s: %s" % (self.address, writtable))
			except serial.SerialException as e:
				logging.info(e)
		else:
			try:
				logging.debug("Tx %s: %s" % (self.id, str(writtable)))
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


class SerialBirther:

	def __init__(self, address, baud):
		self.address = address
		self.baud = baud
		self.status = "Closed"
		self.id = 0
		self.birthed = False
		self.new_id = -1
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
			self.ser.write(self.birth_packet.encode("ascii"))
		except Exception as e:
			raise e
			self.ser = None

	def check_response(self):
		if self.ser.inWaiting():
			line = self.ser.readline().decode("ascii")
			logging.info("Birth response received for %s: %s" % (self.address, line))
			if line != "":
				self.birthed = True
				payload = json.loads(line)
				self.new_id = payload['id']
		return self.birthed

	def close(self):
		self.ser.close()

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

	def __init__(self, address, baud, s=None):
		SerialDevice.__init__(self, address, baud, s)
		self.id = 1

	def parse_rx(self, msg):
		j = json.loads(msg)

	def execute_commands(self):
		c = self.command_queue.get()
		logging.debug("Command received for Motion Serial : %s" % c)
		event = c['event']


class LocalizationSerial(SerialDevice):

	def __init__(self, address, baud, s=None):
		SerialDevice.__init__(self, address, baud, s)
		self.id = 2

	def parse_rx(self, msg):
		j = json.loads(msg)

	def execute_commands(self):
		c = self.command_queue.get()
		logging.debug("Command received for Motion Serial : %s" % c)
		event = c['event']
