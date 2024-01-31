
const int LOADCELL_DOUT_PIN = 14;//D5;
const int LOADCELL_SCK_PIN = 12;//D6;
const int tareButtonPin = 13; // TARE BUTTON  // D7 is GPIO13;

const int _DoutPin = LOADCELL_DOUT_PIN;
const int _SckPin = LOADCELL_SCK_PIN;

long _offset = 0; // tare value
int _scale = 100; // unit scale, experimenting with this

// required to prevent too frequent reading
int period = 20; 
unsigned long time_now = 0;

float readWeight() {
  long val = (getValue() - _offset);
  return (float) val / _scale;
}


long getValue() {
  uint8_t data[3];
    long ret;
    while (digitalRead(_DoutPin)); // wait until _dout is low
    for (uint8_t j = 0; j < 3; j++)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            digitalWrite(_SckPin, HIGH);
            bitWrite(data[2 - j], 7 - i, digitalRead(_DoutPin));
            digitalWrite(_SckPin, LOW);
        }
    }

    digitalWrite(_SckPin, HIGH);
    digitalWrite(_SckPin, LOW);
    ret = (((long) data[2] << 16) | ((long) data[1] << 8) | (long) data[0])^0x800000;
    return ret;
}
void prepareScale() {
    pinMode(_SckPin, OUTPUT);
    pinMode(_DoutPin, INPUT);

    digitalWrite(_SckPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(_SckPin, LOW);
    _offset = getValue();
}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  prepareScale();
  pinMode(tareButtonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long scaleValue;
   if (millis() > time_now + period) {
    time_now = millis();
    scaleValue = readWeight();
    Serial.print("current weight: ");
    Serial.println(scaleValue);
   }
   int tareButtonState = digitalRead(tareButtonPin);
  if (tareButtonState == HIGH) {
    _offset = getValue();
    Serial.print("tare pressed. offset: ");
    Serial.println(_offset);
  }
}
