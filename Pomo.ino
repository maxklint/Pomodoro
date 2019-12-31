const unsigned int pomoLongBreakSession = 4;

bool pomoIsWork = true;
bool pomoIsPaused = true;
bool pomoIsReset = true;
unsigned int pomoSession = 0;
unsigned int pomoMins = 0;
unsigned int pomoSecs = 0;
unsigned int pomoMillisecs = 0;

unsigned int pomoWorkDuration = 0;
unsigned int pomoBreakDuration = 0;
unsigned int pomoLongBreakDuration = 0;
bool pomoSound = false;

unsigned long pauseStartedAt = 0;

void pomoInit() {
}

void pomoUpdate() {
  timerGet(&pomoMins, &pomoSecs, &pomoMillisecs);

  if (pomoIsPaused) return;

  if (pomoMins == 0 && pomoSecs == 0 && pomoMillisecs == 0) {
    pomoIsWork = !pomoIsWork;
    pomoStart();
  }
}

void pomoClick() {
  if (pomoIsReset) {
    pomoStart();
  } else {
    if (pomoIsPaused)
      pomoResume();
    else
      pomoPause();
  }
}

void pomoDoubleClick() {
  pomoReset();
}

void pomoDraw() {
  if (pomoIsReset) {
    displayShowTime(pomoMins, pomoSecs, true);
  }
  else if (pomoIsPaused) {
    int phase = ((millis() - pauseStartedAt) % 2000) < 1000;
    if (phase)
      displayShowBar(pomoSession);
    else
      displayShowTime(pomoMins, pomoSecs, true);

  }
  else {
    displayShowTime(pomoMins, pomoSecs, pomoMillisecs < 500);
  }
}

void pomoResume() {
  timerStart();
  ledsSet(pomoIsWork, !pomoIsWork);
  pomoIsPaused = false;
}

void pomoPause() {
  pauseStartedAt = millis();
  timerPause();
  pomoIsPaused = true;
}

void pomoStart() {
  timerPause();

  if (pomoIsWork) {
    pomoSession++;
    if (pomoSession > pomoLongBreakSession)
      pomoSession = 1;

    timerSet(pomoWorkDuration, 0);
  } else {
    if (pomoSession == pomoLongBreakSession)
      timerSet(pomoLongBreakDuration, 0);
    else
      timerSet(pomoBreakDuration, 0);
  }

  pomoResume();

  pomoIsReset = false;
}

void pomoReset() {
  timerPause();
  timerSet(pomoWorkDuration, 0);

  ledsSet(0, 0);

  pomoIsWork = true;
  pomoIsPaused = true;
  pomoIsReset = true;
  pomoSession = 0;
}


void pomoShow() {
  pomoSound = (bool) EEPROM.read(0);
  pomoWorkDuration = (unsigned int) EEPROM.read(1);
  pomoBreakDuration = (unsigned int) EEPROM.read(2);
  pomoLongBreakDuration = (unsigned int) EEPROM.read(3);

  pauseStartedAt = millis();
}

void pomoHide() {
}
