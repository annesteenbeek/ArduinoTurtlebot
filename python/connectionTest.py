#!/usr/bin/python
import serial
import time
import curses
import sys

ser = serial.Serial(port='/dev/ttyACM3',
    baudrate=9600,
    )
if not ser.isOpen():
    ser.open()

blinkRed = [139, 16, 255, 255]
blinkGreen = [139, 32, 0, 255]

#  send variable amount of integers to serialport
def sendToRoomba(integers):
    sendString = "" # empty the string 
    for num in integers:
        sendString += " "+str(num) # add x to end parseint()
    ser.write(sendString)
    time.sleep(0.1)

sendToRoomba(blinkRed)
time.sleep(2) # sleep 2 seconds
sendToRoomba(blinkGreen)