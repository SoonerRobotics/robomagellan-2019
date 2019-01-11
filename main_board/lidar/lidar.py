# This class stores the most recent lidar data and also facilitates reading
# from the sensor
#
# This code can also be used to send commands to the lidar module

from math import atan, degrees
import numpy as np
import os
import sys
import serial
import struct
import time


class lidar:

    # Class constants
    DEBUG = True

    def __init__(self, port = None, baudRate = 128000):
        # Initialize a list of the 360 cells we want to look at
        self.cells = np.zeros(360)

        # Open the serial port at the baud rate specified
        self.serialComms = serial.Serial(port, baudRate, timeout=2)

        # Initialize the data interpolation variables
        self.lastData = -1
        self.lastCell = -1

    # Run this command to start the scanning process
    def startScan(self):
        # The system command is 0xA5. Send this byte first
        self.serialComms.write(0xA5)

        # Now send the Scan Start command (0x60)
        self.serialComms.write(0x60)

        # Set the device mode to scanning
        self.scanning = True

    # Run this command to stop the scanning process
    def stopScan(self):
        # The system command is 0xA5. Send this byte first
        self.serialComms.write(0xA5)

        # Send the stop command (0x65)
        self.serialComms.write(0x65)

        # Set the device mode to not scanning
        self.scanning = False

    # Read the latest data into an array of distances corresponding to angles
    def readData(self):
        # Only perform this action if the device is already scanning
        if self.scanning == True:
            # Reset the sample lists
            distances = []
            raw_samples = []

            # Read the first 10 control bytes
            ctrl_data = list(self.serialComms.read(size=10))
            
            # Print control data to debug output
            if self.DEBUG:
                print(ctrl_data)

            # If there is an error, give up
            if len(ctrl_data) != 10:
                if self.DEBUG:
                    print("Read error")
                return

            #### Get important constants ###

            # Get the number of sample points in the data
            num_samples = int(ctrl_data[3])

            # Get FSA, an angle calibration value
            FSA = (int(ctrl_data[5]) << 8) + int(ctrl_data[4])
            
            # Get LSA, another angle calibration value
            LSA = (int(ctrl_data[7]) << 8) + int(ctrl_data[6])
            
            # Get the check code, which validates the data packet
            check_code = (int(ctrl_data[9]) << 8) + int(ctrl_data[8])

            # Read in the correct number of raw samples
            for i in range(0, num_samples * 2):
                # Get the serial data packets
                data = list(self.serialComms.read(size = 1))[0]

                # Add data to the sample list
                raw_samples.append(data)

            # Validate the data packet
            #if self.validate(ctrl_data, raw_samples, check_code):
            # TODO: validate the packet. Not sure if necessary. It works better if we don't
            if True:

                # Calculate the distances from the raw data
                i = 0
                while i < (num_samples * 2):
                    # Get the two bytes for a sample
                    s_low = raw_samples[i]
                    s_high = raw_samples[i+1]

                    # Combine the bytes
                    # Convert the raw data to distance measurements (in mm)
                    dist = ((int(s_high) << 8) + int(s_low)) / 4

                    # Add this measurement to the distances list
                    distances.append(dist)

                    # Increment to the next pair
                    i = i + 2

                # Find the start angle
                start_angle = ((FSA >> 1) / 64) + self.ang_correct(distances[0])

                # Find the end angle
                end_angle = ((LSA >> 1) / 64) + self.ang_correct(distances[num_samples - 1])

                # Go through each distance and assign it to a cell
                # When cells are skipped, choose the closest last read distance to replace them
                for i in range(0, num_samples):
                    # Find the current angle
                    if i != 0 and i != (num_samples - 1):
                        cur_angle = (self.diff_angle(start_angle, end_angle) / num_samples) * (i - 1) + start_angle + self.ang_correct(distances[i])
                    elif i == 0:
                        cur_angle = start_angle
                    else:
                        cur_angle = end_angle

                    if self.DEBUG:
                        print("Ang: " + str(cur_angle) + " Dist: " + str(distances[i]))

                    # Find closest cell to this angle
                    # and restrict the cell number to 0 - 359
                    cell_num = int(round(cur_angle)) % 360

                    # Add the distance to the correct cell
                    self.cells[cell_num] = distances[i]

                    # Go back to the last cell and fill in the gaps
                    if self.lastCell == -1:
                        self.lastCell = cell_num
                        self.lastData = distances[i]
                    else:
                        self.cells[self.lastCell + 1:cell_num] = self.min_not_zero(self.lastData, self.cells[cell_num])
                        self.lastCell = cell_num
                        self.lastData = self.min_not_zero(self.lastData, self.cells[cell_num])
    
    # Get the current cell data from the LiDAR module
    def getData(self):
        return self.cells

    # Determines the angle correction value based on the distance
    def ang_correct(self, dist):
        if dist == 0:
            return 0
        else:
            return degrees(atan(21.8 * (155.3 - dist)/(155.3 * dist)))
    
    # Find the clockwise difference between start and end angles
    def diff_angle(self, start_angle, end_angle):
        if start_angle <= end_angle:
            return (end_angle - start_angle)
        else:
            return (360 - start_angle) + end_angle

    # Validate the data packet that is given by the sensor
    def validate(self, ctrl_data, samples, check_code):
        # initialize the XOR operation (PH ^ FSA)
        result = ((int(ctrl_data[0]) << 8) + int(ctrl_data[1])) ^ ((int(ctrl_data[4]) << 8) + int(ctrl_data[5]))

        # XOR all the samples
        i = 0
        while i < len(samples):
            # Combine the raw sample bytes
            si = (int(samples[i]) << 8) + int(samples[i + 1])

            # XOR the result with this sample
            result = result ^ si

            # Move to the next sample pair
            i = i + 2

        # XOR the CT + LSN pair and then the LSA
        result = result ^ ((int(ctrl_data[2]) << 8) + int(ctrl_data[3]))
        result = result ^ ((int(ctrl_data[6]) << 8) + int(ctrl_data[7]))
        
        return (result == check_code)

    # Prints the raw output of the lidar sensor
    def readRaw(self):
        print(self.serialComms.read(size = 10))

    # Returns the minimum non-zero value
    def min_not_zero(self, x, y):
        if x == 0:
            return y
        elif y == 0: 
            return x
        else:
            return min(x, y)