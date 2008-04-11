

#ifndef _LCD_STR912
#define _LCD_STR912

// backlight control
#define BKLGHT_LCD_ON 	1
#define BKLGHT_LCD_OFF 	2

// Booleans
#define NOFILL 			0
#define FILL 			1

// 12-bit color definitions
#define WHITE 			0xFFF
#define BLACK 			0x000
#define RED 			0x00F
#define GREEN 			0x0F0
#define BLUE 			0xF00
#define CYAN 			0xFF0
#define MAGENTA 		0xF0F
#define YELLOW 			0x0FF
#define BROWN 			0x22B
#define ORANGE 			0x0AF
#define PINK 			0xA6F

// Font sizes
#define SMALL 			0
#define MEDIUM 			1
#define LARGE 			2

// hardware definitions
//#define SPI_SR_TXEMPTY
//#define LCD_RESET_LOW pPIOA->PIO_CODR = BIT2
//#define LCD_RESET_HIGH pPIOA->PIO_SODR = BIT2

// LCD GE8 (not GE12)
  #define DISON     0xAF      // Display on
  #define DISOFF    0xAE      // Display off
  #define DISNOR    0xA6      // Normal display
  #define DISINV    0xA7      // Inverse display
  #define COMSCN    0xBB      // Common scan direction
  #define DISCTL    0xCA      // Display control
//  #define DISCTL    0xBA      // Display control
  #define SLPIN     0x95      // Sleep in
  #define SLPOUT    0x94      // Sleep out
  #define PASET     0x75      // Page address set
  #define CASET     0x15      // Column address set
  #define DATCTL    0xBC      // Data scan direction, etc.
  #define RGBSET8   0xCE      // 256-color position set
  #define RAMWR     0x5C      // Writing to memory
  #define RAMRD     0x5D      // Reading from memory
  #define PTLIN     0xA8      // Partial display in
  #define PTLOUT    0xA9      // Partial display out
  #define RMWIN     0xE0      // Read and modify write
  #define RMWOUT    0xEE      // End
  #define ASCSET    0xAA      // Area scroll set
  #define SCSTART   0xAB      // Scroll start set
  #define OSCON     0xD1      // Internal oscillation on
  #define OSCOFF    0xD2      // Internal oscillation off
  #define PWRCTR    0x20      // Power control
  #define VOLCTR    0x81      // Electronic volume control
  #define VOLUP     0xD6      // Increment electronic control by 1
  #define VOLDOWN   0xD7      // Decrement electronic control by 1
  #define TMPGRD    0x82      // Temperature gradient set
  #define EPCTIN    0xCD      // Control EEPROM
  #define EPCOUT    0xCC      // Cancel EEPROM control
  #define EPMWR     0xFC      // Write into EEPROM
  #define EPMRD     0xFD      // Read from EEPROM
  #define EPSRRD1   0x7C      // Read register 1
  #define EPSRRD2   0x7D      // Read register 2
  #define NOP       0x25      // NOP instruction

void sDelay (unsigned long a);

void InitLCD(void);
void Backlight(unsigned char state);

void WriteSpiCommand(unsigned int data);
void WriteSpiData(unsigned int data);

void LCDSettings(void);
void LCDWrite130x130bmp(void);

void SetContrast(unsigned char contrast);

// TI
void LCDPixelColor(int color);
void LCDPutInt(long int nb, int nb_char_min , int x, int y, int Size, int fColor, int bColor);
void LCDPutFloat(float nb, int nb_char_min, int precision, int x, int y, int Size, int fColor, int bColor);


// trouvé sur SparkFun
void fillWin(int area, int color);
int setWin(int x0, int y0, int x1, int y1);
// Ajouté depuis AT91SM7 : 
void LCDClearScreen(void);
void LCDSetXY(int x, int y);
void LCDSetPixel(int x, int y, int color);
void LCDSetLine(int x0, int y0, int x1, int y1, int color);
void LCDSetRect(int x0, int y0, int x1, int y1, unsigned char fill, int color);
void LCDSetCircle(int x0, int y0, int radius, int color);
void LCDPutChar(char c, int x, int y, int size, int fColor, int bColor);
void LCDPutStr(char *pString, int x, int y, int Size, int fColor, int bColor);


#endif // Lcd_STR912







