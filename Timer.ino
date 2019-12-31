#include <TimerOne.h>

// NOTE: MUST to be a divisor of 1000 for the code below to work
const unsigned int timerInterval = 1; // every 1ms

volatile bool timerIsPaused = true;

volatile unsigned int timerMins = 0;
volatile unsigned int timerSecs = 0;
volatile unsigned int timerMillisecs = 0;

void timerInit() {
  Timer1.initialize(timerInterval * 1000);
  Timer1.attachInterrupt(timerISR);
}

void timerSet(unsigned int mins, unsigned int secs) {
  timerMins = mins;
  timerSecs = secs;
  timerMillisecs = 0;
}

void timerStart() {
  timerIsPaused = false;
}

void timerPause() {
  timerIsPaused = true;
}

void timerGet(unsigned int *mins, unsigned int *secs, unsigned int *millisecs) {
  *mins = timerMins;
  *secs = timerSecs;
  *millisecs = timerMillisecs;
}

void timerISR() {
  ledsUpdate();

  if (timerIsPaused)
    return;

  if (timerMillisecs == 0 && timerSecs == 0 && timerMins == 0) {
    timerPause();
    return;
  }

  if (timerMillisecs == 0) {
    timerMillisecs = 1000;

    if (timerSecs == 0) {
      timerSecs = 60;
      timerMins -= 1;
    }

    timerSecs -= 1;
  }

  timerMillisecs -= timerInterval;
}
