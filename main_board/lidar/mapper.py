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

# Program constants
UPDATE_PERIOD = 2   # seconds to wait before saving another log to the file
lidar_port = "COM7" # default port for the scanner module

# If there's a port passed as a command line argument, update the port info
if len(sys.argv) > 1:
    lidar_port = sys.argv[1]

# Set up the scanner on a given port, and at the required baud rate of 128000
scanner = lidar(lidar_port, 128000)

# Create a log file name based on the start time of the run
map_filename = "maps/LiDAR_mapping_log_" + str(datetime.utcnow()).replace(' ', '_').replace(':', '_') + ".csv"

# Set up timers for periodic logging
run_start_time = time.time()
last_time = run_start_time
cur_time = run_start_time

# Start scanning the environment
scanner.startScan()

# Scan the environment while the robot is running
while True:
    # Get the current time
    cur_time = time.time()
    
    # Read the raw data from the scanner and process it
    scanner.readData()

    # Retrieve the current state of the environment
    env_state = scanner.getData()

    # Periodically log the data to a file for later viewing
    if (cur_time - last_time) > 2:
        # Log the current cell data to a file
        with open(map_filename, 'a', newline = '') as map_file:
            wr = csv.writer(map_file, dialect = 'excel')
            wr.writerow(list(env_state))
            map_file.close()
        
        # Reset the last time to the current time
        last_time = cur_time

    # TODO: Obstacle avoidance 

    # TODO: SLAM?


# Stop scanning if the program ends
scanner.stopScan()