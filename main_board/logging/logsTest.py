# logs sample
# logs are imported to a file logsTest.log
import logging
import logs

def main():
	logging.info('Test Started')	
	logging.info('Error Log Test')
	logs.systemError()
	logs.gpsError()
	logs.imuError()	
	logging.info('Reading Log Test')
	logs.read_GPS()
	logs.read_IMUCoordinates()
	logging.info('Route Log Test')
	logs.obstacleFound()
	logs.rerouting()
	logs.routeComplete()	
	logging.info('Stopping Log Test')	
	logs.eStop()
	logs.paused()
	logging.info('Test is Finished')

if __name__ == '__main__':
    main()