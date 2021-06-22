import serial
import time

arduino = serial.Serial('COM6', 9600)
time.sleep(1)

print("pronto a ricevere")

while (True):
    testo= arduino.readline()
    print(testo)
    time.sleep(.1)
