#!/usr/bin/python3
import requests
import time
import datetime
from sense_hat import SenseHat

import paho.mqtt.publish as publish

sense = SenseHat()
api_key = "38UDODZG24P81ZL6"
hostname = "iot.eclipse.org" # Sandbox broker
port = 1883 # Default port for unencrypted MQTT

topic1 = "elec3542-projectdemo/temp" # '/' as delimiter for sub-topics
topic2 = "elec3542-projectdemo/hum"
topic3 = "elec3542-projectdemo/pitch"
topic4 = "elec3542-projectdemo/yaw"
# API reference can be found at https://eclipse.org/paho/clients/python/docs/#id17


while(True):
	temperature = sense.get_temperature()
	humidity = sense.get_humidity()
	orientation = sense.get_orientation_degrees()
	pitch = orientation['pitch']
	yaw = orientation['yaw']
	x = datetime.datetime.now()
	msgs = [(topic1, str(int(temperature)), 0, False), (topic2, str(int(humidity)), 0, False), (topic2, str(int(pitch)), 0, False), (topic2, str(int(yaw)), 0, False)]
	publish.multiple(msgs, hostname=hostname, port=port)
	data = { "api_key": api_key, "field1": temperature, "field2": humidity, "field3": pitch , "field4": yaw }
	req = requests.post("https://api.thingspeak.com/update", data=data)
	time.sleep(2)