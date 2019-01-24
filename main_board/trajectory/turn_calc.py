# Turn calculation files

from point import point 
from math import cos, fmod, radians, sqrt

class turn_builder:

    # Initialize the turn builder with configurable constants
    def __init__(self, config):
        # Environment constants
        self.coeff_friction = config['Environment']['coeff_friction']
        self.gravity = config['Environment']['gravity']
        
        # Trajectory constants
        self.min_crs_chg = config['Trajectory']['min_crs_chg']
        self.max_turn_prep_dist = config['Trajectory']['max_turn_prep_dist']

        # Robot constants
        self.mass = config['Robot']['mass']

        # Derived constants
        self.robot_normal_force = self.mass * self.gravity  # normal force of the robot
        

    # Calculate the turn data given three waypoints
    def calc_turn_data(self, start, vertex, end):
        # Find heading between start and vertex
        hdg_1 = start.getHeadingTo(vertex)

        # Find heading between vertex and end
        hdg_2 = vertex.getHeadingTo(end)

        # Calculate the length of the two legs
        len_leg_1 = start.getDistanceTo(vertex)
        len_leg_2 = vertex.getDistanceTo(end)

        # Calculate the maximum turn preparation distance
        # This is the longest distance from the vertex waypoint that a turn can start from
        # NOTE: The start point needs to be where the last turn ended for this to work. If it is the previous waypoint, results will be unpredictable
        max_start_offset = min(self.max_turn_prep_dist, len_leg_1, len_leg_2)

        # Calculate course change
        dir_sweep = self.calc_dir_sweep(hdg_1, hdg_2)
        crs_chg = dir_sweep[0]
        turn_dir = dir_sweep[1]

        # Only calculate a turn when the course change is greater than a set value
        if crs_chg >= self.min_crs_chg:
            # Calculate the intersection angle (geometric angle between the two legs on the turn side)
            turn_angle = self.calc_sweep(hdg_2, self.hdg_wrap(hdg_1 + 180), turn_dir)

            # Calculate the half turn angle
            half_turn = turn_angle / 2.0
            
            # Calculate length from vertex to turn center
            vertex_to_cntr = max_start_offset / cos(radians(half_turn))

            # Calculate the turn radius
            turn_radius = sqrt(pow(vertex_to_cntr, 2) + pow(max_start_offset, 2))

            # Compute turn speed
            turn_speed = sqrt(turn_radius * self.coeff_friction * self.robot_normal_force)

            # TODO: Calculate the position of the turn center
            turn_center = point(0, 0, -1)

            return (turn_center, turn_radius, turn_speed)


        pass

    # Find the shortest direction to turn
    def calc_dir_sweep(self, start_ang, end_ang):
        # Constrain start angle to [0, 360)
        start_ang = self.hdg_wrap(start_ang)

        # Constrain start angle to [0, 360)
        end_ang = self.hdg_wrap(end_ang)

        # Calculate the sweep of each turn
        right_sweep = self.calc_sweep(start_ang, end_ang, "right")
        left_sweep = self.calc_sweep(start_ang, end_ang, "left")

        # Decide which direction is shorter based on which angle is greater
        if right_sweep < left_sweep:
            return (left_sweep, "left")
        else:
            return (right_sweep, "right")

    # Calculate sweep between two angles in a certain direction
    # Angles entered are assumed to be compass headings [0, 360)
    def calc_sweep(self, start_ang, end_ang, dir):
        # Calculate right sweeps
        if dir == "right":
            # Nominal case
            if end_ang > start_ang:
                angle = end_ang - start_ang
            # Wrapped case
            else:
                angle = (360 - start_ang) + end_ang
        # Calculate left sweeps
        else:
            # Nominal case
            if end_ang < start_ang:
                angle = start_ang - end_ang
            # Wrapped case
            else:
                angle = (360 - end_ang) + start_ang

        return angle 

    # Wrap all headings to [0, 360)
    def hdg_wrap(self, hdg):
        hdg = fmod(hdg, 360)

        if hdg < 0:
            hdg += 360

        return hdg