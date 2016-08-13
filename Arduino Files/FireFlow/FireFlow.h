#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


#define YP A1   //[A1], A3 for ILI9320, A2 for ST7789V 
#define YM 7    //[ 7], 9             , 7
#define XM A2   //[A2], A2 for ILI9320, A1 for ST7789V
#define XP 6    //[ 6], 8             , 6

#define BUFFPIXEL 20

//Colors
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define GRAY   0x8410
#define DARK_GRAY   0x4208
#define LIGHT_GRAY   0xBDF7

#define HOLO_BLUE_LIGHT 0x35BC
#define HOLO_BLUE_DARK 0x04D9
#define HOLO_BLUE_BRIGHT 0x06FF



//Files Types
#define FILE_TRUE 0x30 //char '0'
#define FILE_FALSE 0x31 //char '1'

//Common Files
#define FILE_CONFIG F("fireflow/set/config.txt")
