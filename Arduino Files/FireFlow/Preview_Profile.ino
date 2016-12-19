void Preview_Graph_Page_Listener() {
  Serial1.print("freeMemory()=");
  Serial1.println(freeMemory());
  File file = SD.open(F("fireflow/log/Main.tmp"));
  PrintGraph(file, 400, 0, Preview_Graph_ID);
  file.close();
  file = SD.open(F("fireflow/log/Auxil.tmp"));
  PrintGraph(file, 4, 1, Preview_Graph_ID);
  file.close();
  file = SD.open(F("fireflow/log/Fan.tmp"));
  PrintGraph(file, 4, 2, Preview_Graph_ID);
  file.close();
  file = SD.open(F("fireflow/log/Buzzer.tmp"));
  PrintGraph(file, 4, 3, Preview_Graph_ID);
  file.close();
  Serial1.print("freeMemory()=");
  Serial1.println(freeMemory());
}

void PrintGraph(File &F, uint16_t MaxValue, byte Channel, uint8_t ID) {
  if (F.available()) {
    String data = F.readStringUntil(0x0d);
    int OldTime = getSeperatedValue(data, ',', 0).toInt();
    int OldValue = getSeperatedValue(data, ',', 1).toInt();
    SendDataToChart(1, map(OldValue, 0, MaxValue, 0, 255), ID);

    int t = 1;
    while (F.available()) {
      data = F.readStringUntil(0x0d);
      int NewTime = getSeperatedValue(data, ',', 0).toInt();
      int NewValue = getSeperatedValue(data, ',', 1).toInt();
      while (t < (NewTime - OldTime)) {
        SendDataToChart(Channel, MathLine(OldTime, OldValue, NewTime, NewValue, t, MaxValue), ID);
        t++;
      }
      t = 0;
      OldTime = NewTime;
      OldValue = NewValue;
    }
  }
  //  F.close(); //File close after function return
}

int MathLine(uint16_t P1_x, uint16_t P1_y, uint16_t P2_x, uint16_t P2_y, uint16_t point, uint16_t MaxValue) {
  int temp = map(point, 0, P2_x - P1_x, P1_y, P2_y);
  return map(temp, 0, MaxValue, 0, 255);
}

void SendDataToChart(uint8_t Channel, uint8_t Number, uint8_t ID) {
  while (!NexWaveform(ID, 1, "Chart").addValue(Channel, Number)) {}
}

