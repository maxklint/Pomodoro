const unsigned int menuNumSettings = 4;
const unsigned int menuMaxOptions = 4;
char menuSettings[menuNumSettings] = {1, 25, 5, 15};
char menuOptions[menuNumSettings][menuMaxOptions] = {{0, 1}, {15, 25, 40, 50}, {3, 5, 10}, {10, 15, 20, 30}};
char menuOptionsLength[menuNumSettings] = {2, 4, 3, 4};
char menuSettingsName[menuNumSettings][5] = {"Snd ", "Act ", "br  ", "br L"};
char menuSettingsType[menuNumSettings] = {'b', 'd', 'd', 'd'};
unsigned int menuSetting = 0;
unsigned long menuSettingDisplayStartedAt = 0;

void menuInit() {
}

void menuUpdate() {
}

void menuClick() {
  menuSetting++;
  if (menuSetting >= menuNumSettings)
    menuSetting = 0;

  menuSettingDisplayStartedAt = millis();
}

void menuDoubleClick() {
  int i;
  for (i = 0; i < menuOptionsLength[menuSetting]; i++) {
    if (menuSettings[menuSetting] == menuOptions[menuSetting][i]) {
      break;
    }
  }

  i++;

  if (i == menuOptionsLength[menuSetting])
    i = 0;

  menuSettings[menuSetting] = menuOptions[menuSetting][i];

  menuSettingDisplayStartedAt = millis() - 1000;
}

void menuDraw() {
  char name[4] = {};
  memcpy(name, menuSettingsName[menuSetting], 4);
  int value = menuSettings[menuSetting];
  char valueStr[4] = {};

  if (menuSettingsType[menuSetting] == 'b')
    strncpy(valueStr, value ? "  on" : " off", 4);

  int phase = ((millis() - menuSettingDisplayStartedAt) % 2000) < 1000;
  if (phase)
    displayShowText(name);
  else {
    if (menuSettingsType[menuSetting] == 'b')
      displayShowText(valueStr);
    else
      displayShowValue(value);
  }
}

void menuShow() {
  for (int i = 0; i < 4; i++) {
    menuSettings[i] = (char) EEPROM.read(i);
  }
  menuSetting = 0;
  menuSettingDisplayStartedAt = millis();
}

void menuHide() {
  for (int i = 0; i < 4; i++) {
    EEPROM.write(i, menuSettings[i]);
  }
}
