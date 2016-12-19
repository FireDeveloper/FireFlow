//Variables
uint16_t Oven_Set_Point = 150;

//===============================================

void Oven_Page_Listener(void *ptr) {
  uint16_t temp = ReadTemperature();
  Oven_Set_Thermometer_Value(temp);
  Oven_Set_Text_Value(temp);
  Timer3.start();
}

void Oven_Start_Stop_Listener(void *ptr) {
  uint32_t On_Off = 0;
  while (!Oven_Start_Stop.getValue(&On_Off)) {}

  if (On_Off == 1) { //Start Oven
    Serial1.println("Start");
    uint32_t Set_Temperature = 0;
    while (!NexNumber(Oven_Screen_ID, 9, "SetPoint").getValue(&Set_Temperature)) {}
    PID_Setpoint = Set_Temperature;
    Serial1.print("Set Point:");
    Serial1.println(Set_Temperature, DEC);
    if (Settings.Oven_PID_Mode)
      myPID.SetTunings(Settings.PID_P, Settings.PID_I, Settings.PID_D);

    Oven_Running = true;
    FlashLedOrange(true);
  } else { //Close Oven
    Serial1.println("Stop");
    noInterrupts(); //Avoid Bugs
    Timer3.stop();
    FlashLedOrange(false);
    interrupts();
    delay(0);
    Output_CloseAll();
  }

  // See Functions -----------------------------------------------------------------
  //  char buff[3];
  //  itoa(number, buff, 10);
  // ---------------------------------------------------------------- -


  //  NexText txt = NexText(2, 6, "t0");
  //  txt.setText(buff);
}

void Oven_Back_Listener() {
  Timer3.stop();
  Serial1.println("Back");
}

void Oven_Stop_Listener(void *ptr) {

}

void Oven_Timer_Listener(void *ptr) {
  Oven_Display_Current_Temperature((uint16_t)Settings.Temperature);

  digitalWrite(13, HIGH);
  if (!Oven_PID_Control) { //Simple Control
    if (Settings.Temperature < Oven_Set_Point)
      digitalWrite(13, HIGH); //Enable Resistors
    else
      digitalWrite(13, LOW); //Dissable Resistors
  }
}

void Oven_Display_Current_Temperature(uint16_t Temperature) {
  Oven_Set_Thermometer_Value(Temperature);
  Oven_Set_Text_Value(Temperature);
}

void Oven_Set_Thermometer_Value(uint16_t Temp) {
  int t = map(Temp, Oven_Min_Temp, Oven_Max_Temp, 0, 100); //Map Value
  t = ( t > 100 ) ? 100 : t; //Check if value is >100%
  NexProgressBar(Oven_Screen_ID, 3, "thermometer").setValue(t); //Send Value
}

void Oven_Set_Text_Value(uint16_t Temp) {
  // See Functions -----------------------------------------------------------------
  char buff[3];
  itoa(Temp, buff, 10);
  //---------------------------------------------------------------- -
  NexText(Oven_Screen_ID, 7, "t1").setText(buff);
}

void SetOnOffTemperature() {
  if (Settings.Temperature > PID_Setpoint + 2)
    Output_Close();
  else if (Settings.Temperature < PID_Setpoint - 2)
    Output_Heat();
}


