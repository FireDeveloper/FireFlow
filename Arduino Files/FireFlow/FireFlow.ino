#include <MAX31855.h>

#include <TimerOne.h>
#include <TimerThree.h>

#include <MemoryFree.h>

#include "Nextion.h"
#include "config.c"
#include <RtcDS3231.h>
#include <Adafruit_MAX31855.h>
#include <SPI.h>
#include <SD.h>
#include <PID_v1.h>
#include "Reflow_Data.h"

//Declare a button object [page id:0,component id:1, component name: "b0"].
NexDSButton Oven_Start_Stop = NexDSButton(Oven_Screen_ID, 19, "bt0");
NexButton Oven_Stop = NexButton(Oven_Screen_ID, 4, "b0");
NexButton Oven_Back = NexButton(Oven_Screen_ID, 2, "Back");
NexTimer Oven_Timer = NexTimer(Oven_Screen_ID, 14, "Timer");
NexTimer Oven_Update_Timer = NexTimer(Oven_Screen_ID, 21, "Timer2");
NexPage Oven_Page = NexPage(Oven_Screen_ID, 00, " ");

NexButton PID_Set_P = NexButton(7, 22, "PID_Set_P");
NexButton PID_Set_I = NexButton(7, 23, "PID_Set_I");
NexButton PID_Set_D = NexButton(7, 24, "PID_Set_D");

NexDSButton Units = NexDSButton(4, 5, "Unit_Button");

NexButton Load_PB = NexButton(Reflow_Profile, 1, "PB Profile");
NexButton Load_PB_Free = NexButton(Reflow_Profile, 2, "PBF Profile");
//NexButton Load_Custom = NexButton(Reflow_Profile, 3, "Load Profile");


NexDSButton Output_PWM_1 = NexDSButton(10, 6, "bp1");
NexDSButton Output_PWM_2 = NexDSButton(10, 7, "bp2");
NexDSButton Output_PWM_3 = NexDSButton(10, 8, "bp3");
NexDSButton Output_1 = NexDSButton(10, 9, "b1");
NexDSButton Output_2 = NexDSButton(10, 10, "b2");
NexDSButton Output_3 = NexDSButton(10, 11, "b3");
NexDSButton Output_4 = NexDSButton(10, 12, "b4");
NexDSButton Output_Off = NexDSButton(10, 1, "b0");
NexDSButton Output_Sound = NexDSButton(9, 6, "b7");

NexButton Load_Profile_0 = NexButton(File_List_Screen_ID, 2, "Load_0");
NexButton Load_Profile_1 = NexButton(File_List_Screen_ID, 3, "Load_1");
NexButton Load_Profile_2 = NexButton(File_List_Screen_ID, 4, "Load_2");
NexButton Load_Profile_3 = NexButton(File_List_Screen_ID, 5, "Load_3");
NexButton Delete_Profile_0 = NexButton(File_List_Screen_ID, 10, "Del_0");
NexButton Delete_Profile_1 = NexButton(File_List_Screen_ID, 11, "Del_1");
NexButton Delete_Profile_2 = NexButton(File_List_Screen_ID, 12, "Del_2");
NexButton Delete_Profile_3 = NexButton(File_List_Screen_ID, 13, "Del_3");
NexButton Profile_Up = NexButton(File_List_Screen_ID, 14, "Up");
NexButton Profile_Down = NexButton(File_List_Screen_ID, 15, "Down");
NexPage File_List_Page = NexPage(File_List_Screen_ID, 00, "File_list");

//Preview Graph
NexPage Preview_Graph_Page = NexPage(Preview_Graph_ID, 00, "Preview_Graph");

//Reflow
NexPage Reflow_Graph_Page = NexPage(Reflow_Graph_ID, 00, "Reflow_Graph");
NexDSButton Reflow_Start = NexDSButton(Reflow_Graph_ID, 29, "Reflow_Start");


//Info Pages
NexPage SDCard_Page = NexPage(18, 00, " ");

NexTouch *nex_listen_list[] = {&Oven_Start_Stop,
                               &Oven_Stop,
                               &Oven_Back,
                               &Oven_Timer,
                               &Oven_Update_Timer,
                               &Oven_Page,
                               &SDCard_Page,
                               &PID_Set_P,
                               &PID_Set_I,
                               &PID_Set_D,
                               &Units,
                               &Load_PB,
                               &Load_PB_Free,
                               &Output_PWM_1,
                               &Output_PWM_2,
                               &Output_PWM_3,
                               &Output_1,
                               &Output_2,
                               &Output_3,
                               &Output_4,
                               &Output_Off,
                               &Output_Sound,
                               &Load_Profile_0,
                               &Load_Profile_1,
                               &Load_Profile_2,
                               &Load_Profile_3,
                               &Delete_Profile_0,
                               &Delete_Profile_1,
                               &Delete_Profile_2,
                               &Delete_Profile_3,
                               &Profile_Up,
                               &Profile_Down,
                               &File_List_Page,
                               &Preview_Graph_Page,
                               &Reflow_Graph_Page,
                               &Reflow_Start,
                               NULL
                              };




