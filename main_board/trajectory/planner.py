from trajectory import trajectory

#Test stuff
test_trajectory = trajectory()
test_trajectory.loadWaypoints('./waypoints.txt', True)
test_trajectory.exportToKML('./test.kml')
