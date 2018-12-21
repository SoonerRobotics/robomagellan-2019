# This file manages the kalman filter used for robot localization

# Import the matrix libraries and necessary modules
from math import tan, radians
import numpy as np
from numpy.linalg import inv
import time

# The kalman filter object that will be used to find the robot's location


class kalman_filter:

    # Initialize the filter
    def __init__(self, xo, Po, L):
        # Robot Parameters
        self.L = L

        # Initialize the jacobians
        # Fk = Jacobian of the motion function
        self.Fk = np.identity(14)

        # Hk = Jacobian of the measurement function
        self.Hk = np.identity(14)

        # Set the initial conditions of the filter
        self.x_estimate = np.zeros(14)
        self.x_last = xo
        self.Pk = np.zeros(14)
        self.Pk_last = np.identity(14) * 0.1

        # Start the timing variables
        self.last_time = time.time()

        # Set up the covariance matrices
        self.R = np.identity(14) * 0.5
        self.Q = np.identity(14) * 0.6

    # This is the motion function, normally represented by the function f(xk-1, uk, w) in our non-linear case
    # This function is called in the predict stage
    # This function will estimate xk for use in the update step
    # xk-1: last state
    # uk: input signal
    # w: process noise
    def motionModel(self, deltaT):
        #Run the physics equations to estimate the current state
        self.x_estimate[0] = self.x_last[0] + (self.x_last[3] * deltaT)
        self.x_estimate[1] = self.x_last[1] + (self.x_last[4] * deltaT)
        self.x_estimate[2] = self.x_last[2] + (self.x_last[5] * deltaT)
        self.x_estimate[3] = self.x_last[3] + (self.x_last[6] * deltaT)
        self.x_estimate[4] = self.x_last[4] + (self.x_last[7] * deltaT)
        self.x_estimate[5:7] = self.x_last[5:7]
        self.x_estimate[8] = self.x_last[8] + (self.x_last[3] / self.L) * tan(self.x_last[9])
        self.x_estimate[9:13] = self.x_last[9:13]

        # Update the jacobian for the motion function

    # This is the measurement function, normally represented by zk = xk + vk
    # zk: measured values from sensors
    # xk: estimated value from motion model
    # vk: measurement noise
    def measurementModel(self):
        pass

    # First we must predict the state of the robot based on the Ackermann steering model and prior input
    def predict(self, deltaT):
        # Calculate the uncertainty matrix
        self.Pk = (self.Fk.dot(self.Pk_last)).dot(
            np.transpose(self.Fk)) + self.Q

        # Perform a state estimation
        self.motionModel(deltaT)

    # After prediction is complete, we need to update the predicted values by fusing them with real values
    # These real values are also noisy, so we use the kalman gain (Gk) to determine the tradeoff between sensor
    # and model data.
    # This will return the current state of the robot
    def update(self, zk):
        # Calculate the Kalman Gain
        self.Gk = (self.Pk.dot(np.transpose(self.Hk))).dot(
            inv(self.Hk.dot(self.Pk).dot(np.transpose(self.Hk)) + self.R))

        # Update the state and uncertainty
        self.x_estimate = self.x_estimate + \
            self.Gk(zk - self.measurementModel())
        self.Pk = (np.identity(14) - self.Gk.dot(self.Hk)).dot(self.Pk)

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

        # Return the current coordinates according to the filter
        #coords = [self.xk]
        # return coords
        pass
