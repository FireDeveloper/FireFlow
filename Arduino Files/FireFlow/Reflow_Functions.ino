void Reflow_Preheat() {
  uint16_t SetPoint = RefData.getMainValue(0);
  HeatUp(true);
  HeatDown(true);
  HeatBoost(true);
  Fan(true);
  while (Settings.Temperature < SetPoint) {}
  Running = true;
  HeatUp(false);
  HeatDown(false);
  HeatBoost(false);
  Fan(false);
}

uint16_t Old_Output = 0;

void ReflowStart() {
  myPID.SetTunings(RefData.get_PID_P_Value(0), RefData.get_PID_P_Value(0), RefData.get_PID_P_Value(0));
  myPID.SetOutputLimits(0, 1024);
  myPID.SetMode(AUTOMATIC);


}

void InitPWMOutput() {
  Timer1.initialize(Settings.Window_Size);
  Timer1.attachOVInterrupt(WindowStart);
  Timer1.attachOCRAInterrupt(WindowEnd);
  Timer1.setOCRADuty(0);
}

void WindowStart() {
  Timer1.setOCRADuty(PID_Output);
  Old_Output = PID_Output;
  if (PID_Output != 0)
    Output_Heat();
}
void WindowEnd() {
  if (Old_Output != 1024) {
    HeatUp(false);
    HeatDown(false);
    HeatBoost(false);
  }
}

void Output_CloseAll() {
  HeatUp(false);
  HeatDown(false);
  HeatBoost(false);
  Fan(false);
  LedOff();
}

void Output_Heat() {
  HeatUp(true);
  HeatDown(true);
  HeatBoost(true);
}

void Output_Close() {
  HeatUp(false);
  HeatDown(false);
  HeatBoost(false);
}

void HeatUp(bool On) {
  if (Settings.R_Top != Out_Off)
    if (On)
      digitalWrite(Settings.R_Top, HIGH);
    else
      digitalWrite(Settings.R_Top, LOW);
}
void HeatDown(bool On) {
  if (Settings.R_Bot != Out_Off)
    if (On)
      digitalWrite(Settings.R_Bot, HIGH);
    else
      digitalWrite(Settings.R_Bot, LOW);
}
void HeatBoost(bool On) {
  if (Settings.R_Boost != Out_Off)
    if (On)
      digitalWrite(Settings.R_Boost, HIGH);
    else
      digitalWrite(Settings.R_Boost, LOW);
}
void Fan(bool On) {
  if (Settings.Fan != Out_Off)
    if (On)
      digitalWrite(Settings.Fan, HIGH);
    else
      digitalWrite(Settings.Fan, LOW);
}


void Sound() {
  if (Settings.Sound) {

  }

}

