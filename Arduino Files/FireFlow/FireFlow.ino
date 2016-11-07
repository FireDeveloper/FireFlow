#include "Nextion.h"
#include "config.c"
#include <RtcDS3231.h>
#include <Adafruit_MAX31855.h>
#include <SPI.h>
#include <SD.h>

//Declare a button object [page id:0,component id:1, component name: "b0"].
NexButton Oven_Start_Stop = NexButton(2, 19, "bt0");
NexButton Oven_Stop = NexButton(2, 4, "b0");
NexTimer Oven_Timer = NexTimer(2, 14, "Timer");
NexTimer Oven_Update_Timer = NexTimer(2, 21, "Timer2");
NexPage Oven_Page = NexPage(2, 00, " ");

//Info Pages
NexPage SDCard_Page = NexPage(18, 00, " ");

NexTouch *nex_listen_list[] = {&Oven_Start_Stop,
                               &Oven_Stop,
                               &Oven_Timer,
                               &Oven_Update_Timer,
                               &Oven_Page,
                               &SDCard_Page,
                               NULL
                              };

//Preset Listeners
void Oven_Start_Stop_Listener(void *ptr);
void Oven_Stop_Listener(void *ptr);
void Oven_Timer_Listener(void *ptr);
void Oven_Page_Listener(void *ptr);
void Print_SD_Card_Info(void *ptr);

//Other Functions
void BootImage();
//void SCADA_Listener();
//String getValue(String data, char separator, int index);

struct Global_Settings {
  bool Celsius = true;
} Settings;

//SD Card
Sd2Card card;
SdVolume volume;
SdFile root;
//RTC
RtcDS3231 Rtc;
//Serial
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//Init Variables
//Init Thermocouples
Adafruit_MAX31855 LeftTC(MAXCLK, MAXCS_Left, MAXDO);
Adafruit_MAX31855 RightTC(MAXCLK, MAXCS_Right, MAXDO);

void setup() {
  pinMode(13, OUTPUT);
  nexInit();
  Oven_Start_Stop.attachPop(Oven_Start_Stop_Listener, &Oven_Start_Stop);
  Oven_Stop.attachPop(Oven_Stop_Listener, &Oven_Stop);
  Oven_Timer.attachTimer(Oven_Timer_Listener, &Oven_Timer);
  Oven_Update_Timer.attachTimer(Oven_Page_Listener, &Oven_Update_Timer);
  Oven_Page.attachPop(Oven_Page_Listener, &Oven_Page);

  //Info Pages
  SDCard_Page.attachPop(Print_SD_Card_Info, &SDCard_Page);

  //  inputString.reserve(200);
  //  inputString = "";
    BootImage();
}

void loop() {
  //  SCADA_Listener();
  nexLoop(nex_listen_list);
}

double ReadTemperature() {
  if (Settings.Celsius)
    return random(20, 400);
  else
    return random(20, 400);
}

//Testing temp
int counter = 0;
/*
  void SCADA_Listener() {
  if (stringComplete) {
    if (inputString == "AT")
      Serial.println("AT OK");
    else if (inputString == "AT+STOP")
      Serial.println("OFF");
    else if (inputString.substring(0, 16) == "AT+START_PROFILE")
      Serial.println("On");
    else if (inputString == "AT+GET_DATA") {
      Serial.println(String(counter * 2) + "," + String(counter) + ",Soak"); //        Seconds,Temp,Phase
      counter++;
    } else if (inputString.substring(0, 10) == "AT+SET_MEM") {
      String xval = getValue(inputString, ',', 1);
      String yval = getValue(inputString, ',', 2);
      String temp99 = "AT OK";
      temp99 += " " + xval + " " + yval;
      Serial.println(temp99);
    } else if (inputString.substring(0, 16) == "AT+STORE_PROFILE") {
      Serial.println("AT OK");
    } else if (inputString == "AT+GET_PROFILES") {
      Serial.println("Profie 1");
      Serial.println("Profie 1");
      Serial.println("AT OK");
    }

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  }*/

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
/*
  void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    if (inChar == '\r')
      stringComplete = true;
    else
      inputString += inChar;
  }
  }*/

