#include <RingBuf.h>

const int buttonPin = 3;
const unsigned long buttonLongPressTime = 600;
const unsigned long buttonDebounceTime = 50;
const unsigned long buttonDoubleClickTime = 200;
const unsigned long buttonDoubleClickDebounceTime = 500;

RingBuf<unsigned long , 32> buttonBuf;
RingBuf<InputEvent, 16> buttonOutBuf;

void buttonInit() {
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, RISING);
}

InputEvent buttonUpdate() {
  static unsigned long lastPress = 0;
  static unsigned long ignoreEventsUntil = 0;
  static bool pending = false;

  unsigned long timestamp;
  while (buttonBuf.lockedPop(timestamp)) {
    if (timestamp <= ignoreEventsUntil) continue;
    if (timestamp - lastPress <= buttonDebounceTime) continue;
    pending = true;
    if (timestamp - lastPress <= buttonDoubleClickTime) {
      buttonOutBuf.push(BTN_EV_DOUBLE);
      ignoreEventsUntil = timestamp + buttonDoubleClickDebounceTime;
      pending = false;
    }
    lastPress = timestamp;
  }

  unsigned long now = millis();
  if (pending && now > ignoreEventsUntil) {
    pending = false;
    int buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && now - lastPress > buttonDoubleClickTime)
      buttonOutBuf.push(BTN_EV_CLICK);
    else if (buttonState == HIGH && now - lastPress > buttonLongPressTime)
      buttonOutBuf.push(BTN_EV_LONG);
    else
      pending = true; // still pending
  }

  InputEvent outEv;
  if (buttonOutBuf.pop(outEv))
    return outEv;
  else
    return BTN_EV_NONE;
}

void buttonISR() {
  buttonBuf.push(millis());
}
