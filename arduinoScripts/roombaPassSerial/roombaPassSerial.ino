#include <SoftwareSerial.h>
SoftwareSerial pinSerial(5, 6); //rx,tx
int ddPin = 7;

void setup() {
  pinMode(ddPin,  OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(57600); // PC serial
  while (!Serial){
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinSerial.begin(57600);
  startRoomba();

}
 
void loop() {
  // Send PC data to roomba
  if (Serial.available() > 0) {
    pinSerial.print(Serial.read()); // send received data as binary data to Roomba
  }

  // Send received data back to PC
  if (pinSerial.available() > 0) {
    Serial.print(pinSerial.read());

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
