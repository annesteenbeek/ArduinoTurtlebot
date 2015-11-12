// clytle 2013
// Thanks to bcreighton for debugging help
// Thanks to Marc Moesse for transcribbing music to opcodes
//
// Tested on a Roomba 4150 (manufacture date July 15 2007)
// using an Arduino Duemilanove & Arduino Leonardo. 
//
// Roomba docs at http://www.irobot.com/images/consumer/hacker/Roomba_SCI_Spec_Manual.pdf
//
// Wiring:
// Connect Arduino pin 5 to Roomba pin 4
// Connect Arduino pin 6 to Roomba pin 3
// Connect Arduino pin 7 to Roomba pin 5
// Connect Arduino GND pin to Roomba pin 6 or 7

#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6); //rx,tx
int ddPin = 7;
int now;

void setup() {
  pinMode(ddPin,  OUTPUT);
  mySerial.begin(57600);
  //Use Device Detect to wake Roomba
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);
  //Initialize Roomba SCI
  // Start SCI
  mySerial.write(128);
  delay(100);
  // Enable control
  mySerial.write(130);  
  delay(100);
  // Enable full control, no safety, all commands (optional)
  mySerial.write(132);
  delay(100);
  // Each single letter array is a bar of music.
  // Each double letter array is play command for the corresponding music.
  int a[] = {140, 1, 9, 55, 32, 55, 32, 55, 32, 51, 24, 58, 8, 55, 32, 51, 24, 58, 8, 55, 64};
  int b[] = {140, 2, 9, 62, 32, 62, 32, 62, 32, 63, 24, 58, 8, 54, 32, 51, 24, 58, 8, 55, 64};
  int c[] = {140, 3, 12, 67, 32, 55, 24, 55, 8, 67, 32, 66, 24, 65, 8, 64, 8, 63, 8, 64, 16, 30, 16, 56, 16, 61, 32};
  int d[] = {140, 4, 14, 60, 24, 59, 8, 58, 8, 57, 8, 58, 16, 10, 16, 52, 16, 54, 32, 51, 24, 58, 8, 55, 32, 51, 24, 58, 8, 55, 64};
  int aa[] = {141, 1};
  int bb[] = {141, 2};
  int cc[] = {141, 3};
  int dd[] = {141, 4};
  // Load the songs to the Roomba
  opcodes(a, (sizeof(a)/sizeof(int)));
  opcodes(b, (sizeof(b)/sizeof(int)));
  opcodes(c, (sizeof(c)/sizeof(int)));
  opcodes(d, (sizeof(d)/sizeof(int)));
  // Play the songs. Pauses must be included while the music plays.
  opcodes(aa, (sizeof(aa)/sizeof(int)));
  delay(4000);
  opcodes(bb, (sizeof(bb)/sizeof(int)));
  delay(4000);
  opcodes(cc, (sizeof(cc)/sizeof(int)));
  delay(3500);
  opcodes(dd, (sizeof(dd)/sizeof(int)));
}

void loop() {
}

// This little function takes an array of opcodes (and the array's length) and runs them all.
void opcodes(int *bytes, int len) {
  for (now = 0; now < len; now++) {
    mySerial.write((byte)(bytes[now]));
    delay(100);
  }
}