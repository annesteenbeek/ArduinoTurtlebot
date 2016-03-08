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
  while (Serial.available()>0) {
    int outData = Serial.read();
    pinSerial.write(outData); // send received data as binary data to Roomb
    Serial.print("Send to roomba: ");
    Serial.println(outData);
  }

  // Send received data back to PC
  // while (pinSerial.available() > 0) {
  //   Serial.write(pinSerial.read());
  // }
}

void startRoomba(){
  //Use Device Detect to wake Roomba
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  // delay(2000);
}
