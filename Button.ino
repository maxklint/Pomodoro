const int buttonPin = 3;
const unsigned long buttonLongPressTime = 600;
const unsigned long buttonDebounceTime = 50;
const unsigned long buttonDoubleClickTime = 200;
const unsigned long buttonEventDebounceTime = 500;

void buttonInit() {
  pinMode(buttonPin, INPUT);
}

InputEvent buttonUpdate() {
  static unsigned long lastPress = 0;
  static unsigned long ignoreEventsUntil = 0;
  static bool pending = false;

  static int state = digitalRead(buttonPin);
  static int prevState = state;

  unsigned long now = millis();
  unsigned long timestamp = 0;
  InputEvent outEv = BTN_EV_NONE;

  prevState = state;
  state = digitalRead(buttonPin);

  if (state && !prevState)
    timestamp = now;

  if (!state && prevState)
    ignoreEventsUntil = now + buttonDebounceTime;

  if (timestamp) {
    if (timestamp > ignoreEventsUntil && timestamp - lastPress > buttonDebounceTime) {
      pending = true;
      if (timestamp - lastPress <= buttonDoubleClickTime) {
        outEv = BTN_EV_DOUBLE;
        ignoreEventsUntil = timestamp + buttonEventDebounceTime;
        pending = false;
      }
      lastPress = timestamp;
    }
  }

  if (pending && now > ignoreEventsUntil) {
    pending = false;
    ignoreEventsUntil = now + buttonEventDebounceTime;
    if (!state && now - lastPress > buttonDoubleClickTime)
      outEv = BTN_EV_CLICK;
    else if (state && now - lastPress > buttonLongPressTime)
      outEv = BTN_EV_LONG;
    else {
      pending = true; // still pending
      ignoreEventsUntil = 0;
    }
  }

  return outEv;
}
