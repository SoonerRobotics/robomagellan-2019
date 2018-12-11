import os
from os.path import expanduser
from os.path import basename

#List of github links to clone
git_links = ["https://github.com/Sooner-Competitive-Robotics/RobotLib",
				"https://github.com/Sooner-Competitive-Robotics/SCR_Adafruit_BNO055",
				"https://github.com/adafruit/Adafruit_Sensor",
				"https://github.com/mikalhart/TinyGPS",
				"https://github.com/bblanchon/ArduinoJson.git"]

#Path to the user's directory. This is the parent of the documents directory
user_path = expanduser("~")

#Relative path from the user path to the actual libs folder
f = open("deps.ini", "r")
relative_path_to_libs = f.readline().replace("\n", "")

#full lib path
full_path = os.path.join(user_path, relative_path_to_libs)
print(full_path)

#change to the libraries folder
os.chdir(full_path)

#clone all the dependencies
for i in range(0, len(git_links)):
	#run the clone
	os.system("git clone " + git_links[i])

#Pull the code
for i in range(0, len(git_links)):
	name = git_links[i].split("/")
	os.chdir(name[len(name) -1 ])
	os.system("git pull")
	os.chdir("..")
	
print("Done did it!")
