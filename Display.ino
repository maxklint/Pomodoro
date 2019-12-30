#include <TM1637.h>

const int displayDioPin = 8;
const int displayClkPin = 9;
TM1637 displayDriver(displayClkPin, displayDioPin);
int8_t displayTime[] = {0x00, 0x00, 0x00, 0x00};

void displayInit() {
  displayDriver.set();
  displayDriver.init();
}

void displayShowTime(unsigned int mins, unsigned int secs, bool point) {
  displayTime[0] = mins / 10;
  displayTime[1] = mins % 10;
  displayTime[2] = secs / 10;
  displayTime[3] = secs % 10;
  displayDriver.display(displayTime);
  displayDriver.point(point);
}
