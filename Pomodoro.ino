const unsigned int workDurationMins = 0;
const unsigned int workDurationSecs = 5;
const unsigned int breakDurationMins = 0;
const unsigned int breakDurationSecs = 3;
const unsigned int longBreakDurationMins = 0;
const unsigned int longBreakDurationSecs = 8;

const unsigned int longBreakSession = 2;

enum InputEvent {
  BTN_EV_NONE = 0,
  BTN_EV_CLICK,
  BTN_EV_DOUBLE,
  BTN_EV_LONG
};
volatile int event = BTN_EV_NONE;

bool isWork = true;
bool isPaused = true;
unsigned int session = 0;

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

  Serial.println("initialization complete");

  stateTransition(true, true, true);
}

void loop() {
  processInputEvent();
  buttonUpdate();

  unsigned int mins, secs, millisecs;
  timerGet(&mins, &secs, &millisecs);

  if (!isPaused) {
    if (mins == 0 && secs == 0 && millisecs == 0) {
      stateTransition(!isWork, false, true);
    }
  }

  unsigned long now = millis();
  if (now - lastRedraw > redrawInterval) {
    bool point;
    if (isPaused)
      point = true;
    else
      point = millisecs < 500;
    displayShowTime(mins, secs, point);
    lastRedraw = now;
  }
}

void processInputEvent() {
  switch (event)
  {
    case BTN_EV_CLICK:
      Serial.println("single");
      stateTransition(isWork, !isPaused, false);
      event = BTN_EV_NONE;
      break;
    case BTN_EV_DOUBLE:
      Serial.println("double");
      stateTransition(true, true, true);
      event = BTN_EV_NONE;
      break;
    case BTN_EV_LONG:
      Serial.println("long");
      event = BTN_EV_NONE;
      break;
    default:
      break;
  }
}

void stateTransition(bool work, bool pause, bool reset) {
  if (pause) {
    timerPause();

    if (reset) {
      timerSet(workDurationMins, workDurationSecs);
      ledsSet(0, 0);
      isWork = work;
      session = 0;
    }

    isPaused = true;
  } else {
    if (reset) {
      timerPause();

      if (work) {
        timerSet(workDurationMins, workDurationSecs);
      } else {
        session++;
        if (session > longBreakSession)
          session = 1;
          
        if (session == longBreakSession)
          timerSet(longBreakDurationMins, longBreakDurationSecs);
        else
          timerSet(breakDurationMins, breakDurationSecs);
      }
    }

    ledsSet(work, !work);
    timerStart();
    isWork = work;
    isPaused = false;
  }
}
