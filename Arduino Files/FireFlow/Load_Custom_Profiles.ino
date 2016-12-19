void File_List_Page_Listener() {
  UpdateDisplayProfiles();
}

void Load_Profile_0_Listener() {
  Serial1.println("Load 1");
  Profile_Path = Profile_1_Path;
  DecompressProfile();
  while (!File_List_Page.show()) {}
}
void Load_Profile_1_Listener() {
  Serial1.println("Load 2");
  Profile_Path = Profile_2_Path;
  DecompressProfile();
  while (!File_List_Page.show()) {}
}
void Load_Profile_2_Listener() {
  Serial1.println("Load 3");
  Profile_Path = Profile_3_Path;
  DecompressProfile();
  while (!File_List_Page.show()) {}
}
void Load_Profile_3_Listener() {
  Serial1.println("Load 4");
  Profile_Path = Profile_4_Path;
  DecompressProfile();
  while (!File_List_Page.show()) {}
}

void Delete_Profile_0_Listener() {
  Serial1.println("Delete 1");
}
void Delete_Profile_1_Listener() {
  Serial1.println("Delete 2");
}
void Delete_Profile_2_Listener() {
  Serial1.println("Delete 3");
}
void Delete_Profile_3_Listener() {
  Serial1.println("Delete 4");
}
void Profile_Up_Listener() {
  Serial1.println("Up");
  if (ProfilePosition > 0) {
    ProfilePosition--;
    UpdateDisplayProfiles();
  }
}

void Profile_Down_Listener() {
  Serial1.println("Down");
  int profiles = LoadProfilesNum();
  if (ProfilePosition + 4 < profiles) {
    ProfilePosition++;
    UpdateDisplayProfiles();
  }

}

void UpdateDisplayProfiles() {
  File dir = SD.open(F("FireFlow/profiles/"));
  for (uint16_t i = 0; i < ProfilePosition; i++) //Pass Unwanted Files
    dir.openNextFile();

  File profile;

  profile = dir.openNextFile();
  while (!NexText(File_List_Screen_ID, 6, "Name_0").setText(CutFileType(profile.name()))) {}
  Profile_1_Path = GetFullPath(profile.name());

  profile = dir.openNextFile();
  while (!NexText(File_List_Screen_ID, 7, "Name_1").setText(CutFileType(profile.name()))) {}
  Profile_2_Path = GetFullPath(profile.name());

  profile = dir.openNextFile();
  while (!NexText(File_List_Screen_ID, 8, "Name_2").setText(CutFileType(profile.name()))) {}
  Profile_3_Path = GetFullPath(profile.name());

  profile = dir.openNextFile();
  while (!NexText(File_List_Screen_ID, 9, "Name_3").setText(CutFileType(profile.name()))) {}
  Profile_4_Path = GetFullPath(profile.name());

  profile.close();
  dir.close();
}

char* CutFileType(char* CharArray) {
  byte counter = 0;
  while (CharArray[counter] != '.')
    counter++;

  char* FileName = new char[counter];

  for (byte i = 0; i < counter; i++)
    FileName[i] = CharArray[i];

  return FileName;
}

String GetFullPath(char* FileName) {
  String temp(FileName);
  temp = "FireFlow/profiles/" + temp;
  Serial1.println(temp);
  return temp;
}





