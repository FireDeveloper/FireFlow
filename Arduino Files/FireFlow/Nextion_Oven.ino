//Functions
void Oven_Display_Current_Temperature(uint16_t Temp);
void Oven_Set_Thermometer_Value(uint16_t Temp);
void Oven_Set_Text_Value(uint16_t Temp);

//Variables
uint16_t Oven_Set_Point = 150;

//===============================================

void Oven_Page_Listener(void *ptr) {
  uint16_t Temperature = ReadTemperature();
  Oven_Set_Thermometer_Value(Temperature);
  Oven_Set_Text_Value(Temperature);
}

void Oven_Start_Stop_Listener(void *ptr) {
  NexNumber SetP = NexNumber(2, 9, "SetPoint");

  uint32_t number = 1;
  while (!SetP.getValue(&number)) {
  }

  char buff[3];
  itoa(number, buff, 10);

  NexText txt = NexText(2, 6, "t0");
  txt.setText(buff);
}

void Oven_Stop_Listener(void *ptr) {
  digitalWrite(13, HIGH);
}

void Oven_Timer_Listener(void *ptr) {
  uint16_t Temp = ReadTemperature();
  Oven_Display_Current_Temperature(Temp);

  digitalWrite(13, HIGH);
  if (!Oven_PID_Control) { //Simple Control
    if (Temp < Oven_Set_Point)
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
  NexProgressBar(2, 3, "thermometer").setValue(t); //Send Value
}

void Oven_Set_Text_Value(uint16_t Temp) {
  char buff[3];
  itoa(Temp, buff, 10);
  NexText(2, 7, "t1").setText(buff);
}


