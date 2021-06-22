import serial
import time

arduino = serial.Serial('/dev/tty.HC-05-SerialPort', 9600)
time.sleep(1)

print("pronto a ricevere")

while (True):
    testo= arduino.readline()
    print(testo)
    time.sleep(.5)