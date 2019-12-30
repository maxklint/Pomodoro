const int topLedPin = 6;
const int bottomLedPin = 7;

void ledsInit() {
  pinMode(topLedPin, OUTPUT);
  pinMode(bottomLedPin, OUTPUT);
  ledsSet(0, 0);
}

void ledsSet(bool top, bool bottom) {
  digitalWrite(topLedPin, top);
  digitalWrite(bottomLedPin, bottom);
}
