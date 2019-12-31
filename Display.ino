#include <TM1637Display.h>

const int displayDioPin = 8;
const int displayClkPin = 9;
TM1637Display displayDriver(displayClkPin, displayDioPin);
uint8_t displayBuffer[] = {0x00, 0x00, 0x00, 0x00};

void displayInit() {
  displayDriver.setBrightness(2);
}

void displayClear() {
  memset(displayBuffer, 0, 4);
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

void displayShowValue(int value) {
  displayDriver.showNumberDec(value, false);
}

void displayShowText(char text[4]) {
  for (int i = 0; i < 4; i++)
    displayBuffer[i] = displayDecodeChar(text[i]);
  displayDriver.setSegments(displayBuffer);
}

uint8_t displayDecodeChar(char c) {
  switch (c) {
    default:
      return 0x00;
    case 'A':
      return 0x77;
    case 'b':
      return 0x7C;
    case 'c':
      return 0x58;
    case 'd':
      return 0x5E;
    case 'f':
      return 0x71;
    case 'L':
      return 0x38;
    case 'n':
      return 0x54;
    case 'o':
      return 0x5C;
    case 'r':
      return 0x50;
    case 'S':
      return 0x6D;
    case 't':
      return 0x78;
  }
}
