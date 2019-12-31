#include <TM1637Display.h>

const int displayDioPin = 8;
const int displayClkPin = 9;
TM1637Display displayDriver(displayClkPin, displayDioPin);
uint8_t displayBuffer[] = {0x00, 0x00, 0x00, 0x00};

void displayInit() {
  displayDriver.setBrightness(2);
}

void displayShowTime(unsigned int mins, unsigned int secs, bool point) {
  displayDriver.showNumberDecEx(mins, point ? 0xFF : 0, true, 2, 0);
  displayDriver.showNumberDec(secs, true, 2, 2);
}

void displayShowBar(unsigned int level) {
  for (int i = 0; i < 4; i++) {
    if (level-- == 0) break;
    displayBuffer[i] = SEG_G;
  }
  displayDriver.setSegments(displayBuffer);
}
