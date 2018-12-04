#This class stores the most recent lidar data and also facilitates reading 
#from the sensor
#
#This code can also be used to send commands to the lidar module

import os
import sys
import serial
import struct
import time

class lidar:

    def __init__(self, port, baudRate):
        #Open the serial port at the baud rate specified
        self.serialComms = serial.Serial(port, baudRate, timeout = 5)
        self.serialComms.open()

    #Run this command to start the scanning process
    def startScan(self):
        #The system command is 0xA5. Send this byte first
        self.serialComms.write(0xA5)

        #Now send the Scan Start command (0x60)
        self.serialComms.write(0x60)

        #Set the device mode to scanning
        self.scanning = True

    #Run this command to stop the scanning process
    def stopScan(self):
        #The system command is 0xA5. Send this byte first
        self.serialComms.write(0xA5)

        #Send the stop command (0x65)
        self.serialComms.write(0x65)

        #Set the device mode to not scanning
        self.scanning = False

    #Read the latest data into an array of distances corresponding to angles
    def readData(self):
        #Only perform this action if the device is already scanning
        if self.scanning == True:
            #Reset the samples list
            samples = []

            #Read the first 10 control bytes
            ctrl_data = self.serialComms.read_until(size = 10)

            #Process the control bytes. First convert to big endian
            for i in range(0, len(ctrl_data)):
                ctrl_data[i] = ctrl_data[i]

            #Get important constants
            num_samples = int(ctrl_data[3])                             #Get the number of sample points in the data
            FSA = (int(ctrl_data[5]) << 8) + int(ctrl_data[4])          #Get FSA, an angle calibration value
            LSA = (int(ctrl_data[7]) << 8) + int(ctrl_data[6])          #Get LSA, another angle calibration value
            check_code = (int(ctrl_data[9]) << 8) + int(ctrl_data[8])   #Get the check code, which checks the data packet

            #Read in the correct number of samples
            for i in range(0, num_samples):
                #Get the serial data packets
                data = self.serialComms.read()

                #Convert the raw data to distance measurements (in mm)
                samples.append(data / 4)
            
            #Find the start angle
            