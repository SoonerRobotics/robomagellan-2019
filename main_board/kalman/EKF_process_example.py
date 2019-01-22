# This is an example of how to run the EKF on the robot.
# Some of this code will be used in production, but this is a test class

import numpy as np
import sys

from kalman_filter import kalman_filter
from multiprocessing import Process, Pipe

# Main method
if __name__ == '__main__':
    # Constants
    ROBOT_LENGTH = .333     # Robot length in meters

    # Check for appropriate program arguments
    if len(sys.argv) != 3:
        sys.exit(-1)

    # Initialize xo from the trajectory code (lat and lon included as program args)
    xo = np.array(sys.argv[0], sys.argv[1], sys.argv[2], 0, 0, 0)

    # Initialize Po to be an uncertainty of 20% for now
    # TODO: choose an actual value
    Po = np.eye(6) * 0.2

    # Initialize the kalman filter
    EKF = kalman_filter(xo, Po, ROBOT_LENGTH)

    # Set up the pipes to and from the EKF
    this_proc_out_1, this_proc_in_1 = Pipe()
    this_proc_out_2, this_proc_in_2 = Pipe()

    # NOTE: Send data to the EKF over out_1, and receive over in_2

    # Set up the separate process for running the EKF
    proc = Process(target = EKF.process_data, args = (this_proc_out_1, this_proc_in_2))
    proc.start()

    # Run the separate process as long as the first element in the queue is not 'exit'
    while True:
        # Send data to the EKF process
        # NOTE: data should be a dict of sensor data
        pass

    proc.join()



