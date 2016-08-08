#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>         //Adafruit Library

#include <SPI.h>
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;


MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define GRAY   0x8410
#define DARK_GRAY   0x4208
#define LIGHT_GRAY   0xBDF7


uint16_t g_identifier;

void (*TouchListener)(uint16_t x, uint16_t y); //TouchScreen Listener

#define YP A1   //[A1], A3 for ILI9320, A2 for ST7789V 
#define YM 7    //[ 7], 9             , 7
#define XM A2   //[A2], A2 for ILI9320, A1 for ST7789V
#define XP 6    //[ 6], 8             , 6
TouchScreen myTouch(XP, YP, XM, YM, 300);
TSPoint tp;

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

struct Calibration {
  uint16_t Left, Right, Top, Bottom;
  bool FirstTime, AutoStart;
};

void setup(void) {
  Serial.begin(9600);
  uint32_t when = millis();
  g_identifier = tft.readID();
  Serial.print("ID = 0x");
  Serial.println(g_identifier, HEX);
  if (g_identifier == 0x00D3 || g_identifier == 0xD3D3) g_identifier = 0x9481; // write-only shield
  if (g_identifier == 0xFFFF) g_identifier = 0x9341; // serial
  tft.begin(g_identifier);
  tft.setRotation(3);

  tft.invertDisplay(true);
  tft.fillScreen(BLACK);

  TouchListener = TouchBootListener;
}

uint16_t GraphData[400] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void loop() {
  TouchScreenCalibrate();
  while (true) {}
  BootImage(); //Boot Processing

  PrintKbrd();
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


