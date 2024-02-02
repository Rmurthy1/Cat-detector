
const int LOADCELL_DOUT_PIN = 14; //D5;
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
}
