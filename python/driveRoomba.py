#!/usr/bin/python
import serial
import time
import curses
import sys

from pygame import *
stdscr = curses.initscr()
curses.cbreak()
stdscr.keypad(1)

ser = serial.Serial(port='/dev/ttyACM1',
	baudrate=9600,
	)
if not ser.isOpen():
	ser.open()

#  send variable amount of integers to serialport
def sendToRoomba(integers):
	sendString = "" # empty the string 
	for num in integers:
		sendString += " "+str(num) # add x to end parseint()
	ser.write(sendString)
	time.sleep(0.1)

def splitInt(input):
	outp = []
	outp.append(input & 0xff)
	outp.append((input & 0xff00) >> 8)
	return outp

def drive(setSpeed, setRotation):
	setSpeed = max(min(500, setSpeed), -500) # constrain speed to min and max
	setRotation = max(min(2000, setRotation), -2000)	
	speed = splitInt(setSpeed)
	rotation = splitInt(setRotation)
	sendSpeed = [137, speed[1], speed[0], rotation[1], rotation[0]]
	sendToRoomba(sendSpeed)


blinkRed = [139, 16, 255, 255]
blinkGreen = [139, 32, 0, 255]

ride = [137, 255, 56, 1, 244]
noride = [137, 0, 0, 0, 0]



prevSpeed = [0, 0]
stdscr.addstr(0,10,"Hit 'q' to quit")
stdscr.refresh()
stdscr.nodelay(1)

key = ''
while key != ord('q'):
    key = stdscr.getch()
    stdscr.addch(20,25,key)
    stdscr.refresh()
    if key == curses.KEY_UP: 
        stdscr.addstr(2, 20, "Up")
        forward = 1
    else:
    	forward = 0
    if key == curses.KEY_DOWN: 
        stdscr.addstr(3, 20, "Down")
        backward = 1
    else:
    	backward = 0
    if key == curses.KEY_RIGHT:
        stdscr.addstr(4, 20, "Right")
        right = 1
    else:
    	right = 0
    if key == curses.KEY_LEFT:
        stdscr.addstr(5, 20, "Left")
        left = 1
    else:
    	left = 0
    if key == ord('s'):
    	stdscr.addstr(1,20, "start")
    	sendToRoomba([-1])
    if key == ord('t'):
    	stdscr.addstr(1,20, "Terminate")
    	sendToRoomba([133])
    if key == ord('r'):
    	stdscr.addstr(1,20, "Red")
    	sendToRoomba(blinkRed)
    if key == ord('g'):
    	stdscr.addstr(1,20, "Green")
    	sendToRoomba(blinkGreen)
    speed = [forward * 100 - backward*100, left*200-right*200]
    if speed != prevSpeed:
    	drive(speed[0],speed[1])
    prevSpeed = speed
curses.endwin()
sys.exit()

