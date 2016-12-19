char* NumberConverter(int Num, byte Buffer) {
  char buff[Buffer];
  itoa(Num, buff, 10);
  return buff[Buffer];
}

byte getZeros(String &s) {
  float number = s.toFloat();
  if ((number - (int)number) > 0) //if contains digits
    s.remove(0, s.indexOf('.') + 1); //remove them
  else
    s.remove(0, s.indexOf('.'));

  byte counter = 0;
  while (s.charAt(counter) == '0')//count zeros after comma
    counter++;
  return counter;
}

char* StringConverter(String txt) {
  char buff[txt.length()];
  txt.toCharArray(*buff, txt.length());
  return buff;
}

void FlashLedOn() {
  if (Settings.Flash_Red)
    OnLedRed(true);
  if (Settings.Flash_Orange)
    OnLedOrange(true);
  if (Settings.Flash_Green)
    OnLedGreen(true);
}

void FlashLedOff() {
  if (Settings.Flash_Red)
    OnLedRed(false);
  if (Settings.Flash_Orange)
    OnLedOrange(false);
  if (Settings.Flash_Green)
    OnLedGreen(false);
}

void LedOff() {
  OnLedRed(false);
  OnLedOrange(false);
  OnLedGreen(false);
}

void OnLedGreen(bool On) {
  if (Settings.Led_Green != Out_Off)
    if (On)
      digitalWrite(Settings.Led_Green, HIGH);
    else
      digitalWrite(Settings.Led_Green, LOW);
}
void OnLedOrange(bool On) {
  if (Settings.Led_Orange != Out_Off)
    if (On)
      digitalWrite(Settings.Led_Orange, HIGH);
    else
      digitalWrite(Settings.Led_Orange, LOW);
}
void OnLedRed(bool On) {
  if (Settings.Led_Red != Out_Off)
    if (On)
      digitalWrite(Settings.Led_Red, HIGH);
    else
      digitalWrite(Settings.Led_Red, LOW);
}

void FlashLedGreen(bool On) {
  if (Settings.Led_Green != Out_Off)
    Settings.Flash_Green = On;
}
void FlashLedOrange(bool On) {
  if (Settings.Led_Orange != Out_Off)
    Settings.Flash_Orange = On;
}
void FlashLedRed(bool On) {
  if (Settings.Led_Red != Out_Off)
    Settings.Flash_Red = On;
}

