void PrintMainScreen() {
  TouchListener = MainScreenTouchListener;
  tft.fillScreen(BLACK);
  bmpDraw(F("fireflow/res/Oven.bmp"), 60, 100);
  bmpDraw(F("fireflow/res/Graph.bmp"), 180, 20);
  bmpDraw(F("fireflow/res/Settings.bmp"), 300, 100);
  bmpDraw(F("fireflow/res/info.bmp"), 180, 180);
}

void MainScreenTouchListener() {
  if (tp.x > 179 && tp.x < 300 && tp.y > 19 && tp.y < 140) {
    TFT_Print_Reflow_Screen();
  } else if (tp.x > 59 && tp.x < 180 && tp.y > 99 && tp.y < 220) {
    TFT_Print_Oven_Screen();
  } else if (tp.x > 299 && tp.x < 420 && tp.y > 99 && tp.y < 220) {
    //Settings pressed
  } else if (tp.x > 179 && tp.x < 300 && tp.y > 179 && tp.y < 300) {
    //Info button pressed
  }
}

