/*      Roomba Blink
 
        Sends an active low pulse to the DD (Device Detect) Pin of the Roomba 4000
        for 500msec to wake the Roomba up from the default power on sleep state
       
        Puts the Roomba in Full Command Mode, turn off safety features
        ignore wheel drops, cliff detectors and connected charger
 
        Initializes a software defined serial port
        on pins 5 and 6 of the Arduino Uno
       
        Illuminates the Roomba Power and Status LED
        Green for two seconds, then Red for one second, repeatedly
       
        Flashes the Arduino Uno built in LED connected to Digital Pin 13
        On for two seconds, then Off for two seconds, repeatedly
       
        Roomba Serial Command Interface Specification at the following location:
        http://www.ecsl.cs.sunysb.edu/mint/Roomba_SCI_Spec_Manual.pdf
 
        ArduinoUno Digital IO 5 RX to Roomba pin 4 TXD (yellow wire)
        ArduinoUno Digital IO 6 TX to Roomba pin 3 RXD (orange wire)
        ArduinoUno Digital IO 7 DD to Roomba pin 5 DD  (black wire)
 
        See the project description at the following website:
        https://nightskylife.wordpress.com/2015/05/26/interfacing-roomba-model-4000-with-arduino-uno/
 
*/
 
#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6); //rx,tx
int ddPin = 7;
 
 
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ddPin,  OUTPUT);
  pinMode(13, OUTPUT);
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
  // Enable full control, no safety, all commands
  mySerial.write(132);
  delay(100);
}
 
// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  greenStatusOn();          // turn the Roomba Power and Status LED Green
  delay(2000);              // wait for two seconds
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  redStatusOn();            // turn the Roomba Power and Status LED Red
  delay(1000);              // wait for a second
}
 
void greenStatusOn() {
  mySerial.write(139);       // control LEDs opcode
  mySerial.write(32);        // Status On Green 00100000 Binary = 32 Decimal
  mySerial.write((byte)0);   // Power Color Green
  mySerial.write(255);       // Intensity set to full
}
 
void redStatusOn() {
  mySerial.write(139);        // control LEDs opcode
  mySerial.write(16);         // Status On Green 00010000 Binary = 16 Decimal
  mySerial.write(255);        // Power Color Red
  mySerial.write(255);        // Intensity set to full
}