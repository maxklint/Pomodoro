bool pomoIsWork = true;
bool pomoIsPaused = true;
bool pomoIsReset = true;
unsigned int pomoSession = 0;
unsigned int pomoMins = 0;
unsigned int pomoSecs = 0;
unsigned int pomoMillisecs = 0;

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
  bool point;
  if (pomoIsPaused || pomoIsReset)
    point = true;
  else
    point = pomoMillisecs < 500;
  displayShowTime(pomoMins, pomoSecs, point);
}

void pomoResume() {
  timerStart();
  ledsSet(pomoIsWork, !pomoIsWork);
  pomoIsPaused = false;
}

void pomoPause() {
  timerPause();
  pomoIsPaused = true;
}

void pomoStart() {
  timerPause();

  if (pomoIsWork) {
    timerSet(workDurationMins, workDurationSecs);
  } else {
    pomoSession++;
    if (pomoSession > longBreakSession)
      pomoSession = 1;

    if (pomoSession == longBreakSession)
      timerSet(longBreakDurationMins, longBreakDurationSecs);
    else
      timerSet(breakDurationMins, breakDurationSecs);
  }

  pomoResume();

  pomoIsReset = false;
}

void pomoReset() {
  timerPause();
  timerSet(workDurationMins, workDurationSecs);

  ledsSet(0, 0);

  pomoIsWork = true;
  pomoIsPaused = true;
  pomoIsReset = true;
  pomoSession = 0;
}
