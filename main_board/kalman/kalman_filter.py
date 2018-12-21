# This file manages the kalman filter used for robot localization

# Import the matrix libraries and necessary modules
import numpy as np

# The kalman filter object that will be used to find the robot's location
class kalman_filter:
    
    # Initialize the filter
    def __init__(self, xo, Po):
        # Initialize the jacobians
        
        # Fx = Jacobian of the motion function
        self.Fx = np.identity(14)

        # Hx = Jacobian of the measurement function
        self.Hx = np.identity(14)

        # Set the initial conditions of the filter
        self.x = xo
        self.P = Po
    
    # This is the motion function, normally represented by the function f(xk-1, uk, w) in our non-linear case
    # This function is called in the predict stage
    # This function will estimate xk for use in the update step
    # xk-1: last state
    # uk: input signal
    # w: process noise
    def motionModel(self):
        pass
    
    # This is the measurement function, normally represented by h(xk, vk)
    # Note there's a distiction between this xk and the one computed in the motion model.
    # This xk is the vector of values observed by the sensors, while the other one is an estimate
    # vk: measurement noise
    def measurementModel(self):
        pass
    
    # First we must predict the state of the robot based on the Ackermann steering model and prior input
    def predict(self):
        pass

    # After prediction is complete, we need to update the predicted values by fusing them with real values
    # These real values are also noisy, so we use the kalman gain (Gk) to determine the tradeoff between sensor
    # and model data.
    # This will return the current state of the robot
    def update(self):
        pass

        