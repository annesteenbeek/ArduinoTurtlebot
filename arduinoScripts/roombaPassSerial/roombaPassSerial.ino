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
  while (Serial.available()>0) {
    int outByte = Serial.parseInt();
    pinSerial.write((byte)outByte); // send received data as binary data to Roomb
    Serial.print("Send to roomba: "); Serial.println(outByte);
  }

  // Send received data back to PC
  while (pinSerial.available() > 0) {
    byte inByte = pinSerial.read();
    Serial.print("Received from roomba: ");
    Serial.println(inByte);
  }
}

void startRoomba(){
  //Use Device Detect to wake Roomba
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
}
