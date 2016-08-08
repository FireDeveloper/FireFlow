uint32_t rx[8], ry[8]; //Reed Points

//void showpoint(void) {
//  Serial.print("\r\nx="); Serial.print(tp.x);
//  Serial.print(" y="); Serial.print(tp.y);
//}

bool ISPRESSED(void) {
  // .kbv this was too sensitive !! now touch has to be stable for 50ms
  int count = 0;
  bool state, oldstate;
  while (count < 10) { //10 * 5ms delay - 5ms last dummy delay = 45ms stable 50ms responce
    readResistiveTouch();
    state = tp.z > 20 && tp.z < 1000;
    if (state == oldstate) count++;
    else count = 0;
    oldstate = state;
    delay(5);
  }
  return oldstate;
}

void readResistiveTouch(void) {
  tp = myTouch.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH);
}

void waitForTouch() {
  while (ISPRESSED() == true) {}
  while (ISPRESSED() == false) {}
  while (ISPRESSED() == true) {}
}

void drawCrossHair(int x, int y, uint16_t Color) {
  tft.drawRect(x - 10, y - 10, 20, 20, Color);
  tft.drawFastHLine(x - 5, y, 10, Color);
  tft.drawFastVLine(x, y - 5, 10, Color);
}

void startup() {
  tft.fillScreen(WHITE);
  tft.fillRect(0, 0, 480, 32, RED);
  tft.drawFastHLine(0, 32, 480, BLACK);
  tft.setTextSize(2);
  tft.setCursor(48, 8);
  tft.setTextColor(BLACK);
  tft.print(F("FireFlow TouchScreen Calibration"));

  tft.setTextSize(2);

  tft.setCursor(24, 60);
  tft.print(F("Use a stylus or similar to touch the"));
  tft.setCursor(30, 80);
  tft.print(F("center of the highlighted crosshair"));

  tft.setCursor(36, 120);
  tft.print(F("Keep as still as possible and keep"));
  tft.setCursor(12, 140);
  tft.print(F("holding until the highlight is removed"));

  tft.setCursor(18, 180);
  tft.print(F("Repeat for all crosshairs in sequence"));

  tft.setCursor(96, 242);
  tft.print(F("Touch screen to continue"));

  waitForTouch();
  tft.fillScreen(WHITE);
  tft.setTextColor(BLACK, WHITE);
}

void calibrate(int x, int y, int i) {
  drawCrossHair(x, y, BLACK);
  readCoordinates();
  tft.setCursor(198, 118);
  tft.print(F("RELEASE"));
  drawCrossHair(x, y, 0x528A );
  rx[i] = tp.x;
  ry[i] = tp.y;
  //Print Coordinates
  tft.setCursor(192, 152);
  tft.print(F("   "));
  tft.setCursor(192, 152);
  tft.print(tp.x);

  tft.setCursor(252, 152);
  tft.print(F("   "));
  tft.setCursor(252, 152);
  tft.print(tp.y);
  while (ISPRESSED() == true) {}
}

void readCoordinates() {
  int iter = 5000;
  int failcount = 0;
  int cnt = 0;
  uint32_t tx = 0;
  uint32_t ty = 0;
  boolean OK = false;

  while (OK == false) {
    tft.setCursor(198, 118);
    tft.print(" PRESS ");
    while (ISPRESSED() == false) {}
    tft.setCursor(198, 118);
    tft.print(" HOLD! ");
    cnt = 0;
    iter = 400;
    do {
      readResistiveTouch();
      if (tp.z > 20 && tp.z < 1000) {
        tx += tp.x;
        ty += tp.y;
        cnt++;
      } else
        failcount++;
    } while ((cnt < iter) && (failcount < 10000));

    if (cnt >= iter)
      OK = true;
    else {
      tx = 0;
      ty = 0;
      cnt = 0;
    }
    if (failcount >= 10000)
      fail();
  }

  tp.x = tx / iter;
  tp.y = ty / iter;
}


void TouchScreenCalibrate() {
  startup();

  drawCrossHair(480 - 10, 10, 0x528A);
  drawCrossHair(480 / 2, 10, 0x528A);
  drawCrossHair(10, 10, 0x528A);
  drawCrossHair(480 - 10, 320 / 2, 0x528A);
  drawCrossHair(10, 320 / 2, 0x528A);
  drawCrossHair(480 - 10, 320 - 10, 0x528A);
  drawCrossHair(480 / 2, 320 - 10, 0x528A);
  drawCrossHair(10, 320 - 10, 0x528A);

  //Middle Boxes
  tft.drawRect(179,  109,  122,  34, BLACK);
  tft.drawRect(178,  108,  124,  69, BLACK);
  tft.drawRect(179,  143,  61,  34, BLACK);
  tft.drawRect(240,  143,  61,  34, BLACK);
  tft.drawRect(179,  177,  122,  34, BLACK);
  tft.drawRect(178,  177,  124,  35, BLACK);


  //Left
  calibrate(10, 10, 0);
  calibrate(10, 320 / 2, 1);
  calibrate(10, 320 - 10, 2);
  //Mid
  calibrate(480 / 2, 10, 3);
  calibrate(480 / 2, 320 - 10, 4);
  //Right
  calibrate(480 - 10, 10, 5);
  calibrate(480 - 10, 320 / 2, 6);
  calibrate(480 - 10, 320 - 10, 7);

  //  invertouch();

  int swapxy = ry[2] - ry[0];
  swapxy = (swapxy < -500 || swapxy > 500);

  int32_t clx, crx, cty, cby;

  if (swapxy != 0) { //normal
    //  Serial.println("XY Normal");
    clx = (rx[0] + rx[1] + rx[2]) / 3;
    crx = (rx[5] + rx[6] + rx[7]) / 3;
    cty = (ry[0] + ry[3] + ry[5]) / 3;
    cby = (ry[2] + ry[4] + ry[7]) / 3;
  } else { //inverted
    // Serial.println("XY Inverted");
    clx = (ry[0] + ry[1] + ry[2]) / 3;
    crx = (ry[5] + ry[6] + ry[7]) / 3;
    cty = (rx[0] + rx[3] + rx[5]) / 3;
    cby = (rx[2] + rx[4] + rx[7]) / 3;
  }

  // Cross offset fix
  float  px = float(crx - clx) / (480 - 20);
  float  py = float(cby - cty) / (320 - 20);
  clx -= px * 10;
  crx += px * 10;
  cty -= py * 10;
  cby += py * 10;


  done();

  while (true)
    if (ISPRESSED()) {
      int x = map(tp.x, clx, crx, 0, 480);
      int y = map(tp.y, cty, cby, 0, 320);
      Serial.print(x);
      Serial.print("  ");
      Serial.println(y);
      while (ISPRESSED() == true) {}
    }



}


void fail() {

}

void done() {
  tft.setCursor(216, 186);
  tft.print(F("Exit")); Exit
  while (true) {}
}

void invertouch() {
  for (byte i = 0; i < 8; i++) {
    int temp = rx[i];
    rx[i] = ry[i];
    ry[i] = temp;
  }
}

