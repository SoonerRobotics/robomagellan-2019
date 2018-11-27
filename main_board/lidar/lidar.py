#This class stores the most recent lidar data and also facilitates reading 
#from the sensor
#
#This code can also be used to send commands to the lidar module

import os
import sys
import serial
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
            #implement this later
            pass