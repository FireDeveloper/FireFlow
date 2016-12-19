void Print_SD_Card_Info(void *ptr) {
  char buff[12];

  if (!volume.init(card))
    NexText(SD_Info_Screen_ID, 8, "t51").setText(F("Unknown"));
  else {
    sprintf(buff, "FAT%d", volume.fatType());
    NexText(SD_Info_Screen_ID, 8, "t51").setText(buff);
  }
  uint32_t VolumeUsed = UsedSpace(SD.open("/"));
  uint64_t VolumeSize = volume.blocksPerCluster();
  VolumeSize *= volume.clusterCount();
  VolumeSize *= 512;
  uint32_t VolumeFree = VolumeSize - VolumeUsed;
  sprintf(buff, "%d MB", VolumeSize / 1048576);
  NexText(SD_Info_Screen_ID, 11, "t11").setText(buff);
  sprintf(buff, "%d MB", VolumeFree / 1048576);
  NexText(SD_Info_Screen_ID, 12, "t21").setText(buff);
  sprintf(buff, "%d MB", VolumeUsed / 1048576);
  NexText(SD_Info_Screen_ID, 7, "t41").setText(buff);

  itoa(LoadProfilesNum(), buff, 10);
  NexText(SD_Info_Screen_ID, 9, "t61").setText(buff); //Test
}

int LoadProfilesNum() {
  int counter = 0;
  File dir;
  dir = SD.open(F("FireFlow/profiles/"));

  while (true) {
    File entry =  dir.openNextFile();
    if (!entry) // no more files
      break;
    if (FileIsProfile(entry.name()))
      counter++;
    entry.close();
  }
  dir.close();
  return counter;
}

bool FileIsProfile(char* filename) {
  int8_t len = strlen(filename);
  if (strstr(strlwr(filename + (len - 4)), ".prf") || strstr(strlwr(filename + (len - 4)), ".PRF")) //need check to remove 1
    return true;
  else
    return false;
}

uint32_t UsedSpace(File dir) {
  uint32_t counter = 0;
  while (true) {
    File entry =  dir.openNextFile();
    if (!entry)
      break;
    if (entry.isDirectory())
      counter += UsedSpace(entry);
    else
      counter += entry.size();
    entry.close();
  }
  dir.close();
  return counter;
}

