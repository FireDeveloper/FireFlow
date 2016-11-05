#include "Nextion.h"
#include "config.c"

//Declare a button object [page id:0,component id:1, component name: "b0"].
NexButton Oven_Start_Stop = NexButton(2, 19, "bt0");
NexButton Oven_Stop = NexButton(2, 4, "b0");
NexTimer Oven_Timer = NexTimer(2, 14, "Timer");
NexTimer Oven_Update_Timer = NexTimer(2, 21, "Timer2");
NexPage Oven_Page = NexPage(2, 00, " ");

NexTouch *nex_listen_list[] = {&Oven_Start_Stop,
                               &Oven_Stop,
                               &Oven_Timer,
                               &Oven_Update_Timer,
                               &Oven_Page,
                               NULL
                              };

//Preset Listeners
void Oven_Start_Stop_Listener(void *ptr);
void Oven_Stop_Listener(void *ptr);
void Oven_Timer_Listener(void *ptr);
void Oven_Page_Listener(void *ptr);


struct Global_Settings {
  bool Celsius = true;
} Settings;


void setup() {
  pinMode(13, OUTPUT);
  nexInit();
  Oven_Start_Stop.attachPop(Oven_Start_Stop_Listener, &Oven_Start_Stop);
  Oven_Stop.attachPop(Oven_Stop_Listener, &Oven_Stop);
  Oven_Timer.attachTimer(Oven_Timer_Listener, &Oven_Timer);
  Oven_Update_Timer.attachTimer(Oven_Page_Listener, &Oven_Update_Timer);
  Oven_Page.attachPop(Oven_Page_Listener, &Oven_Page);
}

void loop() {
  nexLoop(nex_listen_list);
}

double ReadTemperature() {
  if (Settings.Celsius)
    return random(20, 400);
  else
    return random(20, 400);
}



