from sense_hat import SenseHat
import time
import numled
import paho.mqtt.client as mqtt

sense = SenseHat()
colors = [(0, 255, 0), (255, 255, 255)]

hostname = "iot.eclipse.org" # Sandbox broker
port = 1883 # Default port for unencrypted MQTT

topic = "elec3542-projectdemo/temp" # Wildcard '#' indicates that all sub-topics (e.g., elec3542/test, elec3542/sensor/temperature, etc.)

def on_connect(client, userdata, flags, rc):
	# Successful connection is '0'
	print("Connection result: " + str(rc))
	if rc == 0:
		# Subscribe to topics
		client.subscribe(topic)

def on_message(client, userdata, message):
    print("Received message on %s: %s (QoS = %s)" % (message.topic, message.payload.decode("utf-8"), str(message.qos)))
    numled.show_number(sense, int(message.payload.decode("utf-8")), colors[0])
    time.sleep(1)
    numled.show_number(sense, int(message.payload.decode("utf-8")), colors[1])

def on_disconnect(client, userdata, rc):
	if rc != 0:
		print("Disconnected unexpectedly")

# Initialize client instance
client = mqtt.Client()

# Bind events to functions
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect

# Connect to the specified broker
client.connect(hostname, port, 60)

# Network loop runs in the background to listen to the events
client.loop_forever()
