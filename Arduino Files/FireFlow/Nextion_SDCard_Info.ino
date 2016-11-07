bool FileIsProfile(char* filename);
int LoadProfilesNum();

void Print_SD_Card_Info(void *ptr) {
  digitalWrite(13, HIGH);
  char buff[12];

  NexText TXT = NexText(18, 11, "t11");

  uint32_t volumesize = volume.blocksPerCluster();// clusters are collections of blocks
  volumesize *= volume.clusterCount();// we'll have a lot of clusters
  volumesize / 2; // SD card blocks are always 512 bytes /1024 to make kb
  volumesize /= 1024; // /1024 to make MB
  //  TXT_Size.setText(volumesize + "");
  TXT.setText(itoa(volumesize, buff, 10));

  TXT = NexText(18, 8, "t51");
  sprintf(buff, "FAT%d", volume.fatType());
  TXT.setText(buff);


  TXT = NexText(18, 9, "t61");
  itoa(LoadProfilesNum(), buff, 10);
  if (LoadProfilesNum() == 6)
    //  itoa(15, buff, 10);
    TXT.setText("6"); //Test
  else
    TXT.setText("99");
}

int LoadProfilesNum() {
  int counter = 0;
  File root;
  root = SD.open(F("fireflow/profiles"));
  while (true) {
    File entry =  root.openNextFile();
    if (!entry) // no more files
      break;
    if (!entry.isDirectory() && FileIsProfile(entry.name()))
      counter++;
    entry.close();
  }
  return counter;
}

bool FileIsProfile(char* filename) {
  int8_t len = strlen(filename);
  bool result;
  if (strstr(strlwr(filename + (len - 4)), ".prf") || strstr(strlwr(filename + (len - 4)), ".PRF")) //need check to remove 1
    return true;
  else
    return false;
}

