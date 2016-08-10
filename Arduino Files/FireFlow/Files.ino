void Save_TFT_Calibration() {
  File Files;
  Files = SD.open(F("fireflow/set/TFTcal.txt"), FILE_WRITE);
  Files.seek(0);
  Files.println(Cal_Left_X);
  Files.println(Cal_Right_X);
  Files.println(Cal_Top_Y);
  Files.println(Cal_Bot_Y);
  Files.close();
}

void Load_TFT_Calibration() {
  String s;
  File Files;
  Files = SD.open(F("fireflow/set/TFTcal.txt"));

  s = Files.readStringUntil('\n');
  Cal_Left_X = s.toInt();
  s = Files.readStringUntil('\n');
  Cal_Right_X = s.toInt();
  s = Files.readStringUntil('\n');
  Cal_Top_Y = s.toInt();
  s = Files.readStringUntil('\n');
  Cal_Bot_Y = s.toInt();

  Files.close();
}
