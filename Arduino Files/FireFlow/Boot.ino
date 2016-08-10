
const int SDSS = 53;

void BootImage() {
  BootCheck_SD(); //Check SD card
  PrintLoading(); //Print Loading screen
  BootCheckFiles();
  BootCheckSensor();
  BootCheckFinal(); //Work on it
}

void BootCheck_SD() {
  if (card.init(SPI_HALF_SPEED, SDSS))
    return;
  tft.setTextSize(5);
  tft.setTextColor(WHITE);
  tft.setCursor((480  - 13 * 5 * 6) / 2,  (320 - 8 * 5) / 2); //(45, 140)
  tft.println(F("SD Card Error"));
  while (true) {}
}

void PrintLoading() {
  SD.begin(SDSS);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(480  - 7  * 6 * 2 - 1,  320 - 8 * 2); //(45, 140)
  tft.println(F("Ver 0.1"));
  delay(100);

  if (!SD.exists(F("fireflow/res/Boot_Img.bmp")))
    PrintMissingFiles();

  bmpDraw(F("fireflow/res/Boot_Img.bmp"), 124, 40);

}

void BootCheckFiles() {
  File Files;  // Open requested file on SD card

  if ((Files = SD.open(F("fireflow/set/FileList.txt"))) == NULL)
    PrintMissingFiles();

  while (Files.available()) {
    String s = Files.readStringUntil('\n');
    char charFileName[s.length()];
    s.toCharArray(charFileName, sizeof(charFileName));

    if (!SD.exists(charFileName)) {
      Serial.println(charFileName);
      PrintMissingFiles();
    }
  }
  Files.close();
}

void BootCheckSensor() {

}

void BootCheckFinal() {
  File Files;
  Files = SD.open(FILE_CONFIG);
  if (Files.read() == FILE_TRUE) { //First Boot
    Files.close();
    TouchScreenCalibrate();
    Files =  SD.open(FILE_CONFIG, FILE_WRITE);

    Files.seek(0);
    Files.print("1");
    Files.close();
    Save_TFT_Calibration();
  } else {
    Load_TFT_Calibration();
    PrintMainScreen();
  }
}

void PrintMissingFiles() {
  tft.fillScreen(BLACK);
  tft.setTextSize(5);
  tft.setCursor((480  - 13 * 5 * 6) / 2,  (320 - 8 * 5) / 2); //(45, 140)
  tft.println(F("Files Missing"));
  while (true) {}
}

void TouchBootListener() {

}
