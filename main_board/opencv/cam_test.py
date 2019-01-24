from picamera import PiCamera
from conecv import ConePipeline
from picamera.array import PiRGBArray
import time

camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 5
rawCapture = PiRGBArray(camera, size=(640, 480))

# allow the camera to warmup
time.sleep(2)

# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    # grab the raw NumPy array representing the image, then initialize the timestamp
    # and occupied/unoccupied text
    image = rawCapture.array
    ConePipeline.process(image)
    contours = ConePipeline.output
    cv2.drawContours(image, contours, -1, (0, 255, 0), 3)

    cv2.imshow("Frame", image)
    key = cv2.waitKey(1) & 0xFF

    # clear the stream in preparation for the next frame
    rawCapture.truncate(0)
