# This script is used to test the device and the lidar class to make sure everything works fine

from lidar import lidar
import time

# Set up the scanner on a given port, and at the required baud rate of 128000
scanner = lidar("COM7", 128000)

# Set the start time and begin scanning
start_time = time.time()
cur_time = time.time()
scanner.startScan()

# Scan for 10 seconds
while (cur_time - start_time) < 10:
    scanner.readData()
    cur_time = time.time()

# Stop scanning
scanner.stopScan()

# Print the environment
print(scanner.getData())