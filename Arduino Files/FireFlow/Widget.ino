
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

void TFT_Draw_Analog_Segment(uint16_t center_x, uint16_t center_y, int theta, uint16_t color) {
  int end_x =  OVEN_TEMP_R * cos(theta * DEGREES_TO_RADIANS);
  int end_y = OVEN_TEMP_R * sin(theta * DEGREES_TO_RADIANS);

  //Romvos
  int P_1_x = 25 * cos((theta - 10) * DEGREES_TO_RADIANS);
  int P_1_y = 25 * sin((theta - 10) * DEGREES_TO_RADIANS);

  int P_2_x = 25 * cos((theta + 10) * DEGREES_TO_RADIANS);
  int P_2_y = 25 * sin((theta + 10) * DEGREES_TO_RADIANS);

  tft.fillTriangle(center_x, center_y, center_x + end_x, center_y - end_y, center_x + P_1_x, center_y - P_1_y, color);

  tft.fillTriangle(center_x, center_y, center_x + end_x, center_y - end_y, center_x + P_2_x, center_y - P_2_y, color);
}

