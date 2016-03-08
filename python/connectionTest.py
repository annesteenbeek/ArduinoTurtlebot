#!/usr/bin/python
import serial
import time
import sys

ser = serial.Serial(port='/dev/ttyACM0',
    baudrate=57600,
    timeout=2
    )
if not ser.isOpen():
    ser.open()
    print "opened serial"
else:
    print "Serial was open"

blinkRed = [139, 16, 255, 255]
blinkGreen = [139, 32, 0, 255]

SCI = [128, 132]

#  send variable amount of integers to serialport
def sendToRoomba(integers):
    sendString = "" # empty the string 
    for num in integers:
        ser.write(bytearray([num]))
        print "send: " + str(num)
        time.sleep(0.1)

def readSerial():
    print "Received: "
    out = ''
    while ser.inWaiting() > 0:
        out += ser.read(1)

    if out != '':
        print ">>" + out

time.sleep(2.9)
print "enable full control"
sendToRoomba(SCI)
time.sleep(1)
readSerial()
sendToRoomba(blinkRed)
print "red led"
time.sleep(1)
readSerial()
