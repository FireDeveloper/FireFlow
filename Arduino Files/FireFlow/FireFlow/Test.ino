
#define KeyboardColor_Bg 0x0000
#define KeyboardColor_Btn 0x4208
#define KeyboardColor_Fore 0xFFFF

void PrintKbrdButton(uint16_t x, uint16_t y, uint8_t w, uint8_t h, char chr) {
  tft.fillRect(x, y, 3, h , KeyboardColor_Bg); //3 black lines before box
  tft.fillRect(x + w + 3, y, 3, h , KeyboardColor_Bg); //3 black lines after box

  tft.fillRect(x, y - 2, w + 6, 2 , KeyboardColor_Bg); //2 black lines upper box
  tft.fillRect(x, y + h, w + 6, 2 , KeyboardColor_Bg); //2 black lines down box
  tft.drawFastHLine(x + 3, y + h - 1, w, LIGHT_GRAY);

  tft.drawFastVLine(x + 3, y , h - 1, LIGHT_GRAY);
  tft.drawRect(x + 4, y, w - 1, h - 1 , GRAY);

  tft.fillRect(x + 3 + 2, y + 1, w - 3, h - 3, KeyboardColor_Btn); //Button box

  tft.setTextColor(BLACK); //Temp
  tft.setTextSize(2); //Temp
  tft.setCursor(x + w / 2 + 3 - 6,  y + 10);
  tft.print(chr);
}

void PrintKbrd() {
  extern const char KeyboardVal[];
  for (byte i = 0; i < 10; i++) {
    PrintKbrdButton( i * 48, 120,  42, 36 , ' ' + i + 16);
    PrintKbrdButton( i * 48, 160,  42, 36 ,  KeyboardVal[i]);
  }
  for (byte i = 0; i < 9; i++)
    PrintKbrdButton( i * 48 + 24, 200,  42, 36 , ' ' + i + 16);
  for (byte i = 0; i < 7; i++)
    PrintKbrdButton( i * 48 + 72, 240,  42, 36 , ' ' + i + 16);
}













void PrintBmp() {
  tft.fillRect(0, 0, 24, 24, RED);
  extern const uint8_t ic_save_48px[];
  tft.setAddrWindow(0, 0, 24 - 1, 24 - 1);
  tft.pushColors(ic_save_48px, 576 , 1);
}

void TestSeekBar() {
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  //uint16_t x = 15;
  uint16_t y = 30;
  for (uint16_t x = 15; x <= 465; x += 10) {
    tft.fillCircle(x, y, 12, RED);
    tft.fillTriangle(x,  y + 17,  x - 10,  y + 7,  x + 10,  y + 7,  RED);

    tft.setCursor(x - 8,  y - 4);
    tft.print("000");
    //  delay(100);

    tft.fillCircle(x, 30, 12, BLACK);
    tft.fillTriangle(x,  y + 17,  x - 10,  y + 7,  x + 10,  y + 7,  BLACK);
  }
  for (uint16_t x = 465; x >= 15; x -= 10) {
    tft.fillCircle(x, 30, 12, RED);
    tft.fillTriangle(x,  y + 17,  x - 10,  y + 7,  x + 10,  y + 7,  RED);
    tft.setCursor(x - 8,  26);
    tft.print("000");
    //   delay(100);
    tft.fillCircle(x, 30, 12, BLACK);
    tft.fillTriangle(x,  y + 17,  x - 10,  y + 7,  x + 10,  y + 7,  BLACK);
  }
}

/*struct SeekBar {
  uint16_t x;
  uint16_t y;
  uint16_t Width;
  uint16_t Height;
  uint8_t Padding;
  int Maximum;
  int Minimum;
  uint8_t Progress;
  };*/



void DrawSeekBar(SeekBar bar, uint16_t color, uint16_t txt_color) {
  tft.drawFastHLine(bar.x + bar.Padding, bar.y + 33, bar.Width - (bar.Padding * 2) + 1, GRAY);
  tft.drawFastHLine(bar.x + bar.Padding, bar.y + 34, bar.Width - (bar.Padding * 2) + 1, GRAY);
  uint16_t prg = round( map(bar.Progress, 0, 100 , 0, bar.Width - bar.Padding * 2));
  tft.drawFastHLine(bar.x + bar.Padding + 1, bar.y + 32, prg - 1 , color);
  tft.drawFastHLine(bar.x + bar.Padding, bar.y + 33, prg + 1, color);
  tft.drawFastHLine(bar.x + bar.Padding, bar.y + 34, prg + 1, color);
  tft.drawFastHLine(bar.x + bar.Padding + 1, bar.y + 35, prg - 1 , color);

  tft.fillCircle(prg + bar.Padding, bar.y + 13, 12, color);
  tft.fillTriangle(prg + bar.Padding,  bar.y + 17 + 13,  prg + bar.Padding - 10,  bar.y + 7 + 13,  prg + bar.Padding + 10,  bar.y + 7 + 13,  color);

  tft.setTextColor(txt_color);
  tft.setTextSize(1);

  if (bar.Progress < 10)
    tft.setCursor(prg + bar.Padding - 2,  bar.y + 13 - 4);
  else if (bar.Progress < 100)
    tft.setCursor(prg + bar.Padding - 5,  bar.y + 13 - 4);
  else
    tft.setCursor(prg  + bar.Padding - 8,  bar.y + 13 - 4);
  tft.print(bar.Progress);

}

void SeekBar_SetProgress(SeekBar bar, uint8_t Progress, uint16_t color, uint16_t txt_color) {


  uint16_t Old_prg = round( map(bar.Progress, 0, 100 , 0, bar.Width - bar.Padding * 2));
  uint16_t New_prg = round( map(Progress, 0, 100 , 0, bar.Width - bar.Padding * 2));
  uint16_t temp_color = (Old_prg > New_prg ) ? GRAY : color ;

  //  tft.fillCircle(prg + bar.Padding, bar.y + 13, 12, BLACK);
  //  tft.fillTriangle(prg + bar.Padding,  bar.y + 17 + 13,  prg + bar.Padding - 10,  bar.y + 7 + 13,  prg + bar.Padding + 10,  bar.y + 7 + 13,  BLACK);

  if (Old_prg > New_prg) { //Erase bar
    tft.drawFastHLine(Old_prg + bar.Padding + 1, bar.y + 32, New_prg - Old_prg - 2, BLACK);
    tft.drawFastHLine(Old_prg + bar.Padding + 1, bar.y + 35, New_prg - Old_prg - 2, BLACK);
  }
  tft.drawFastHLine(Old_prg + bar.Padding + 1, bar.y + 33, New_prg - Old_prg - 1, temp_color);
  tft.drawFastHLine(Old_prg + bar.Padding + 1, bar.y + 34, New_prg - Old_prg - 1, temp_color);

  // return Progress;
}

// while (true) {
// }
