# This file will run the LiDAR scanner, collect data and generate a map
# of the environment while the robot is running. This is the LiDAR driver
# and will be used for obstacle avoidance and SLAM

# Import the lidar device, timing variables and other libraries
import csv
from datetime import datetime
from lidar import lidar
import numpy as np
import sys
import time
from multiprocessing import Process, Pipe
import sys
from picamera import PiCamera
from opencv.conecv import ConePipeline
from picamera.array import PiRGBArray
import time
import logging
import io


# Program constants
UPDATE_PERIOD = 2   # seconds to wait before saving another log to the file
lidar_port = "/dev/ttyUSB0"  # default port for the scanner module

# If there's a port passed as a command line argument, update the port info
if len(sys.argv) > 1:
    lidar_port = sys.argv[1]

# Set up the scanner on a given port, and at the required baud rate of 128000

# Create a log file name based on the start time of the run
map_filename = "LiDAR_mapping_log_" + str(datetime.utcnow()).replace(' ', '_').replace(':', '_') + ".csv"


# Scan the environment while the robot is running
class Mapper(Process):
    def __init__(self, daddy_pipe):
        Process.__init__(self)
        self.scanner = lidar.Lidar(lidar_port, 128000)
        self.run_start_time = time.time()
        self.last_time = self.run_start_time
        self.cur_time = self.run_start_time
        # Start scanning the environment
        self.obstacle = False
        self.scanner.startScan()
        self.camera = PiCamera()
        logging.info("PiCamera initialized")
        self.camera.resolution = (640, 480)
        self.camera.framerate = 5
        self.camera_enabled = False
        self.stream = PiRGBArray(self.camera, size=(640, 480))
        # This is the proper python syntax and terminology pls don't change
        self.daddy_pipe = daddy_pipe

    def run(self):
        logging.info("Mapper is starting")
        while True:
            # Get the current time
            if self.daddy_pipe.poll():
                event = self.daddy_pipe.recv()
                logging.debug(str(event))
                data = event['data']
                if event['event'] == 'camera':
                    start = data['start']
                    self.camera_enabled = start
                elif event['event'] == 'obstacle':
                    obstacle = data['obstacle']
                    self.obstacle = obstacle

            self.cur_time = time.time()
            if self.cur_time - self.run_start_time > 2 and self.camera_enabled:
                self.camera.capture(self.stream, format="bgr", use_video_port=True)
                image = self.stream.array
                ConePipeline.process(image)
                contours = ConePipeline.output

                # TODO do something with the contours... like find the code the gives
                #  you the angle off center of the cone

                # clear the stream in preparation for the next frame
                self.stream.truncate(0)
            # Read the raw data from the scanner and process it
            self.scanner.readData()

            # Retrieve the current state of the environment
            env_state = self.scanner.getData()

            # Periodically log the data to a file for later viewing
            if (self.cur_time - self.last_time) > 2:
                # Log the current cell data to a file
                self.daddy_pipe.send(env_state)
                with open(map_filename, 'a+', newline='') as map_file:
                    wr = csv.writer(map_file, dialect='excel')
                    wr.writerow(list(env_state))
                    map_file.close()

                # Reset the last time to the current time
                self.last_time = self.cur_time

            # TODO: Obstacle avoidance

            # TODO: SLAM?

    def stop(self):
        # Stop scanning if the program ends
        logging.info("Stopping LiDAR Scan")
        self.scanner.stopScan()