struct Global_Settings {
  bool Celsius = true;
  float PID_P = 0;
  float PID_I = 0;
  float PID_D = 0;
  byte R_Top = Out_Off;
  byte R_Bot = Out_Off;
  byte R_Boost = Out_Off;
  byte Fan = Out_Off;
  byte Led_Green = Out_Off;
  byte Led_Orange = Out_Off;
  byte Led_Red = Out_Off;
  bool Sound = true;
  uint16_t Window_Size = 1000;
  double Temperature = 0;
  bool Oven_PID_Mode = false;
  bool Flash_Red = false;
  bool Flash_Orange = false;
  bool Flash_Green = false;
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

String Profile_Path = "";
uint16_t ProfilePosition = 0;
String Profile_1_Path = "";
String Profile_2_Path = "";
String Profile_3_Path = "";
String Profile_4_Path = "";


//Init Variables
//Init Thermocouples
Adafruit_MAX31855 LeftTC(MAXCS_Left);
Adafruit_MAX31855 RightTC(MAXCS_Right);

//Reflow
bool Running = false;
bool Preheating = false;
double PID_Setpoint, PID_Input, PID_Output;
PID myPID(&PID_Input, &PID_Output, &PID_Setpoint, 0, 0, 0, DIRECT);

//Temperature Reading
MAX31855 MAX31855_1(TC_SO, TC1_CS, TC_CLK);
MAX31855 MAX31855_2(TC_SO, TC2_CS, TC_CLK);

int Temperature_MO_Counter = 0;
double Temp_Matrix[] = {0, 0, 0, 0};

//Oven
bool Oven_Running = false;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(43, OUTPUT);
  Serial1.begin(9600);
  Timer3.initialize(250000);
  Timer3.attachInterrupt(MaxInterrupt);

  //  Serial1.println("================");
  nexInit();
  Oven_Start_Stop.attachPop(Oven_Start_Stop_Listener, &Oven_Start_Stop);
  Oven_Back.attachPop(Oven_Back_Listener, &Oven_Back);
  Oven_Stop.attachPop(Oven_Stop_Listener, &Oven_Stop);
  Oven_Timer.attachTimer(Oven_Timer_Listener, &Oven_Timer);
  Oven_Update_Timer.attachTimer(Oven_Page_Listener, &Oven_Update_Timer);
  Oven_Page.attachPop(Oven_Page_Listener, &Oven_Page);

  PID_Set_P.attachPop(getPID_P_Value, &PID_Set_P);
  PID_Set_I.attachPop(getPID_I_Value, &PID_Set_I);
  PID_Set_D.attachPop(getPID_D_Value, &PID_Set_D);
  Units.attachPop(Units_Listener, &Units);

  //Reflow Profile
  Load_PB.attachPop(Load_PB_Listener, &Load_PB);
  Load_PB_Free.attachPop(Load_PB_Free_Listener, &Load_PB_Free);

  //Set Outputs
  Output_PWM_1.attachPop(Output_PWM_1_Listener, &Output_PWM_1);
  Output_PWM_2.attachPop(Output_PWM_2_Listener, &Output_PWM_2);
  Output_PWM_3.attachPop(Output_PWM_3_Listener, &Output_PWM_3);
  Output_1.attachPop(Output_1_Listener, &Output_1);
  Output_2.attachPop(Output_2_Listener, &Output_2);
  Output_3.attachPop(Output_3_Listener, &Output_3);
  Output_4.attachPop(Output_4_Listener, &Output_4);
  Output_Off.attachPop(Output_Off_Listener, &Output_Off);
  Output_Sound.attachPop(Output_Sound_Listener, &Output_Sound);
  //Info Pages
  SDCard_Page.attachPop(Print_SD_Card_Info, &SDCard_Page);
  //Load Profile
  Load_Profile_0.attachPop(Load_Profile_0_Listener, &Load_Profile_0);
  Load_Profile_1.attachPop(Load_Profile_1_Listener, &Load_Profile_1);
  Load_Profile_2.attachPop(Load_Profile_2_Listener, &Load_Profile_2);
  Load_Profile_3.attachPop(Load_Profile_3_Listener, &Load_Profile_3);
  Delete_Profile_0.attachPop(Delete_Profile_0_Listener, &Delete_Profile_0);
  Delete_Profile_1.attachPop(Delete_Profile_1_Listener, &Delete_Profile_1);
  Delete_Profile_2.attachPop(Delete_Profile_2_Listener, &Delete_Profile_2);
  Delete_Profile_3.attachPop(Delete_Profile_3_Listener, &Delete_Profile_3);
  Profile_Up.attachPop(Profile_Up_Listener, &Profile_Up);
  Profile_Down.attachPop(Profile_Down_Listener, &Profile_Down);
  File_List_Page.attachPop(File_List_Page_Listener, &File_List_Page);
  //Preview Profile
  Preview_Graph_Page.attachPop(Preview_Graph_Page_Listener, &Preview_Graph_Page);
  //Reflow
  Reflow_Graph_Page.attachPop(Reflow_Graph_Page_Listener, &Reflow_Graph_Page);
  Reflow_Start.attachPop(Reflow_Start_Listener, &Reflow_Start);


  //  inputString.reserve(200);
  //  inputString = "";
  BootImage();
}

void loop() {
  if (Running || (Oven_Running && Settings.Oven_PID_Mode))
    myPID.Compute();

  nexLoop(nex_listen_list);
  //  SCADA_Listener();
}

void MaxInterrupt() {
  Temp_Matrix[Temperature_MO_Counter] = ReadTemperature();
  Temperature_MO_Counter++;
  if ( Temperature_MO_Counter == 2) {
    FlashLedOn();
  } else if (Temperature_MO_Counter == 4) {
    Temperature_MO_Counter = 0;
    Settings.Temperature = (Temp_Matrix[0] + Temp_Matrix[1] + Temp_Matrix[2] + Temp_Matrix[3]) / 4;
    if (!Settings.Oven_PID_Mode)
      SetOnOffTemperature();
    FlashLedOff();
  }
}


double ReadTemperature() {
  if (Settings.Celsius)
    return MAX31855_1.readThermocouple(CELSIUS);
  else
    return MAX31855_1.readThermocouple(FAHRENHEIT);
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

