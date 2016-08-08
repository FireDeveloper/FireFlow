#define Graph_BG  0xD69A
#define Graph_X 30
#define Graph_Y 49
#define Graph_Width 402
#define Graph_Heigh 202
//char 6x8
//480 x 320

void TFT_Print_Reflow_Btns() {
  //Boarder
  tft.fillRoundRect(480 - 4 - 120, 4, 120, 40, 10, GREEN);
  tft.setTextSize(3);
  //Text
  tft.setTextColor(BLACK);
  tft.setCursor(480 - 4 - 120 + 15,  20 + 4 - 12);
  tft.print("Start");
}

void TFT_Print_Stats() {
  tft.fillRect(0, 270, 480, 60, WHITE);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(30,  275);
  tft.print("State");
  tft.setCursor(36 + 120,  275);
  tft.print("Time");
  tft.setCursor(30 + 240,  275);
  tft.print("Temp");
  tft.setCursor(36 + 360,  275);
  tft.print("Point");

}

void TFT_Print_Grid() {
  tft.fillRect(Graph_X, Graph_Y, Graph_Width, Graph_Heigh, Graph_BG); //Graph bg
  //Graph Boarders
  tft.drawFastHLine(Graph_X - 1,  Graph_Heigh + Graph_Y - 1,  Graph_Width + 1,  WHITE);
  tft.drawFastHLine(Graph_X - 1,  Graph_Heigh + Graph_Y,  Graph_Width + 1,  WHITE);
  tft.drawFastVLine(Graph_X - 2,  Graph_Y,  Graph_Heigh + 1,  WHITE);
  tft.drawFastVLine(Graph_X - 1,  Graph_Y,  Graph_Heigh + 1,  WHITE);

  tft.setTextSize(1);
  tft.setTextColor(WHITE, BLACK);

  for (uint8_t i = 20; i > 0; i--) { //Fast code time line
    tft.drawFastVLine(Graph_X + i * 20,  Graph_Heigh + Graph_Y + 1,  3,  WHITE);
    tft.drawFastVLine(Graph_X + i * 20 - 1,  Graph_Heigh + Graph_Y + 1,  3,  WHITE);
    tft.drawFastVLine(Graph_X + i * 20 - 2,  Graph_Heigh + Graph_Y + 1,  3,  WHITE);

    //Grid
    tft.drawFastVLine(Graph_X + i * 20 - 1,  Graph_Y + 2 ,  Graph_Heigh - 3,  BLACK);

    //Text
    if (i < 5)
      tft.setCursor(Graph_X + i * 20 - 7,  Graph_Heigh + Graph_Y + 5);
    else
      tft.setCursor(Graph_X + i * 20 - 10,  Graph_Heigh + Graph_Y + 5);
    tft.print(i * 10 * 2);
  }

  for (uint8_t i = 10; i > 0; i--) { //Fast code Temp line
    tft.drawFastHLine(Graph_X - 5,   Graph_Heigh + Graph_Y - i * 20,  3,  WHITE);
    tft.drawFastHLine(Graph_X - 5,   Graph_Heigh + Graph_Y - i * 20 - 1,  3,  WHITE);
    tft.drawFastHLine(Graph_X - 5,   Graph_Heigh + Graph_Y - i * 20 + 1,  3,  WHITE);

    //Grid
    tft.drawFastHLine(Graph_X ,   Graph_Heigh + Graph_Y - i * 20,  Graph_Width - 2,  BLACK);

    //Text
    if (i < 3)
      tft.setCursor(Graph_X - 19,  Graph_Heigh + Graph_Y - i * 20 - 3);
    else
      tft.setCursor(Graph_X - 25,  Graph_Heigh + Graph_Y - i * 20 - 3);
    tft.print(i * 10 * 4);

    //0 point
    tft.setCursor(Graph_X - 8,  Graph_Heigh + Graph_Y + 4);
    tft.print("0");

    //Line Explanation
    tft.setCursor(Graph_X + Graph_Width + 5,  Graph_Heigh + Graph_Y - 4);
    tft.print("Time(s)");
    tft.setCursor(Graph_X - 30,   Graph_Y - 12);
    tft.print("Temp(C)");
  }
}

void TFT_Print_Graph() {
  for (uint16_t i = 0; i < sizeof(GraphData) / 2; i++) {
    tft.drawPixel(Graph_X + i, Graph_Y + Graph_Heigh - 2 - GraphData[i], RED);
    //bigger line
    tft.drawPixel(Graph_X + i, Graph_Y + Graph_Heigh - 2 - GraphData[i] - 1, RED);
    tft.drawPixel(Graph_X + i + 1, Graph_Y + Graph_Heigh - 2 - GraphData[i], RED);
    tft.drawPixel(Graph_X + i + 1, Graph_Y + Graph_Heigh - 2 - GraphData[i] - 1, RED);
  }


}

