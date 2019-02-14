import serial
from com.serial_device import *
import time
import multiprocessing
from multiprocessing import Queue
import logging
import json
import trajectory.trajectory as trajectory
from config import config


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

	def __init__(self, daddy_pipe, trajectory, process_rate=50):
		self.daddy_pipe = daddy_pipe
		logging.Formatter.converter = time.gmtime
		logging.basicConfig(filename="/var/log/serial_communication.log", level=logging.INFO,
								 format='%(asctime)s:%(message)s ')
		self.devices = list()
		self.birth_devices = list()
		self.passthrough = list()
		self.process_rate = process_rate
		self.process = None
		self.sensor_data = dict()
		self.stop = False
		self.state = 0
		self.traj = trajectory
		self.buffer = Queue()
		self.cfg = config.Config()


	# Main process for looping automatically, runs at process rate defined in controller instantiation, default is 50ms
	def loop_forever(self):
		while not self.stop:
			if self.daddy_pipe.poll():
				event = self.daddy_pipe.recv()
				if event['event'] == 'state':
					self.state = event['data']['state']
					logging.info("State manually changed to %s for SerialController" % (self.state))
				elif event['event'] == 'kalman_init':
					self.ekf_pipe = event['data']
				elif event['event'] == 'mapping_init':
					self.mapping_pipe = event['data']

			# Birth packets
			if self.state == 0 or len(self.birth_devices) == 0:
				for device in self.birth_devices:
					if device.check_response():
						logging.info(
                            "Device %s detected at address %s, creating now..." % (device.address, device.new_id))
						new_device = self.fetch_device(device, device.new_id)
						self.birth_devices.remove(device)
						# self.daddy_pipe.send(new_device)

			# Regular operations
			elif self.state == 1:
				# Read serial data
				self.handle_serial(remove_from_queue=True)

				# TODO: Parse data
				new_sensor_data = False

				# Only send data to the EKF if there is a pipe set up for it
				if self.ekf_pipe:
					# Check for the most recent update on this end of the pipe
					while self.ekf_pipe.poll():
						self.state_data = self.ekf_pipe.recv()

					# If there's new measurement data, send in that data
					if new_sensor_data:
						self.ekf_pipe.send(self.sensor_data)

				# Get most recent mapping data
				if self.mapping_pipe:
					self.map_data = self.mapping_pipe.recv()

				# The decision (https://www.youtube.com/watch?v=2_LUnTQHV4c)
				# Three possibilities
				# 1. Everything is normal, just read the trajectory data to make the robot move
				# 2. The robot is near a cone, so turn on the camera and make it hit the cone
				# 3. The robot is going to hit an obstacle, so don't let that happen
				
				# Obstacle avoid
				# TODO: Actually implement obstacle avoidance (using json?)
				if self.map_data[0] < -1000:
					pass
				# Check to see if the robot is near a cone
				elif False: #self.traj.getDistance(self.state_data[0], self.state_data[1], self.traj.robotPoint):
					pass
				# Otherwise do normal operation
				else:
					# Get the steering angle and power
					# TODO: configure robot length globally
					self.steer_ang = self.traj.getSteeringAngle(self.state_data[4], 0.333, self.state_data[2])
					self.power = self.traj.getPower()
					
					# Form the motion data packet
					motion_pkt = self.make_motion_packet(False, self.steer_ang, self.power, 0, 0)
					
					# Send commands to motion device
					self.tx(self.get_device(1), motion_pkt)

				time.sleep(self.process_rate / 1000)

	# Determine device to create based off id
	def fetch_device(self, d, did):
		if did == 1:
			new_d = MotionSerial(d.address, d.baud, s=d.ser)
			logging.info("Motion Serial created")
		elif did == 2:
			new_d = LocalizationSerial(d.address, d.baud, s=d.ser)
			logging.info("Localization Serial created")
		self.devices.append(new_d)
		return new_d

	# Starts loop
	def start(self, addresses):
		self.stop = False
		logging.info("Starting Serial Controller")
		for a in addresses:
			self.birth_devices.append(SerialBirther(a, 115200))
		logging.info("Birth Devices initialized")
		self.process = multiprocessing.Process(target=self.loop_forever)
		self.process.start()

	# Loops just once in cases of manual looping elsewhere
	def loop(self):
		try:
			self.handle_serial()
		except Exception as e:
			logging.info(e)

	# Receives data for all devices and pass through any setup passthroughs
	def handle_serial(self, remove_from_queue=False):
		for d in self.devices:
			try:
				d.execute_commands()
				msg = d.rx(remove_from_queue=remove_from_queue)
				d.parse_rx(msg)
			except Exception as e:
				logging.info(e)

		for p in self.passthrough:
			try:
				p.passthrough()
			except Exception as e:
				logging.info(e)

	# Transmit data for device; can also be done on the device itself
	def tx(self, device, writtable):
		try:
			device.tx(writtable)
		except Exception as e:
			logging.info(e)

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
			logging.info(e)

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
			logging.info("Passthrough established from %s to %s" % (from_device.address, to_device.address))
		except Exception as e:
			logging.info(e)
		self.passthrough.append(p)
		return p

	# Make a packet to send to the motion board
	def make_motion_packet(self, near_cone, steer_ang, power, opencv_err, cone_vis):
		# Populate the data packet
		data = dict()
		data["gps_near_cone"] = near_cone
		data["steer_ang"] = steer_ang
		data["traj_power"] = power
		data["opencv_error"] = opencv_err
		data["opencv_cone_visible"] = cone_vis

		# Construct the packet
		packet = dict()
		packet["id"] = 2
		packet["event"] = "full_update"
		packet["data"] = data

		# Get the json string, remove newlines
		json_str = json.dumps(packet)

		return json_str