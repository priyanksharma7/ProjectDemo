import serial
ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.write(bytes('0', "utf-8"))