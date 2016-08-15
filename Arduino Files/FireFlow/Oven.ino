bool Set_Oven_On = false;

bool Oven_Time_On = true;

uint16_t Oven_Temp_Now = 200;
uint16_t Oven_Temp_Set = 200;

uint32_t Oven_Time_S_Left = 1000;
uint32_t Oven_Time_S_Set = 1000;

void TFT_Print_Oven_Screen() {
  TouchListener =  OvenTouchListener; //Change Touch Listener
  tft.fillScreen(BLACK);
  TFT_Draw_Back_Button();
  TFT_Draw_Holo_Switch_Off(190, 40);

  tft.drawCircle(119, 159, 79, WHITE); //Left
  tft.fillCircle(119, 159, 78, DARK_GRAY);

  tft.drawCircle(360, 159, 79, WHITE); //Right
  tft.fillCircle(360, 159, 78, DARK_GRAY);

  TFT_Draw_Small_Button_Clock(438, 74); //Time Settings
  TFT_Draw_Small_Button_Temp(40, 74);

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

  //Print Temp
  tft.setCursor(70,  201);
  tft.print(F("0"));
  tft.setCursor(48,  156);
  tft.print(F("50"));
  tft.setCursor(64,  110);
  tft.print(F("100"));
  tft.setCursor(111,  88);
  tft.print(F("150"));
  tft.setCursor(157,  110);
  tft.print(F("200"));
  tft.setCursor(173,  156);
  tft.print(F("250"));
  tft.setCursor(157,  201);
  tft.print(F("300"));

  tft.setTextSize(4);
  tft.setCursor(4, 245);
  tft.print(F("Set:"));
  tft.setCursor(4, 283);
  tft.print(F("Now:"));


  TFT_Oven_Print_Temp_Symbol(192, 245, 4);
  TFT_Oven_Print_Temp_Symbol(192, 283, 4);

  TFT_Oven_Print_Temp_Symbol(108, 211, 2);

  TFT_Oven_Print_Lefting_Time();
  TFT_Oven_Print_Set_Time();
  TFT_Oven_Print_Set_Temp();
  /*
    for (int i = 0; i < 301; i++) {
      TFT_Draw_Clock_Segment(119, 159, Calculate_Theta_Temp(i - 1), DARK_GRAY);
      TFT_Draw_Clock_Segment(119, 159, Calculate_Theta_Temp(i), RED);
      TFT_Oven_Draw_Temp(i);
      delay(100);
    }*/
}

TSPoint Oven_Old_Temp_B_Point;


int Calculate_Theta_Temp(int Temp) { //Farenaight must added
  if (Temp < 0)
    return 225;
  else if (Temp > 300)
    return -45;

  int r = map(Temp, 0, 300, 225, -45);
  if (r < 0)
    r += 360;

  return r;
}

void Oven_Timer_Interrupt() {
  Oven_Time_S_Left -= 1;
  UpdateScreenHelper = TFT_Oven_Print_Lefting_Time;
}

void TFT_Oven_Print_Lefting_Time() {
  tft.setTextSize(4);
  tft.setTextColor(WHITE, BLACK);
  tft.setCursor(264, 283);
  tft.print(FormatTime(Oven_Time_S_Left));

  TFT_Draw_Analog_Segment(360, 159, 450 - (numberOfSeconds(Oven_Time_S_Left) + 1) * 6, 50, DARK_GRAY); //450 = 360 + 90

  TFT_Draw_Analog_Segment(360, 159, 450 - (numberOfMinutes(Oven_Time_S_Left) + 1) * 6, 30, DARK_GRAY); //450 = 360 + 90

  TFT_Draw_Analog_Segment(360, 159, 450 - numberOfSeconds(Oven_Time_S_Left) * 6, 50, RED);

  TFT_Draw_Analog_Segment(360, 159, 450 - numberOfMinutes(Oven_Time_S_Left) * 6, 30, GREEN);

  UpdateScreenHelper = NullFunction; //Reset Intrupt Driven Screen Update
}

void TFT_Oven_Print_Set_Time() {
  tft.setTextSize(4);
  tft.setTextColor(WHITE, BLACK);
  tft.setCursor(264, 245);
  tft.print(FormatTime(Oven_Time_S_Set));
}

void TFT_Oven_Print_Set_Temp() {
  tft.setTextSize(4);
  tft.setTextColor(WHITE, BLACK);
  tft.setCursor(120, 245);
  if (Oven_Temp_Set < 100)
    tft.print(F(" "));
  if (Oven_Temp_Set < 10)
    tft.print(F(" "));

  tft.print(Oven_Temp_Set);

}

void TFT_Oven_Print_Now_Temp() {
}


void OvenTouchListener() {
  if (TFT_Back_Button_Pressed())
    PrintMainScreen();
  else if (tp.x > 190 && tp.x < 290 && tp.y > 40 && tp.y < 80) {
    Set_Oven_On = !Set_Oven_On;
    if (Set_Oven_On) {
      TFT_Draw_Holo_Switch_On(190, 40);
      if (Oven_Time_On) {
        TFT_Erase_Back_Button();
        Timer3.initialize(1000000);
        Timer3.attachInterrupt(Oven_Timer_Interrupt);
      }
    } else {
      Timer3.stop();
      TFT_Draw_Back_Button();
      TFT_Draw_Holo_Switch_Off(190, 40);
    }
  }
}

void TFT_Oven_Print_Temp_Symbol(uint16_t x, uint16_t y, uint8_t s) {
  tft.setTextSize(s);
  tft.setCursor(x, y - 2 * s);
  tft.write((byte)9);
  tft.setCursor(x + 6 * s, y);
  if (Temp_Celsius)
    tft.print('C');
  else
    tft.print('F');
}


String FormatTime(uint32_t Time) {
  String data = "";
  uint8_t temp = numberOfHours(Time);
  if (temp < 10)
    data += "0";
  data += temp;
  data += ":";
  temp = numberOfMinutes(Time);
  if (temp < 10)
    data += "0";
  data += temp;
  data += ":";
  temp = numberOfSeconds(Time);
  if (temp < 10)
    data += "0";
  data += temp;
  return data ;
}

