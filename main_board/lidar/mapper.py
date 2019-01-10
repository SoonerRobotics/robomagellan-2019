# This file will run the LiDAR scanner, collect data and generate a map
# of the environment while the robot is running. This is the LiDAR driver 
# and will be used for obstacle avoidance and SLAM

# Import the lidar device, timing variables and other libraries
from datetime import datetime
from lidar import lidar
import numpy as np
import time

# Program constants
UPDATE_PERIOD = 2   # seconds to wait before saving another log to the file

# Receive port information upon startup
# TODO: receive port information as a program argument
lidar_port = "COM7"

# Set up the scanner on a given port, and at the required baud rate of 128000
scanner = lidar(lidar_port, 128000)

# Create a log file based on the start time of the run
log_file = open("LiDAR_mapping_log_" + str(datetime.utcnow()).replace(' ', '_') + ".log", "w")

# Set up timers for periodic logging
last_time = time.time()
cur_time = time.time()

# Start scanning the environment
scanner.startScan()

# Scan the environment while the robot is running
while True:
    # Get the current time
    cur_time = time.time()
    
    # Read the raw data from the scanner and process it
    scanner.readData()

    # Periodically log the data to a file for later viewing
    if (cur_time - last_time) > 2:
        # Log the current cell data to a file
        log_file.write(str(scanner.getData()))
        
        # Reset the last time to the current time
        last_time = cur_time

    # TODO: Obstacle avoidance 

    # TODO: SLAM?

# Stop scanning if the program ends
scanner.stopScan()