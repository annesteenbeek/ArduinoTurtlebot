#!/usr/bin/python
import serial
import time
import curses
import sys

stdscr = curses.initscr()
curses.cbreak()
stdscr.keypad(1)

ser = serial.Serial(port='/dev/ttyACM3',
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
    sendSpeed = []
    setSpeed = max(min(500, setSpeed), -500) # constrain speed to min and max
    setRotation = max(min(2000, setRotation), -2000)    
    if setRotation == 0 and setSpeed != 0:  # to tranvel in a straight line
        setRotation = 32768
    if setSpeed == 0 and setRotation != 0:  # rotate in place
        setSpeed = setRotation
        setRotation = setRotation/abs(setRotation)

    speed = splitInt(setSpeed)
    rotation = splitInt(setRotation)
    sendSpeed = [137, speed[1], speed[0], rotation[1], rotation[0]]
    sendToRoomba(sendSpeed)

blinkRed = [139, 16, 255, 255]
blinkGreen = [139, 32, 0, 255]

ride = [137, 255, 56, 1, 244]
noride = [137, 0, 0, 0, 0]

stdscr.addstr(0,10,"Hit 'q' to quit")
stdscr.refresh()

key = ''
while key != ord('q'):
    key = stdscr.getch()
    stdscr.addch(20,25,key)
    stdscr.refresh()
    if key == ord('w'): 
        stdscr.addstr(2, 20, "Up")
        forward = 1
    else:
        forward = 0
    if key == ord('s'): 
        stdscr.addstr(3, 20, "Down")
        backward = 1
    else:
        backward = 0
    if key == ord('d'):
        stdscr.addstr(4, 20, "Right")
        right = 1
    else:
        right = 0
    if key == ord('a'):
        stdscr.addstr(5, 20, "Left")
        left = 1
    else:
        left = 0
    if key == ord(' '):
        stdscr.addstr(1,20, "Stop")
        drive(0,0)
    if key == ord('b'):
        stdscr.addstr(1,20, "begin")
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
    speed = [forward * 50 - backward*50, left*50-right*50]
    drive(speed[0],speed[1])
    stdscr.addstr(1,20, str(key))
curses.endwin()
sys.exit()

