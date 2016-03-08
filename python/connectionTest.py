#!/usr/bin/python
import serial
import time
import curses
import sys

ser = serial.Serial(port='/dev/ttyACM0',
    baudrate=57600,
    )
if not ser.isOpen():
    ser.open()
    print "opened serial"
else:
    print "Serial was open"

blinkRed = [139, 16, 255, 255]
blinkGreen = [139, 32, 0, 255]

SCI = [128, 130, 132]

#  send variable amount of integers to serialport
def sendToRoomba(integers):
    sendString = "" # empty the string 
    for num in integers:
        sendString += " "+str(num) # add x to end parseint()
    ser.write(sendString)
    time.sleep(0.1)

print "enable full control"
sendToRoomba(SCI)
time.sleep(2)

print "Enable red"
sendToRoomba(blinkRed)
time.sleep(2) # sleep 2 seconds
print "Enable green"
sendToRoomba(blinkGreen)