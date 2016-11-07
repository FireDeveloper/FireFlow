void BootCheck_SD();
void BootCheckFiles();
void PrintMissingFiles();
void BootCheckSensor();
void BootCheckFinal();

void BootImage() {
  BootCheck_SD(); //Check SD card
  BootCheckFiles(); //Check if all files exist
  BootCheckSensor(); //Check if sensors works
  BootCheckFinal(); //Check if SD files match software
}

void BootCheck_SD() {
  digitalWrite(13, HIGH);
  if (card.init(SPI_HALF_SPEED, SD_Card_CS))
    return;
  Serial.println(11, HEX);
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
      Serial.println(charFileName);
      PrintMissingFiles();
    }
  }
  Files.close();
}

void PrintMissingFiles() {
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

