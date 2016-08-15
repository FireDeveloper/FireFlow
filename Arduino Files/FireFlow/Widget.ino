
//Back Button
bool Back_Button_Enable = true;
void TFT_Draw_Back_Button() {
  //y = 0-30
  tft.fillTriangle(15, 0,  15,  30,  0,  15,  WHITE);
  tft.fillRect( 15,  7,  40,  17,  WHITE);
  Back_Button_Enable = true;
}

void TFT_Erase_Back_Button() {
  tft.fillTriangle(15, 0,  15,  30,  0,  15,  BLACK);
  tft.fillRect( 15,  7,  40,  17,  BLACK);
  Back_Button_Enable = false;
}

bool TFT_Back_Button_Pressed() {
  if (tp.x < 55 && tp.y < 30 & Back_Button_Enable)
    return true;
  return false;
}

//On-off Holo Switch
void TFT_Draw_Holo_Switch_On(uint16_t x, uint16_t y) {
  tft.fillRect( x,  y,  62,  40,  DARK_GRAY); //off side
  tft.fillTriangle( x + 39,  y,  x + 62,  y,  x + 62,  y + 39,  HOLO_BLUE_DARK); //on side
  tft.fillRect( x + 63,  y,  37,  40,  HOLO_BLUE_DARK);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(x + 63,  y + 12);
  tft.print(F("ON"));
}

void TFT_Draw_Holo_Switch_Off(uint16_t x, uint16_t y) {
  tft.fillRect( x + 39,  y,  61,  40,  DARK_GRAY); //on side
  tft.fillTriangle( x + 38,  y,  x + 39,  y + 39,  x + 61,  y + 39,  GRAY); //on side
  tft.fillRect( x,  y,  38,  40,  GRAY);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(x + 7,  y + 12);
  tft.print(F("OFF"));
}

void TFT_Draw_Small_Button_Clock(uint16_t x, uint16_t y) {
  tft.fillCircle(x, y, 25, GRAY);
  tft.drawCircle(x, y, 25, WHITE);

  tft.fillCircle(x, y, 17, WHITE);
  tft.fillCircle(x, y, 15, DARK_GRAY);

  tft.drawFastVLine(x, y - 12, 14, WHITE);
  tft.drawFastVLine(x + 1, y - 12, 14, WHITE);
  tft.drawFastHLine(x + 2, y, 12, WHITE);
  tft.drawFastHLine(x + 2, y + 1, 12, WHITE);
}

void TFT_Draw_Small_Button_Temp(uint16_t x, uint16_t y) {
  tft.fillCircle(x, y, 25, GRAY);
  tft.drawCircle(x, y, 25, WHITE);

  tft.fillRoundRect(x - 3, y - 18, 7, 27, 3, DARK_GRAY);
  tft.fillRoundRect(x - 3, y - 4, 7, 13, 3, WHITE);
  tft.drawRoundRect(x - 3, y - 18, 7, 27, 3, WHITE);
  tft.fillCircle(x, y + 13, 7, WHITE);
}

void TFT_Draw_Analog_Segment(uint16_t center_x, uint16_t center_y, int theta, uint8_t r, uint16_t color) {
  int end_x = r * cos(theta * DEGREES_TO_RADIANS);
  int end_y = r * sin(theta * DEGREES_TO_RADIANS);

  //Romvos
  int P_1_x = r / 2 * cos((theta - 10) * DEGREES_TO_RADIANS);
  int P_1_y = r / 2 * sin((theta - 10) * DEGREES_TO_RADIANS);

  int P_2_x = r / 2 * cos((theta + 10) * DEGREES_TO_RADIANS);
  int P_2_y = r / 2 * sin((theta + 10) * DEGREES_TO_RADIANS);

  tft.fillTriangle(center_x, center_y, center_x + end_x, center_y - end_y, center_x + P_1_x, center_y - P_1_y, color);

  tft.fillTriangle(center_x, center_y, center_x + end_x, center_y - end_y, center_x + P_2_x, center_y - P_2_y, color);
}

void ExportImageInterrupt() {
  UpdateScreenHelper = ExportImage;
}

void ExportImage() {
  Serial.println("Export Image");
  char Name[] = "ss_00.bmp";

  byte VH, VL;
  int i, j = 0;

  File outFile;
  //Create the File
  int counter = 0;
  while (SD.exists(Name)) {
    String s= Name;
    Serial.println(s + " Exists");
    counter++;
    Name[3] = counter / 10 + '0';
    Name[4] = counter % 10 + '0';
  }

  outFile = SD.open(Name, FILE_WRITE);
  if (!outFile) {
    Serial.println("err opng file");
    return;
  };
  outFile.seek(0);

  unsigned char bmFlHdr[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
  // 54 = std total "old" Windows BMP file header size = 14 + 40

  unsigned char bmInHdr[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 0};
  // 40 = info header size
  //  1 = num of color planes
  // 16 = bits per pixel
  // all other header info = 0, including RI_RGB (no compr), DPI resolution

  unsigned long fileSize = 2ul * SS_H * SS_W + 54; // pix data + 54 byte hdr

  bmFlHdr[ 2] = (unsigned char)(fileSize      ); // all ints stored little-endian
  bmFlHdr[ 3] = (unsigned char)(fileSize >>  8); // i.e., LSB first
  bmFlHdr[ 4] = (unsigned char)(fileSize >> 16);
  bmFlHdr[ 5] = (unsigned char)(fileSize >> 24);

  bmInHdr[ 4] = (unsigned char)(    SS_W     );
  bmInHdr[ 5] = (unsigned char)(    SS_W >>  8);
  bmInHdr[ 6] = (unsigned char)(    SS_W >> 16);
  bmInHdr[ 7] = (unsigned char)(    SS_W >> 24);
  bmInHdr[ 8] = (unsigned char)(    SS_H      );
  bmInHdr[ 9] = (unsigned char)(    SS_H >>  8);
  bmInHdr[10] = (unsigned char)(    SS_H >> 16);
  bmInHdr[11] = (unsigned char)(    SS_H >> 24);

  outFile.write(bmFlHdr, sizeof(bmFlHdr));
  outFile.write(bmInHdr, sizeof(bmInHdr));

  for (i = SS_H; i > 0; i--) {
    for (j = 0; j < SS_W; j++) {

      uint16_t rgb = tft.readPixel(j, i - 1); // get pix color in rgb565 format //Fire fix '-1'

      VH = (rgb & 0xFF00) >> 8; // High Byte
      VL = rgb & 0x00FF;        // Low Byte

      //RGB565 to RGB555 conversion... 555 is default for uncompressed BMP
      //this conversion is from ...topic=177361.0 and has not been verified
      VL = (VH << 7) | ((VL & 0xC0) >> 1) | (VL & 0x1f);
      VH = VH >> 1;

      //Write image data to file, low byte first
      outFile.write(VL);
      outFile.write(VH);
    }
  }
  outFile.close();  //Close the file
  Serial.println("done");
  UpdateScreenHelper = NullFunction;
}




