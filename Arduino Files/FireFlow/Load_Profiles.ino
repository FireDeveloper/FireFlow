void Load_PB_Listener(void *ptr) {
  Profile_Path = F("fireflow/profiles/Standard/PB.prf");
  DecompressProfile();
  while (!NexPage(Reflow_Profile, 0, "Reflow_Profile").show()) {}
}

void Load_PB_Free_Listener(void *ptr) {
  Profile_Path = F("fireflow/profiles/Standard/PBFree.prf");
  DecompressProfile();
  while (!NexPage(Reflow_Profile, 0, "Reflow_Profile").show()) {}
}

void Load_Custom_Listener(void *ptr) {
  //Display Profiles After Page Loaded
}

void DecompressProfile() {
  Serial1.println("Decompress");
  RemoveLoadedProfile();
  CopyProfleFile();
}

void RemoveLoadedProfile() { //Remove all leftover files from old profiles to load the new ones
  if (SD.exists(F("fireflow/log/Auxil.tmp")))
    SD.remove(F("fireflow/log/Auxil.tmp"));
  if (SD.exists(F("fireflow/log/Buzzer.tmp")))
    SD.remove(F("fireflow/log/Buzzer.tmp"));
  if (SD.exists(F("fireflow/log/Fan.tmp")))
    SD.remove(F("fireflow/log/Fan.tmp"));
  if (SD.exists(F("fireflow/log/Auxil.tmp")))
    SD.remove(F("fireflow/log/Auxil.tmp"));
  if (SD.exists(F("fireflow/log/GPIO.tmp")))
    SD.remove(F("fireflow/log/GPIO.tmp"));
  if (SD.exists(F("fireflow/log/Main.tmp")))
    SD.remove(F("fireflow/log/Main.tmp"));
  if (SD.exists(F("fireflow/log/PID_D.tmp")))
    SD.remove(F("fireflow/log/PID_D.tmp"));
  if (SD.exists(F("fireflow/log/PID_I.tmp")))
    SD.remove(F("fireflow/log/PID_I.tmp"));
  if (SD.exists(F("fireflow/log/PID_P.tmp")))
    SD.remove(F("fireflow/log/PID_P.tmp"));
  if (SD.exists(F("fireflow/log/Profile.tmp")))
    SD.remove(F("fireflow/log/Profile.tmp"));
}

void CopyProfleFile() {
  unsigned long Time = millis();
  File File2 = SD.open(Profile_Path);
  File File3 = SD.open(F("fireflow/log/Profile.tmp"), FILE_WRITE);

  //Header
  String data = File2.readStringUntil('\n');
  File3.print(getSeperatedValue(data, ',', 1)); //Profile Name
  data = File2.readStringUntil('\n');
  File3.print(getSeperatedValue(data, ',', 1)); //Window Width
  File3.write((byte)13);
  File3.print(getSeperatedValue(data, ',', 3)); //Window Width
  data = File2.readStringUntil('\n');
  File3.print(getSeperatedValue(data, ',', 1)); //Time Base

  data = File2.readStringUntil('\n'); //First Data
  String Type = getSeperatedValue(data, ',', 0);
  String Temp_Sec = "";
  int counter = 0;

  File File1 = SD.open(F("fireflow/log/Main.tmp"), FILE_WRITE);
  while (Type == "Main") {
    counter++;
    Temp_Sec = getSeperatedValue(data, ',', 1) + ',' + getSeperatedValue(data, ',', 2);
    File1.print(Temp_Sec);
    data = File2.readStringUntil('\n');
    Type = getSeperatedValue(data, ',', 0);
  } File1.close();
  File3.print(counter);
  File3.write((byte)13);
  counter = 0;

  File1 = SD.open(F("fireflow/log/Auxil.tmp"), FILE_WRITE);
  while (Type == "Aux") {
    counter++;
    Temp_Sec = getSeperatedValue(data, ',', 1) + ',' + getSeperatedValue(data, ',', 2);
    File1.print(Temp_Sec);
    data = File2.readStringUntil('\n');
    Type = getSeperatedValue(data, ',', 0);
  } File1.close();
  File3.print(counter);
  File3.write((byte)13);
  counter = 0;

  File1 = SD.open(F("fireflow/log/Fan.tmp"), FILE_WRITE);
  while (Type == "Fan") {
    counter++;
    Temp_Sec = getSeperatedValue(data, ',', 1) + ',' + getSeperatedValue(data, ',', 2);
    File1.print(Temp_Sec);
    data = File2.readStringUntil('\n');
    Type = getSeperatedValue(data, ',', 0);
  } File1.close();
  File3.print(counter);
  File3.write((byte)13);
  counter = 0;

  File1 = SD.open(F("fireflow/log/Buzzer.tmp"), FILE_WRITE);
  while (Type == "Buzzer") {
    counter++;
    Temp_Sec = getSeperatedValue(data, ',', 1) + ',' + getSeperatedValue(data, ',', 2);
    File1.print(Temp_Sec);
    data = File2.readStringUntil('\n');
    Type = getSeperatedValue(data, ',', 0);
  } File1.close();
  File3.print(counter);
  File3.write((byte)13);
  counter = 0;

  File1 = SD.open(F("fireflow/log/GPIO.tmp"), FILE_WRITE);
  while (Type == "GPIO") {
    counter++;
    Temp_Sec = getSeperatedValue(data, ',', 1) + ',' + getSeperatedValue(data, ',', 2);
    File1.print(Temp_Sec);
    data = File2.readStringUntil('\n');
    Type = getSeperatedValue(data, ',', 0);
  } File1.close();
  File3.print(counter);
  File3.write((byte)13);
  //  counter = 0;

  File1 = SD.open(F("fireflow/log/PID_P.tmp"), FILE_WRITE);
  while (Type == "GainP") {
    Temp_Sec = getSeperatedValue(data, ',', 1);
    File1.print(Temp_Sec);
    data = File2.readStringUntil('\n');
    Type = getSeperatedValue(data, ',', 0);
  } File1.close();

  File1 = SD.open(F("fireflow/log/PID_I.tmp"), FILE_WRITE);
  while (Type == "GainI") {
    Temp_Sec = getSeperatedValue(data, ',', 1);
    File1.print(Temp_Sec);
    data = File2.readStringUntil('\n');
    Type = getSeperatedValue(data, ',', 0);
  } File1.close();

  File1 = SD.open(F("fireflow/log/PID_D.tmp"), FILE_WRITE);
  while (Type == "GainD") {
    Temp_Sec = getSeperatedValue(data, ',', 1);
    File1.print(Temp_Sec);
    data = File2.readStringUntil('\n');
    Type = getSeperatedValue(data, ',', 0);
  } File1.close();

  File2.close();
  File3.close();
  Serial1.println((millis() - Time), DEC);
  Serial1.println("End");
}


String getSeperatedValue(String data, char separator, int index) {
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
  byte ibuffer[255] = "";
  int ibufferspace = sizeof(ibuffer);
  uint16_t i = 0;
  int BuffSize = File1.read(ibuffer, ibufferspace);
  Serial1.println(BuffSize);
  Serial1.println(*ibuffer);
  i++;
  if (i == ibufferspace) {
    File2.write(ibuffer, BuffSize);
    i = 0;
  }
  }
  File2.write(ibuffer, i - 1);*/
