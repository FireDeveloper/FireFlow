void TFT_Print_Oven_Screen() {
  TouchListener =  OvenTouchListener; //Change Touch Listener
  tft.fillScreen(BLACK);
  TFT_Draw_Back_Button();
  //  TFT_Draw_Holo_Switch_On(190, 40); //Will change it to off , just for temp testing
  TFT_Draw_Holo_Switch_Off(190, 40);

  tft.drawCircle(119, 159, 79, WHITE); //Left
  tft.fillCircle( 119,  159,  78,  DARK_GRAY);

  tft.drawCircle(360, 159, 79, WHITE); //Right
  tft.fillCircle( 360,  159,  78,  DARK_GRAY);

  //Print Clock
  tft.setTextSize(1);

  tft.setCursor(388,  97);
  tft.print(F("05"));
  tft.setCursor(413,  121);
  tft.print(F("10"));
  tft.setCursor(420,  156);
  tft.print(F("15"));
  tft.setCursor(413,  189);
  tft.print(F("20"));
  tft.setCursor(388,  214);
  tft.print(F("25"));
  tft.setCursor(355,  223);
  tft.print(F("30"));
  tft.setCursor(321,  214);
  tft.print(F("35"));
  tft.setCursor(296,  189);
  tft.print(F("40"));
  tft.setCursor(289,  156);
  tft.print(F("45"));
  tft.setCursor(296,  121);
  tft.print(F("50"));
  tft.setCursor(321,  97);
  tft.print(F("55"));
  tft.setCursor(355,  88);
  tft.print(F("60"));


}

bool Set_Oven_On = false;

void OvenTouchListener() {
  if (TFT_Back_Button_Pressed())
    PrintMainScreen();
  else if (tp.x > 190 && tp.x < 290 && tp.y > 40 && tp.y < 80) {
    Set_Oven_On = !Set_Oven_On;
    if (Set_Oven_On)
      TFT_Draw_Holo_Switch_On(190, 40);
    else
      TFT_Draw_Holo_Switch_Off(190, 40);
  }

}

