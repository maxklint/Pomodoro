const unsigned int menuNumSettings = 4;
unsigned int menuSetting = 0;
unsigned long menuSettingDisplayStartedAt = 0;

void menuInit() {
}

void menuUpdate() {
}

void menuClick() {

}

void menuDoubleClick() {
  menuSetting++;
  if (menuSetting >= menuNumSettings)
    menuSetting = 0;

  menuSettingDisplayStartedAt = millis();
}

void menuDraw() {
  char name[4] = {};
  int value = 0;
  char valueStr[4] = {};
  bool valueIsNumeric = true;

  switch (menuSetting) {
    case 0:
      strncpy(name, "Act ", 4);
      value = 25;
      break;
    case 1:
      strncpy(name, "br  ", 4);
      value = 5;
      break;
    case 2:
      strncpy(name, "br L", 4);
      value = 15;
      break;
    case 3:
      strncpy(name, "Snd ", 4);
      strncpy(valueStr, " off", 4);
      valueIsNumeric = false;
      break;
  }

  int phase = ((millis() - menuSettingDisplayStartedAt) % 2000) < 1000;
  if (phase)
    displayShowText(name);
  else {
    if (valueIsNumeric)
      displayShowValue(value);
    else
      displayShowText(valueStr);
  }

}

void menuShow() {
  menuSetting = 0;
  menuSettingDisplayStartedAt = millis();
}

void menuHide() {
}
