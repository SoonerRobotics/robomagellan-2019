import configparser

#Config Reader
class Config:

	#static configparser data
	data = None

	def __init__(self):
		#If we haven't read the config data yet, read it and store it in Config.data
		if not Config.data:
			Config.data = configparser.SafeConfigParser()
			Config.data.read("config.ini")

	#Get an item from the config
	#Example:
	# cfg = Config()
	# value = cfg["section"]["key"]
	def __getitem__(self, key):
		return Config.data[key]