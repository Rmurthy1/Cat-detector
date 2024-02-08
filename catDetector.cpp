
/*const int LOADCELL_DOUT_PIN = 14; //D5;
const int LOADCELL_SCK_PIN = 12; //D6;
const int tareButtonPin = 13; // TARE BUTTON  // D7 is GPIO13;

// required to prevent too frequent reading (maybe)
int period = 20; 
unsigned long time_now = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tareButtonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long scaleValue;
   if (millis() > time_now + period) {
    time_now = millis();
    
   }
   int tareButtonState = digitalRead(tareButtonPin);
  if (tareButtonState == HIGH) { // refactor to use interrupts
   
    Serial.print("tare pressed. offset: ");
    
  }
}*/
#include <Arduino.h>
#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;

const byte trigPin = 4;
const byte echoPin = 5;

// Set up a new SoftwareSerial object
SoftwareSerial mySerial (rxPin, txPin);

String message = "";
bool messageReady = false;

void setup() {
  Serial.begin(9600);

// pins for software serial, may get rid of when i use hardware serial
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  // pins for the HC-SR04
  //pinMode(uint8_t pin, uint8_t mode)
    
  // Set the baud rate for the SoftwareSerial object
  mySerial.begin(9600);
}

void loop() {
  while (Serial.available()) { 
    message = Serial.readString();
    messageReady = true;
    Serial.println("wrote");
  }
  if (messageReady == true) {
    //do stuff
    messageReady = false;
    mySerial.write(message.c_str());
  }

}