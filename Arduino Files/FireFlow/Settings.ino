void getPID_P_Value() {
  char buff[17] = "";
  while (NexText(8, 5, "t0").getText(buff, 15) == 0) {}
  Settings.PID_P = String(buff).toFloat();
  SaveGainsFile();
}

void getPID_I_Value() {
  char buff[17] = "";
  while (NexText(8, 6, "t1").getText(buff, 15) == 0) {}
  Settings.PID_I = String(buff).toFloat();
  SaveGainsFile();
}

void getPID_D_Value() {
  char buff[17] = "";
  while (NexText(8, 7, "t2").getText(buff, 15) == 0) {}
  Settings.PID_D = String(buff).toFloat();
  SaveGainsFile();
}

void Units_Listener() {
  uint32_t Value = 0;
  while (!NexNumber(4, 6, "Celsius").getValue(&Value)) {}
  //  Serial1.print(value);
  if (Value == 0)
    Settings.Celsius = false;
  else
    Settings.Celsius = true;
  File temp = SD.open(F("fireflow/set/config.txt"), FILE_WRITE);
  temp.seek(3);
  temp.print(Value);
  temp.close();
}

void SaveGainsFile() {
  if (SD.exists(F("fireflow/set/Gains.txt"))) //Remove old file
    SD.remove(F("fireflow/set/Gains.txt"));
  File temp = SD.open(F("fireflow/set/Gains.txt"), FILE_WRITE); //Make new file

  temp.println(Settings.PID_P);
  temp.println(Settings.PID_I);
  temp.println(Settings.PID_D);
  temp.close();
}

void Output_1_Listener() {
  uint32_t ID = 0;
  while (!NexVariable(10, 3, "Set_Output_Num.ID").getValue(&ID)) {}
  SaveOutputWithID(ID, Out_1);
}
void Output_2_Listener() {
  uint32_t ID = 0;
  while (!NexVariable(10, 3, "Set_Output_Num.ID").getValue(&ID)) {}
  SaveOutputWithID(ID, Out_2);
}
void Output_3_Listener() {
  uint32_t ID = 0;
  while (!NexVariable(10, 3, "Set_Output_Num.ID").getValue(&ID)) {}
  SaveOutputWithID(ID, Out_3);
}
void Output_4_Listener() {
  uint32_t ID = 0;
  while (!NexVariable(10, 3, "Set_Output_Num.ID").getValue(&ID)) {}
  SaveOutputWithID(ID, Out_4);
}
void Output_PWM_1_Listener() {
  uint32_t ID = 0;
  while (!NexVariable(10, 3, "Set_Output_Num.ID").getValue(&ID)) {}
  SaveOutputWithID(ID, PWM_1);
}
void Output_PWM_2_Listener() {
  uint32_t ID = 0;
  while (!NexVariable(10, 3, "Set_Output_Num.ID").getValue(&ID)) {}
  SaveOutputWithID(ID, PWM_2);
}
void Output_PWM_3_Listener() {
  uint32_t ID = 0;
  while (!NexVariable(10, 3, "Set_Output_Num.ID").getValue(&ID)) {}
  SaveOutputWithID(ID, PWM_3);
}
void Output_Off_Listener() {
  uint32_t ID = 0;
  while (!NexVariable(10, 3, "Set_Output_Num.ID").getValue(&ID)) {}
  SaveOutputWithID(ID, 0);
}

void Output_Sound_Listener() {
  uint32_t Value = 0; //0== Off, 1==On
  while (!NexVariable(0, 21, "Loading_Screen.Sound").getValue(&Value)) {}
  if (Value == 1)
    Settings.Sound = true;
  else
    Settings.Sound = false;

  File temp = SD.open(F("fireflow/set/config.txt"), FILE_WRITE);
  temp.seek(6);
  temp.print(Value);
  temp.close();

}


void SaveOutputWithID(byte ID, byte Data) {
  if (ID == 1) {
    Settings.R_Top = Data;
    SaveOutputs();
  } else if (ID == 2) {
    Settings.R_Bot = Data;
    SaveOutputs();
  } else if (ID == 3) {
    Settings.R_Boost = Data;
    SaveOutputs();
  } else if (ID == 4) {
    Settings.Fan = Data;
    SaveOutputs();
  } else if (ID == 5) {
    Settings.Led_Green = Data;
    SaveOutputs();
  } else if (ID == 6) {
    Settings.Led_Orange = Data;
    SaveOutputs();
  }  else if (ID == 7) {
    Settings.Led_Red = Data;
    SaveOutputs();
  }
  Serial1.println("Read Values");
  Serial1.println(Settings.R_Top);
  Serial1.println(Settings.R_Bot);
  Serial1.println(Settings.R_Boost);
  Serial1.println(Settings.Fan);
  Serial1.println(Settings.Led_Green);
  Serial1.println(Settings.Led_Orange);
  Serial1.println(Settings.Led_Red);
  Serial1.println("==============");
}

void SaveOutputs() {
  if (SD.exists(F("fireflow/set/Outputs.txt"))) //Remove old file
    SD.remove(F("fireflow/set/Outputs.txt"));
  File temp = SD.open(F("fireflow/set/Outputs.txt"), FILE_WRITE); //Make new file

  temp.println(Settings.R_Top);
  temp.println(Settings.R_Bot);
  temp.println(Settings.R_Boost);
  temp.println(Settings.Fan);
  temp.println(Settings.Led_Green);
  temp.println(Settings.Led_Orange);
  temp.println(Settings.Led_Red);
  temp.close();
}


