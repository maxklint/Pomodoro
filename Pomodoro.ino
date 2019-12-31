const unsigned int workDurationMins = 0;
const unsigned int workDurationSecs = 5;
const unsigned int breakDurationMins = 0;
const unsigned int breakDurationSecs = 3;
const unsigned int longBreakDurationMins = 0;
const unsigned int longBreakDurationSecs = 8;

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
