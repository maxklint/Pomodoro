const int buttonPin = 3;
const unsigned long longPressTime = 600;
const unsigned long doubleClickTime = 200;
const unsigned long doubleClickDebounceTime = 500;

int buttonState = 0;
unsigned long lastDown = 0;
unsigned long lastUp = 0;
bool waitingForUp = false;
bool waitingForDoubleClick = false;
bool ignoreEvents = false;

void buttonInit() {
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, CHANGE);
  buttonState = digitalRead(buttonPin);
}

void buttonUpdate() {
  unsigned long now = millis();

  if (waitingForUp && now - lastDown > longPressTime) {
    event = BTN_EV_LONG;
    waitingForUp = false;
  }

  if (ignoreEvents && now - lastUp > doubleClickDebounceTime) {
    ignoreEvents = false;
  }

  if (waitingForDoubleClick && now - lastUp > doubleClickTime) {
    event = BTN_EV_CLICK;
    waitingForDoubleClick = false;
  }
}

void buttonISR() {
  buttonState = !buttonState;
  if (buttonState) {
    // press
    if (ignoreEvents) return;

    waitingForUp = true;
    lastDown = millis();
  } else {
    // release
    if (ignoreEvents) return;
    if (!waitingForUp) return;

    waitingForUp = false;
    unsigned long now = millis();
    if (now - lastUp < doubleClickTime) {
      waitingForDoubleClick = false;
      ignoreEvents = true;
      event = BTN_EV_DOUBLE;
    } else {
      waitingForDoubleClick = true;
    }

    lastUp = now;
  }
}
