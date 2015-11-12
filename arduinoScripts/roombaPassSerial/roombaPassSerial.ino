#include <SoftwareSerial.h>
SoftwareSerial pinSerial(5, 6); //rx,tx
int ddPin = 7;
int data;
 
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ddPin,  OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600); // PC serial
  pinSerial.begin(57600);
  startRoomba();

}
 
// the loop function runs over and over again forever
void loop() {
  if (Serial.available()>0) {
    data = Serial.parseInt();
    if (data<0){
      startRoomba();
    }
    pinSerial.write((byte)data); // send received data as binary data to Roomb
    Serial.print("Send to roomba: "); Serial.println(data);
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