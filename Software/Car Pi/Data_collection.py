#!/usr/bin/python3
import requests
import time
import datetime
from sense_hat import SenseHat

sense = SenseHat()
api_key = "6YCW61J0MUV0TCHK"

while(True):
	temperature = sense.get_temperature()
	orientation = sense.get_orientation_degrees()
	pitch = orientation['pitch']
	yaw = orientation['yaw']
	roll = orientation['roll']
	data = { "api_key": api_key, "field1": temperature, "field2": pitch, "field3": yaw , "field4": roll }
	req = requests.post("https://api.thingspeak.com/update", data=data)
	time.sleep(1)


