#include <SoftwareSerial.h>
SoftwareSerial pinSerial(5, 6); //rx,tx
int ddPin = 7;
 
void setup() {
  pinMode(ddPin,  OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(57600); // PC serial
  pinSerial.begin(57600);
  startRoomba();

}
 
void loop() {
  // Send PC data to roomba
  if (Serial.available()>0) {
    char outByte = Serial.read();
    pinSerial.write(outByte); // send received data as binary data to Roomba
  }

  // Send received data back to PC
  if (pinSerial.available() > 0) {
    char inByte = pinSerial.read();
    Serial.write(inByte);
  }
}

void startRoomba(){
  //Use Device Detect to wake Roomba
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);
    //Initialize Roomba SCI
  // Start SCI
  pinSerial.write(128);
  delay(100);
  // Enable control
  pinSerial.write(130);  
  delay(100);
  // Enable full control, no safety, all commands
  pinSerial.write(132);
  delay(100);

}
