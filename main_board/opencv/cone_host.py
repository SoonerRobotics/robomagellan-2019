from picamera import PiCamera
from conecv import ConePipeline
from picamera.array import PiRGBArray
import time
import socket

camera = PiCamera()
width = 640
height = 480
camera.resolution = (width, height)
fov_x = 62.2
focal_length = 3.6
camera.framerate = 5
rawCapture = PiRGBArray(camera, size=(width, height))
processing = True
# allow the camera to warmup
time.sleep(2)
# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
	# grab the raw NumPy array representing the image, then initialize the timestamp
	# and occupied/unoccupied text
	image = frame.array
	if processing:
		#Process image and get traffic cone shape
	 	ConePipeline.process(image)
	 	c = ConePipeline.get_bounding_rect()
	 	angle = c['x'] + (width/2)
	 	# distance(mm) = (Focal length (mm) * cone height (mm) * image height (px) / cone height (px) * sensor height (mm))
	 	distance = 0
	 	if c['height'] != 0:
	 		distance = (3.6 * 457.2 * height ) / (c['height'] * 3)
 		
	# clear the stream in preparation for the next frame
	rawCapture.truncate(0)

