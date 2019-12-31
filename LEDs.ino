const int ledsTopPin = 6;
const int ledsBottomPin = 7;

volatile int ledsTop = 0;
volatile int ledsBottom = 0;

void ledsInit() {
  pinMode(ledsTopPin, OUTPUT);
  pinMode(ledsBottomPin, OUTPUT);
  ledsSet(0, 0);
}

void ledsUpdate() {
  static int phase = 0;
  phase++;
  if (phase == 8) phase = 0;
  if (!phase) {
    digitalWrite(ledsTopPin, ledsTop);
    digitalWrite(ledsBottomPin, ledsBottom);
  } else {
    digitalWrite(ledsTopPin, 0);
    digitalWrite(ledsBottomPin, 0);
  }
}

void ledsSet(bool top, bool bottom) {
  ledsBottom = bottom;
  ledsTop = top;
}
