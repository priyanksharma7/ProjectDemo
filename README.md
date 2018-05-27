# ProjectDemo
Code for Project Demo

Hardware folder contains the code for the Arduino. Tests are to check whether the motor sensor and ultasonic sensors work perfectly. Final Code is the code to be uplaoded.

Software folder contains the python files for 4 different Raspberry Pis, namely, Car Pi, Server Pi and 2 Sensor Pis.

Car Pi contains the Data collection file to collect data. start.py and stop.py are to control the car using the Raspberry Pi.

Server Pi has the MQTT-subscribe file and other necessary supporting files.

Sensor Pi has the MQTT-publish file to contantly update the environment conditions to the MQTT broker.
