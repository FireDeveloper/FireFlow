ReflowData RefData = ReflowData();

void Reflow_Graph_Page_Listener() {
  //  File file = SD.open(F("fireflow/log/Main.tmp"));
  //  PrintGraph(file, 400, 0, Reflow_Graph_ID);
  //  file.close();
  //  file = SD.open(F("fireflow/log/Fan.tmp"));
  //  PrintGraph(file, 4, 2, Reflow_Graph_ID);
  //  file.close();
  //  file = SD.open(F("fireflow/log/Buzzer.tmp"));
  //  PrintGraph(file, 4, 3, Reflow_Graph_ID);
  //  file.close();
  PrepareReflow();
  while (!Reflow_Start.Set_visibility(true)) {}
}

void Reflow_Start_Listener() {
  uint32_t buff = 0;
  while (!Reflow_Start.getValue(&buff)) {}
  Serial1.println(buff, DEC);

  if (buff == 1) { //Start
    Serial1.println("Start");
    Serial1.println("PreHeat Oven");
    Preheating = true;
    Reflow_Preheat();
  } else { //Stop
    Running = false;
    Preheating = false;
    noInterrupts(); //Avoid Bugs
    Output_CloseAll();
    Serial1.println("End");
    interrupts();
  }
}

void PrintProfileData() {
  Serial1.println("Main");
  for (byte i = 0; i < RefData.getMainSize(); i++) {
    Serial1.print(RefData.getMainValue(i), DEC);
    Serial1.print(" ");
    Serial1.println(RefData.getMainTime(i), DEC);
  }
  Serial1.println("Aux");
  for (byte i = 0; i < RefData.getAuxSize(); i++) {
    Serial1.print(RefData.getAuxValue(i), DEC);
    Serial1.print(" ");
    Serial1.println(RefData.getAuxTime(i), DEC);
  }
  Serial1.println("Fan");
  for (byte i = 0; i < RefData.getFanSize(); i++) {
    Serial1.print(RefData.getFanValue(i), DEC);
    Serial1.print(" ");
    Serial1.println(RefData.getFanTime(i), DEC);
  }
  Serial1.println("Buzzer");
  for (byte i = 0; i < RefData.getBuzzerSize(); i++) {
    Serial1.print(RefData.getBuzzerValue(i), DEC);
    Serial1.print(" ");
    Serial1.println(RefData.getBuzzerTime(i), DEC);
  }
  Serial1.println("GPIO");
  for (byte i = 0; i < RefData.getGPIOSize(); i++) {
    Serial1.print(RefData.getGPIOValue(i), DEC);
    Serial1.print(" ");
    Serial1.println(RefData.getGPIOTime(i), DEC);
  }

  Serial1.println("PID P");
  for (byte i = 0; i < RefData.getMainSize(); i++)
    Serial1.println(RefData.get_PID_P_Value(i), DEC);

  Serial1.println("PID I");
  for (byte i = 0; i < RefData.getMainSize(); i++)
    Serial1.println(RefData.get_PID_I_Value(i), DEC);

  Serial1.println("PID D");
  for (byte i = 0; i < RefData.getMainSize(); i++)
    Serial1.println(RefData.get_PID_D_Value(i), DEC);
}

void PrepareReflow() {
  Reflow_Get_Bounds();

  LoadDataForReflow(F("fireflow/log/Main.tmp"), RefData.getMainSize(), MainData);
  LoadDataForReflow(F("fireflow/log/Auxil.tmp"), RefData.getAuxSize(), AuxData);
  LoadDataForReflow(F("fireflow/log/Fan.tmp"), RefData.getFanSize(), FanData);
  LoadDataForReflow(F("fireflow/log/Buzzer.tmp"), RefData.getBuzzerSize(), BuzzerData);
  LoadDataForReflow(F("fireflow/log/GPIO.tmp"), RefData.getGPIOSize(), GPIOData);

  LoadDataForReflow(F("fireflow/log/PID_P.tmp"), RefData.getMainSize(), PID_P_Data);
  LoadDataForReflow(F("fireflow/log/PID_I.tmp"), RefData.getMainSize(), PID_I_Data);
  LoadDataForReflow(F("fireflow/log/PID_D.tmp"), RefData.getMainSize(), PID_D_Data);
}


void Reflow_Get_Bounds() {
  File F = SD.open(F("fireflow/log/Profile.tmp"));
  String data = F.readStringUntil(0x0d); //Name
  //====================================
  Serial1.println(data);
  data = F.readStringUntil(0x0d);//Width
  RefData.SetWidth(data.toInt());
  data = F.readStringUntil(0x0d);//Height
  RefData.SetHeight(data.toInt());
  data = F.readStringUntil(0x0d);//TimeBase
  RefData.SetTimeBase(data.toInt());
  data = F.readStringUntil(0x0d);//Main
  RefData.SetMainSize(data.toInt());
  data = F.readStringUntil(0x0d);//Aux
  RefData.SetAuxSize(data.toInt());
  data = F.readStringUntil(0x0d);//Fan
  RefData.SetFanSize(data.toInt());
  data = F.readStringUntil(0x0d);//Buzzer
  RefData.SetBuzzerSize(data.toInt());
  data = F.readStringUntil(0x0d);//GPIO
  RefData.SetGPIOSize(data.toInt());
  F.close();
}

void LoadDataForReflow(String Path, byte Size, byte ID) {
  String data;
  File F = SD.open(Path);
  for (byte i = 0; i < Size; i++) {
    data = F.readStringUntil(0x0d);
    switch (ID) {
      case MainData:
        RefData.AddMainData(getSeperatedValue(data, ',', 1).toInt(),  getSeperatedValue(data, ',', 0).toInt());
        break;
      case AuxData:
        RefData.AddAuxData(getSeperatedValue(data, ',', 1).toInt(),  getSeperatedValue(data, ',', 0).toInt());
        break;
      case FanData:
        RefData.AddFanData(getSeperatedValue(data, ',', 1).toInt(),  getSeperatedValue(data, ',', 0).toInt());
        break;
      case BuzzerData:
        RefData.AddBuzzerData(getSeperatedValue(data, ',', 1).toInt(),  getSeperatedValue(data, ',', 0).toInt());
        break;
      case GPIOData:
        RefData.AddGPIOData(getSeperatedValue(data, ',', 1).toInt(),  getSeperatedValue(data, ',', 0).toInt());
        break;
      case PID_P_Data:
        RefData.Add_PID_P_Data(getSeperatedValue(data, ',', 0).toFloat());
        break;
      case PID_I_Data:
        RefData.Add_PID_I_Data(getSeperatedValue(data, ',', 0).toFloat());
        break;
      case PID_D_Data:
        RefData.Add_PID_D_Data(getSeperatedValue(data, ',', 0).toFloat());
        break;
      default:
        break;
    }
  }
  F.close();
}

