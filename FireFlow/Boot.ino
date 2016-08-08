
const int SDSS = 53;

void BootImage() {
  BootCheck_SD(); //Check SD card
  PrintLoading(); //Print Loading screen
  BootCheckFiles();
  BootCheckMax(); //Work on it


  PrintMainScreen();
  while (true) {}

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
    char charFileName[s.length() ];
    s.toCharArray(charFileName, sizeof(charFileName));

    if (!SD.exists(charFileName)) {
      Serial.println(charFileName);
      PrintMissingFiles();
    }

  }
}

void BootCheckMax() {

}

void PrintMissingFiles() {
  tft.fillScreen(BLACK);
  tft.setTextSize(5);
  tft.setCursor((480  - 13 * 5 * 6) / 2,  (320 - 8 * 5) / 2); //(45, 140)
  tft.println(F("Files Missing"));
  while (true) {}
}


void PrintMainScreen() {
  tft.fillScreen(BLACK);
  bmpDraw(F("fireflow/res/Oven.bmp"), 60, 100);
  bmpDraw(F("fireflow/res/Graph.bmp"), 180, 20);
  bmpDraw(F("fireflow/res/Settings.bmp"), 300, 100);
  bmpDraw(F("fireflow/res/info.bmp"), 180, 180);
}

void TouchBootListener(uint16_t x, uint16_t y) {

}

