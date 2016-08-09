#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


//Files Types
#define FILE_TRUE 0x30 //char '0'
#define FILE_FALSE 0x31 //char '1'

//Common Files
#define FILE_CONFIG F("fireflow/set/config.txt")
