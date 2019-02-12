# This file manages the kalman filter used for robot localization

# Import the matrix libraries and necessary modules
from math import cos, sin, tan, radians, pow
from multiprocessing import Process, Pipe
import numpy as np
from numpy.linalg import inv
import time
import logging

# The kalman filter class that will be used to find the robot's location


class kalman_filter:

    # State vector format
    # 0: latitude
    # 1: longitude
    # 2: velocity
    # 3: acceleration
    # 4: heading
    # 5: steering angle

    # Class constants
    NUM_STATE_VARS = 6

    # Initialize the filter
    def __init__(self, xo, Po, config):
        # Robot Parameters
        self.L = config['Robot']['wheelbase_length']
        self.TOP_SPEED = config['Robot']['top_speed']

        # Initialize the jacobians
        # Fk = Jacobian of the motion function
        self.Fk = np.identity(self.NUM_STATE_VARS)

        # Hk = Jacobian of the measurement function
        self.Hk = np.identity(self.NUM_STATE_VARS)

        # Set the initial conditions of the filter
        self.x_estimate = np.zeros(self.NUM_STATE_VARS)
        self.x_last = xo
        self.Pk = np.identity(self.NUM_STATE_VARS) * 0.1
        self.Pk_last = Po

        # Start the timing variables
        self.last_time = time.time()

        # Set up the covariance matrices
        self.R = np.identity(self.NUM_STATE_VARS) * 0.5
        self.Q = np.identity(self.NUM_STATE_VARS) * 0.6
        logging.info("Kalman Filter Initialized")

    # This is the motion function, normally represented by the function f(xk-1, uk, w) in our non-linear case
    # This function is called in the predict stage
    # This function will estimate xk for use in the update step
    # xk-1: last state
    # uk: input signal
    # w: process noise
    def motionModel(self, deltaT):
        # Run the physics equations to estimate the current state
        self.x_estimate[0] = self.x_last[0] + (self.x_last[2] * cos(radians(self.x_last[4]))
                                               * sin(radians(self.x_last[5])) * deltaT)
        self.x_estimate[1] = self.x_last[1] + (self.x_last[2] * cos(radians(self.x_last[4]))
                                               * cos(radians(self.x_last[5])) * deltaT)
        self.x_estimate[2] = self.x_last[2] + (self.x_last[3] * deltaT)
        self.x_estimate[3] = self.x_last[3]
        self.x_estimate[4] = self.x_last[4] + (self.x_last[2] / self.L) * tan(self.x_last[5])
        self.x_estimate[5] = self.x_last[5]

        # Update the jacobian for the motion function based on last values
        # Latitude depends on velocity, steering angle, and heading
        self.Fk[0, 2] = cos(radians(self.x_last[4])) * sin(radians(self.x_last[5]))
        self.Fk[0, 4] = self.x_last[2] * cos(radians(self.x_last[4])) * cos(radians(self.x_last[5]))
        self.Fk[0, 5] = -self.x_last[2] * cos(radians(self.x_last[4])) * sin(radians(self.x_last[5]))

        # Longitude depends on the same things latitude does
        self.Fk[1, 2] = cos(radians(self.x_last[4])) * cos(radians(self.x_last[5]))
        self.Fk[1, 4] = -self.x_last[2] * sin(radians(self.x_last[4])) * cos(radians(self.x_last[5]))
        self.Fk[1, 5] = -self.x_last[2] * cos(radians(self.x_last[4])) * sin(radians(self.x_last[5]))

        # Heading depends on velocity and steering angle
        self.Fk[4, 2] = tan(radians(self.x_last[5])) / self.L
        self.Fk[4, 5] = (self.x_last[2] / self.L) * pow((1 / tan(self.x_last[5])), 2)

    # This is the measurement function, normally represented by zk = h(xk) + vk
    # We know the sensor data and estimated state, so this function will find vk
    # zk: measured values from sensors
    # xk: estimated value from motion model
    # vk: measurement noise
    def measurementModel(self, sensor_data):
        # Initialize zk to zero value for sensor processing
        zk = np.zeros(self.NUM_STATE_VARS)

        # Process sensor data
        zk[0] = sensor_data['GPS_lat']
        zk[1] = sensor_data['GPS_lon']
        zk[2] = sensor_data['encoder_vel'] # consider adding/using GPS velocity
        zk[3] = sensor_data['accel_x']
        zk[4] = sensor_data['compass']
        zk[5] = sensor_data['steer_ang']

        # Subtract x_estimate from zk and return this vector (vk)
        return (zk - self.x_estimate)

    # First we must predict the state of the robot based on the Ackermann steering model and prior state
    # We can also consider the input signal in this stage, but we currently are not doing so
    def predict(self, deltaT):
        # Perform a state estimation
        self.motionModel(deltaT)

        # Calculate the uncertainty matrix based on the last state's jacobian of f(xk, uk)
        self.Pk = (self.Fk.dot(self.Pk_last)).dot(np.transpose(self.Fk)) + self.Q

    # After prediction is complete, we need to update the predicted values by fusing them with real values
    # These real values are also noisy, so we use the kalman gain (Gk) to determine the tradeoff between sensor
    # and model data.
    # sensor_data is a dict of all the sensor values included in this update
    # This will return the current state of the robot
    def update(self, sensor_data):
        # Calculate the Kalman Gain
        self.Gk = (self.Pk.dot(np.transpose(self.Hk))).dot(inv(self.Hk.dot(self.Pk).dot(np.transpose(self.Hk)) + self.R))

        # Update the state and uncertainty
        self.x_estimate = self.x_estimate + self.Gk(self.measurementModel(sensor_data))
        self.Pk = (np.identity(self.NUM_STATE_VARS) - self.Gk.dot(self.Hk)).dot(self.Pk)

    # Run the filter on a new data point
    def run(self, sensor_data):
        # Calculate time change
        cur_time = time.time()
        deltaT = cur_time - self.last_time

        # Predict the state of the robot
        self.predict(deltaT)

        # Update with appropriate measurements
        self.update(sensor_data)

        # Set the current data to the last data for future iterations
        self.x_last = self.x_estimate
        self.Pk_last = self.Pk
        self.last_time = cur_time

        # Return the current state
        return self.x_last

    # Get the most recent state calculated by the filter
    def getState(self):
        return self.x_last

    # Process data piped in by another process
    def process_data(self, pipe):
        # Run the process until an exit command is sent
        while True:
            # We only care if there is data
            if pipe.poll():
                # Receive data from the other process
                sensor_data = pipe.recv()

                # TODO: Add standards - like JSON instead of this sketchy implentation
                # Exit if told to exit
                if sensor_data == 'exit':
                    break
                # Return state info if a request is lodged
                elif sensor_data == 'request':
                    pipe.send(self.getState())
                # Otherwise update the filter with the new data
                else:
                    # Run the kalman filter on the sensor data
                    cur_state = self.run(sensor_data)

                    # Output the result
                    pipe.send(cur_state)

        # Close the pipe connections
        pipe.close()
