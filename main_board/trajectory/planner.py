from trajectory import trajectory

#Test stuff
test_trajectory = trajectory()
test_trajectory.loadWaypoints('./waypoints_quad.txt', True)
test_trajectory.exportToKML('./quad.kml')

test_trajectory.updatePosition(35.210478, -97.442447)
print(test_trajectory.getHeading())
print(test_trajectory.getPower())