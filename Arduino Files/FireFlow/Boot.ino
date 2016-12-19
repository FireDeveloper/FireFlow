void BootImage() {
  BootCheck_SD(); //Check SD card
  BootCheckFiles(); //Check if all files exist
  BootCheckSensor(); //Check if sensors works
  BootCheckFinal(); //Check if SD files match software
  LoadGains();
  LoadUnits();
  LoadSound();
  LoadOutputs();
  FinishBoot();
}

void BootCheck_SD() {
  if (card.init(SPI_HALF_SPEED, SD_Card_CS))
    SD.begin(SD_Card_CS);
  return;
}

void BootCheckFiles() {
  File Files;  // Open requested file on SD card

  if ((Files = SD.open(F("fireflow/set/FileList.txt"))) == NULL)
    PrintMissingFiles();

  while (Files.available()) {
    String s = Files.readStringUntil('\n');
    char charFileName[s.length()];
    s.toCharArray(charFileName, sizeof(charFileName));

    if (!SD.exists(charFileName) && Debug) {
      Serial1.println(charFileName);
      PrintMissingFiles();
    }
  }
  Files.close();
}

void PrintMissingFiles() {
  pinMode(13, OUTPUT);
}

void BootCheckSensor() {
  LeftTC.readInternal();
  RightTC.readInternal();
  Rtc.Begin();
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
}

void BootCheckFinal() {
}

void LoadGains() {
  File gains = SD.open(F("fireflow/set/Gains.txt"));
  String S_P = gains.readStringUntil('\n');
  Settings.PID_P = S_P.toFloat();
  String S_I = gains.readStringUntil('\n');
  Settings.PID_I = S_I.toFloat();
  String S_D = gains.readStringUntil('\n');
  Settings.PID_D = S_D.toFloat();
  gains.close();

  while (!NexNumber(0, 4, "PID_P").setValue((int) Settings.PID_P)) {}
  while (!NexNumber(0, 5, "PID_I").setValue((int) Settings.PID_I)) {}
  while (!NexNumber(0, 6, "PID_D").setValue((int) Settings.PID_D)) {}

  while (!NexNumber(0, 14, "PID_P_zero").setValue(getZeros(S_P))) {}
  while (!NexNumber(0, 15, "PID_I_zero").setValue(getZeros(S_I))) {}
  while (!NexNumber(0, 16, "PID_D_zero").setValue(getZeros(S_D))) {}

  while (!NexNumber(0, 7, "PID_P_dec").setValue(S_P.toInt())) {}
  while (!NexNumber(0, 8, "PID_I_dec").setValue(S_I.toInt())) {}
  while (!NexNumber(0, 9, "PID_D_dec").setValue(S_D.toInt())) {}
}

void LoadUnits() {
  File Config = SD.open(F("fireflow/set/config.txt"));
  Config.seek(3);
  char s = '1';
  Config.read(&s, 1);
  if (s == '0') {
    //Serial1.println("Farhenait on SD");
    Settings.Celsius = false;
    while (!NexNumber(0, 17, "Celsius").setValue(0)) {}
  }  else
    Settings.Celsius = true; //It is preset to Celsius
}

void LoadSound() {
  File Config = SD.open(F("fireflow/set/config.txt"));
  Config.seek(6);
  char s = '1';
  Config.read(&s, 1);
  if (s == '0') {
    Settings.Sound = false;
    while (!NexNumber(0, 21, "Sound").setValue(0)) {}
  }  else
    Settings.Sound = true; //It is preset to Celsius
}

void LoadOutputs() {
  String temp;
  File Outputs = SD.open(F("fireflow/set/Outputs.txt"));
  Settings.R_Top = Outputs.readStringUntil('\n').toInt();
  Settings.R_Bot = Outputs.readStringUntil('\n').toInt();
  Settings.R_Boost = Outputs.readStringUntil('\n').toInt();
  Settings.Fan = Outputs.readStringUntil('\n').toInt();
  Settings.Led_Green = Outputs.readStringUntil('\n').toInt();
  Settings.Led_Orange = Outputs.readStringUntil('\n').toInt();
  Settings.Led_Red = Outputs.readStringUntil('\n').toInt();
  Outputs.close();

  while (!NexNumber(0, 10, "Loading_Screen.R_top").setValue(ConvertOutputToID(Settings.R_Top))) {}
  while (!NexNumber(0, 11, "Loading_Screen.R_bot").setValue(ConvertOutputToID(Settings.R_Bot))) {}
  while (!NexNumber(0, 12, "Loading_Screen.fan").setValue(ConvertOutputToID(Settings.Fan))) {}
  while (!NexNumber(0, 13, "Loading_Screen.R_boost").setValue(ConvertOutputToID(Settings.R_Boost))) {}
  while (!NexNumber(0, 18, "Loading_Screen.Led_Green").setValue(ConvertOutputToID(Settings.Led_Green))) {}
  while (!NexNumber(0, 19, "Loading_Screen.Led_Orange").setValue(ConvertOutputToID(Settings.Led_Orange))) {}
  while (!NexNumber(0, 20, "Loading_Screen.Led_Red").setValue(ConvertOutputToID(Settings.Led_Red))) {}
}

byte ConvertOutputToID(byte Output) {
  if (Output == Out_1)
    return 1;
  else if (Output == Out_2)
    return 2;
  else if (Output == Out_3)
    return 3;
  else if (Output == Out_4)
    return 4;
  else if (Output == PWM_1)
    return 5;
  else if (Output == PWM_2)
    return 6;
  else if (Output == PWM_3)
    return 7;
  else
    return 0;
}

void FinishBoot() {
  while (!NexPage(1, 0, "Main_Screen").show()) {}
}

