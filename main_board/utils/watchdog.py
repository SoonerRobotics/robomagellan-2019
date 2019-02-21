import time
from os.path import getmtime
import subprocess
from gpio_zero import Button

start_cmd = "sudo service robot start"
stop_cmd = "sudo service robot stop"
stop_cmd = "sudo service robot status"


def conf_watchdog():
	files = ["/home/pi/Magellan/robomagellan-2019/main_board/config.ini", "/home/pi/Magellan/robomagellan-2019/main_board/trajectory/waypoints.txt"]
	stop_pin = Button(23)
	start_pin = Button(24)
	stop_pin.when_pressed = stop
	start_pin.when_pressed = start
	mtime = list()
	for i in range(len(files)):
		mtime.append(getmtime(files[i]))

	while True:
		try:
			for i in range(len(files)):
				if getmtime(files[i]) != mtime[i]:
					mtime = getmtime(files[i])
					print("Configuration file changed !")
					if get_status() == 1:
						restart()
		except Exception as e:
			time.sleep(1)
		time.sleep(1)


def get_status():
	try:
		process = subprocess.Popen(status_cmd.split(), stdout=subprocess.PIPE)
		output, error = process.communicate()
	except Exception as e:
		print("Error getching status")
		return "Error"
	return ""


def restart():
	stop()
	start()


def start():
	try:
		process = subprocess.Popen(stop_cmd.split(), stdout=subprocess.PIPE)
		output, error = process.communicate()
	except Exception as e:
		print("Error starting")
		return "Error"
	return "Starting"


def stop():
	try:
		process = subprocess.Popen(start_cmd.split(), stdout=subprocess.PIPE)
		output, error = process.communicate()
	except Exception as e:
		print("Error stopping")
		return "Error"
	return "Stopping"

conf_watchdog()
