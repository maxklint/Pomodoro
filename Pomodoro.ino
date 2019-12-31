#include <EEPROM.h>

typedef enum {
  BTN_EV_NONE = 0,
  BTN_EV_CLICK,
  BTN_EV_DOUBLE,
  BTN_EV_LONG
} InputEvent;

const unsigned long redrawInterval = 50;
unsigned long lastRedraw = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("startup");

  buttonInit();
  displayInit();
  ledsInit();
  buzzerInit();
  timerInit();

  menuInit();
  pomoInit();

  pomoShow();
  pomoReset();

  Serial.println("initialization complete");
}

void loop() {
  static bool isMenuOpen = false;

  // process input
  InputEvent ev = buttonUpdate();
  switch (ev)
  {
    case BTN_EV_CLICK:
      Serial.println("single");
      if (isMenuOpen) menuClick();
      else pomoClick();
      break;
    case BTN_EV_DOUBLE:
      Serial.println("double");
      if (isMenuOpen) menuDoubleClick();
      else pomoDoubleClick();
      break;
    case BTN_EV_LONG:
      Serial.println("long");
      isMenuOpen = !isMenuOpen;
      if (isMenuOpen) {
        menuShow();
        pomoHide();
      } else {
        menuHide();
        pomoShow();
      }
      break;
  }

  // regular state update
  menuUpdate();
  pomoUpdate();

  // redraw
  unsigned long now = millis();
  if (now - lastRedraw > redrawInterval) {
    if (isMenuOpen)
      menuDraw();
    else
      pomoDraw();
    lastRedraw = now;
  }
}
