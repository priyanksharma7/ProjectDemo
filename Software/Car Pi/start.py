import serial
ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.write(bytes('1', "utf-8"))