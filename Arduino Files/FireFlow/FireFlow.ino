
//#include <TimerOne.h>

#include <MCUFRIEND_kbv.h>
#include <max6675.h>
#include <TimerThree.h>
#include <SPI.h>
#include <SD.h>
#include "Adafruit_GFX.h"// Hardware-specific library
#include "FireFlow.h"

#include <TouchScreen.h>         //Adafruit Library

Sd2Card card;
SdVolume volume;
SdFile root;

MAX6675 thermocouple(THERMOCOUPLE_CLK, THERMOCOUPLE_CS, THERMOCOUPLE_DO);

MCUFRIEND_kbv tft;

void (*TouchListener)(); //TouchScreen Listener
void (*ScreenPrinting)(); //Screen Printing Helper
void (*UpdateScreenHelper)();

TouchScreen myTouch(XP, YP, XM, YM, 300);
TSPoint tp;

int32_t Cal_Left_X, Cal_Right_X, Cal_Top_Y, Cal_Bot_Y;

bool Temp_Celsius = true;

struct SeekBar {
  uint16_t x;
  uint16_t y;
  uint16_t Width;
  uint16_t Height;
  uint8_t Padding;
  int Maximum;
  int Minimum;
  uint8_t Progress;
};
SeekBar skBar1 = {0, 0, 480, 100, 13, 100, 0, 50};


void setup(void) {
  Serial.begin(9600);
  tft.begin(tft.readID());
  tft.setRotation(3);

  pinMode(20, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(20), ExportImageInterrupt, FALLING );

  tft.invertDisplay(true);
  tft.fillScreen(BLACK);

  TouchListener = TouchBootListener;
  UpdateScreenHelper = NullFunction;

  BootImage(); //Start Boot Proccess
}

uint16_t GraphData[400] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void loop() {
  if (ISPRESSED()) {
    tp.x = map(tp.x, Cal_Left_X, Cal_Right_X, 0, 480);
    tp.y = map(tp.y, Cal_Top_Y, Cal_Bot_Y, 0, 320);
    TouchListener();
  }
  UpdateScreenHelper(); //Updates Screen which caused from interrupts
}

void NullFunction() {}


/*
  //  PrintKbrd();
  while (true) {
  }
  PrintBmp();
  DrawSeekBar(skBar1, CYAN, BLACK);
  delay(2000);
  SeekBar_SetProgress(skBar1, 25,  CYAN,  CYAN);
  skBar1.Progress = 25;
  delay(2000);
  SeekBar_SetProgress(skBar1, 75,  CYAN,  CYAN);

  TestSeekBar();

  }
*/






/*
  DebugTemp();
  // put your main code here, to run repeatedly:
  TFT_Print_Grid();
  TFT_Print_Reflow_Btns();
  TFT_Print_Stats();
  TFT_Print_Graph();
  while (true) {
  }
  }*/

void DebugTemp() {
  float temp = 30;
  for (int i = 0; i < 91; i++) {
    temp += 0.7;
    GraphData[i] = temp;
  }
  for (int i = 91; i < 210; i++) {
    temp += 0.28;
    GraphData[i] = temp;
  }
  for (int i = 211; i < 360; i++) {
    temp += 0.4;
    GraphData[i] = temp;
  }
  for (int i = 360; i < 400; i++) {
    temp += -0.52;
    GraphData[i] = temp;
  }
}


