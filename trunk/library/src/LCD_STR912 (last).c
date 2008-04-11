

#include "lcd_STR912.h"

#include "91x_lib.h"
#include "bmp.h"
#include "bits.h"
#include "font.h"




#define SSP0_FREQ   100000 // (100KHz)
#define GE08



void sDelay (unsigned long a) { while (--a!=0); }

unsigned int i,j;

void InitLCD(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	SSP_InitTypeDef   SSP_InitStructure;
  // GPIO
  //
  // Init GPIO Structure
  GPIO_DeInit(GPIO6);
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_Alternate=GPIO_OutputAlt1;
  //
  // Pin for backlight (P6.4)
  GPIO_Init (GPIO6, &GPIO_InitStructure);
  GPIO_WriteBit(GPIO6, GPIO_Pin_4, Bit_SET);
  //
  GPIO_DeInit(GPIO0);
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_Alternate=GPIO_OutputAlt1;
  //
  // Pin for LCD_CS (P0.1)
  GPIO_Init (GPIO0, &GPIO_InitStructure);

  GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_SET);
  // SSP1
  //
  // Enable the __SSP1 Clock
  SCU_APBPeriphClockConfig(__SSP1 ,ENABLE);
  //
  // Set desired frequency
  //SSP1->PR = (SCU_GetPCLKFreqValue()*1000)/SSP0_FREQ;
  //SSP1->PR = 250;
  //
  GPIO_DeInit(GPIO3);
  // Gonfigure SSP1_CLK, SSP1_MOSI
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Enable;
  GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt2;
  GPIO_Init (GPIO3, &GPIO_InitStructure);

  //Configure SSP1_MISO pin
  GPIO_InitStructure.GPIO_Direction = GPIO_PinInput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Enable;
  GPIO_InitStructure.GPIO_Alternate = GPIO_InputAlt1  ;
  GPIO_Init (GPIO3, &GPIO_InitStructure);

  //
  // SSP1 configuration
  SSP_DeInit(SSP1);
  SSP_InitStructure.SSP_FrameFormat = SSP_FrameFormat_Motorola;
  SSP_InitStructure.SSP_Mode = SSP_Mode_Master;
  SSP_InitStructure.SSP_CPOL = SSP_CPOL_Low;
  SSP_InitStructure.SSP_CPHA = SSP_CPHA_1Edge;
  SSP_InitStructure.SSP_DataSize = SSP_DataSize_9b;
  SSP_InitStructure.SSP_ClockRate = 0;
  SSP_InitStructure.SSP_ClockPrescaler = 25; //250
  SSP_Init(SSP1, &SSP_InitStructure);
  //
  // Enable SSP1
  SSP_Cmd(SSP1, ENABLE);

}


void WriteSpiCommand(unsigned int data){

  GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_RESET);
  data = (data & ~0x0100);
  SSP_SendData(SSP1, data);
  while(SSP_GetFlagStatus(SSP1, SSP_FLAG_Busy));
  GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_SET);

}

void WriteSpiData(unsigned int data){

  
  GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_RESET);
  data = (data | 0x0100);
  SSP_SendData(SSP1, data);
  while(SSP_GetFlagStatus(SSP1, SSP_FLAG_Busy));
  GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_SET);

}


void Backlight(unsigned char state) {

  if(state == BKLGHT_LCD_ON)
    GPIO_Write(GPIO6,BIT4);     // Set P6.4 to HIGH
  else
    GPIO_Write(GPIO6,BIT4);     // Set PB6.4 to LOW

}

void SetContrast(unsigned char contrast) {

#ifdef GE12
  WriteSpiCommand(CONTRAST);
  WriteSpiData(0x20+contrast);    // contrast
#else

#endif
}

void LCDSettings(void) {


#ifdef GE12

  ///// Initialization start /////

  // 2. Software Reset
  WriteSpiCommand(SOFTRST);
  sDelay(2000);


  // 3. Initial escape
  WriteSpiCommand(INITESC);
  sDelay(2000);

  ///// Initialization end /////


  ///// Display setting 1 /////

  // 1. Refresh set
  WriteSpiCommand(REFSET);
  WriteSpiData(0);


  // 2. Display control - 7 parameters
  WriteSpiCommand(DISPCTRL);
  WriteSpiData(128);     // Set the lenght of one selection term
  WriteSpiData(128);     // Set N inversion -> no N inversion
  WriteSpiData(134);     // Set frame frequence and bias rate -> 2 devision of frequency and 1/8 bias, 1/67 duty, 96x67 size
  WriteSpiData(84);      // Set duty parameter
  WriteSpiData(69);      // Set duty parameter
  WriteSpiData(82);      // Set duty parameter
  WriteSpiData(67);      // Set duty parameter


  // 3.1 Grey scale 0 position set - 15 parameters
  WriteSpiCommand(GRAYSCALE0);
  WriteSpiData(1);     // GCP1 - gray lavel to be output when the RAM data is "0001"
  WriteSpiData(2);     // GCP2 - gray lavel to be output when the RAM data is "0010"
  WriteSpiData(4);     // GCP3 - gray lavel to be output when the RAM data is "0011"
  WriteSpiData(8);     // GCP4 - gray lavel to be output when the RAM data is "0100"
  WriteSpiData(16);    // GCP5 - gray lavel to be output when the RAM data is "0101"
  WriteSpiData(30);    // GCP6 - gray lavel to be output when the RAM data is "0110"
  WriteSpiData(40);    // GCP7 - gray lavel to be output when the RAM data is "0111"
  WriteSpiData(50);    // GCP8 - gray lavel to be output when the RAM data is "1000"
  WriteSpiData(60);    // GCP9 - gray lavel to be output when the RAM data is "1001"
  WriteSpiData(70);    // GCP10 - gray lavel to be output when the RAM data is "1010"
  WriteSpiData(80);    // GCP11 - gray lavel to be output when the RAM data is "1011"
  WriteSpiData(90);    // GCP12 - gray lavel to be output when the RAM data is "1100"
  WriteSpiData(100);   // GCP13 - gray lavel to be output when the RAM data is "1101"
  WriteSpiData(110);   // GCP14 - gray lavel to be output when the RAM data is "1110"
  WriteSpiData(127);   // GCP15 - gray lavel to be output when the RAM data is "1111"

  // 4. Gamma curve set - select gray scale - GRAYSCALE 0 or GREYSCALE 1
  WriteSpiCommand(GAMMA);
  WriteSpiData(1);     // Select grey scale 0


  // 5. Command driver output
  WriteSpiCommand(COMMONDRV);
  WriteSpiData(0);     // Set COM1-COM41 side come first, normal mod


  // 6. Set Normal mode (my)
  WriteSpiCommand(NORMALMODE);

  // 7. Inversion off
  // WriteSpiCommand(INVERSIONOFF);

  // 8. Column address set
  WriteSpiCommand(COLADDRSET);
  WriteSpiData(0);
  WriteSpiData(131);
  // WriteSpiData(0);

  // 9. Page address set
  WriteSpiCommand(PAGEADDRSET);
  WriteSpiData(0);
  WriteSpiData(131);
  // WriteSpiData(0);

  // 10. Memory access controler
  WriteSpiCommand(ACCESSCTRL);
  WriteSpiData(0x40);     // horizontal
  // WriteSpiData(0x20);   // vertical

  ///// Display setting 1 end  /////


  ///// Power supply  ///////

  // 1. Power control
  WriteSpiCommand(PWRCTRL);
  WriteSpiData(4);     // Internal resistance, V1OUT -> high power mode, oscilator devision rate

  // 2. Sleep out
  WriteSpiCommand(SLEEPOUT);


  // 3. Voltage control - voltage control and write contrast define LCD electronic volume
  WriteSpiCommand(VOLTCTRL);
  //WriteSpiData(0x7f);    //  full voltage control
  WriteSpiData(0x03);    //  must be "1"

  // 4. Write contrast
  WriteSpiCommand(CONTRAST);
  WriteSpiData(0x3b);    // contrast

  sDelay(2000);

  // 5. Temperature gradient
  WriteSpiCommand(TEMPGRADIENT);
  for(i=0; i<14; i++) {
    WriteSpiData(0);
  }

  // 6. Booster voltage ON
  WriteSpiCommand(BOOSTVON);


  // Finally - Display On
  WriteSpiCommand(DISPLAYON);	

#else

  // Display vontrol
  WriteSpiCommand(DISOFF);	// Display On
  WriteSpiCommand(SLPIN);

  WriteSpiCommand(DISCTL);
//  WriteSpiData(0x03); // no division
//  WriteSpiData(0x23); // 160 line
//  WriteSpiData(0x02); // 2 highlighte line
  WriteSpiData(0x00); // default
  WriteSpiData(0x20); // (32 + 1) * 4 = 132 lines (of which 130 are visible)
  WriteSpiData(0x0a); // default




  // COM scan
  WriteSpiCommand(COMSCN);
  WriteSpiData(0x01);  // Scan 1-80

  // Internal oscilator ON
  WriteSpiCommand(OSCON);

  // Sleep out
  WriteSpiCommand(SLPOUT);

  // Voltage control
  WriteSpiCommand(VOLCTR);
  WriteSpiData(0x1F); // middle value of V1
  WriteSpiData(0x03); // middle value of resistance value

  // Temperature gradient
  WriteSpiCommand(TMPGRD);
  WriteSpiData(0x00); // default

  // Power control
  WriteSpiCommand(PWRCTR);
  WriteSpiData(0x0f);   // referance voltage regulator on, circuit voltage follower on, BOOST ON

  // Normal display
  //WriteSpiCommand(DISNOR);

  // Inverse display
  WriteSpiCommand(DISINV);

  // Partial area off
  WriteSpiCommand(PTLOUT);

//  // Scroll area set
//  WriteSpiCommand(ASCSET);
//  WriteSpiData(0);
//  WriteSpiData(0);
//  WriteSpiData(40);
//  WriteSpiData(3);

//  // Vertical scrool address start
//  WriteSpiCommand(SCSTART);
//  WriteSpiData(0);

/*
  WriteSpiCommand(DATCTL);
  WriteSpiData(0x02); // all inversions off, column direction
  WriteSpiData(0x00); // RGB sequence
  WriteSpiData(0x03); // Grayscale -> 16

    WriteSpiCommand(PASET);
	WriteSpiData(0);
	WriteSpiData(2);
	// Column address set (command 0x2A)
	WriteSpiCommand(CASET);
	WriteSpiData(0);
	WriteSpiData(2);

	fillWin(50,0);
*/
	sDelay(10000);

	  // Data control
  WriteSpiCommand(DATCTL);
  WriteSpiData(0x00); // all inversions off, column direction
  WriteSpiData(0x03); // RGB sequence
  WriteSpiData(0x01); // Grayscale -> 16
  
	//(0,0)
	WriteSpiCommand(PASET);
	WriteSpiData(0);
	WriteSpiData(131);
	// Column address set (command 0x2A)
	WriteSpiCommand(CASET);
	WriteSpiData(0);
	WriteSpiData(131);




	WriteSpiCommand(NOP);
	fillWin(100000,0);

	sDelay(10000);

	WriteSpiCommand(DISON);	// Display On
						   

	sDelay(10000);

  // wait ~100ms
  

#endif

}



void LCDWrite130x130bmp(void) {

#ifdef GE12

  // Display OFF
  WriteSpiCommand(DISPLAYOFF);

    // WRITE MEMORY
  WriteSpiCommand(MEMWRITE);

  for(j=0; j<sizeof(bmp); j++) {
    WriteSpiData(bmp[j]);
    //WriteSpiData(0xFF);
  }

  // Display On
  WriteSpiCommand(DISPLAYON);	

#else

	WriteSpiCommand(NOP);
  // Display OFF
  //WriteSpiCommand(DISOFF);

  	WriteSpiCommand(PASET);
	WriteSpiData(0);
	WriteSpiData(131);
	// Column address set (command 0x2A)
	WriteSpiCommand(CASET);
	WriteSpiData(0);
	WriteSpiData(131);

  // WRITE MEMORY
  WriteSpiCommand(RAMWR);

  //for(j=0; j<sizeof(bmp)-396; j++) {
  for(j=0; j<25740; j++) {
    WriteSpiData(bmp[j]);
    //WriteSpiData(0xFF);
  }

  // wait ~100ms
  sDelay(10000);

  // Display On
  WriteSpiCommand(DISON);	

#endif

}


void fillWin(int area, int color) {     // Fill window with specified color
    int i;
    WriteSpiCommand(RAMWR);
    for (i=0; i<area; i++) {
        //WriteSpiData(color>>8);      // big endian: 0000_RRRR_GGGG_BBBB
        //WriteSpiData(color);
	WriteSpiData(0x00); //(unsigned char)((color >> 4) & 0x00FF));
	WriteSpiData(0x00); //(unsigned char)((color >> 4) & 0x00FF));
	WriteSpiData(0x00); //(unsigned char)((color >> 4) & 0x00FF));
    }
} // fillWin



int setWin(int x0, int y0, int x1, int y1) {
// Set rectangular area for a window on the LCD
// Returns its area (in pixels)
    int t;

    if (x0>x1) {t=x0; x0=x1; x1=t;}     // put coordinates into ascending order
    if (y0>y1) {t=y0; y0=y1; y1=t;}

	WriteSpiCommand(CASET);      // set column address
    WriteSpiData(x0);      // start (visible area starts in column 2)
    WriteSpiData(x1);      // end

    WriteSpiCommand(PASET);      // set page (row) address
    WriteSpiData(y0);        // start
    WriteSpiData(y1);        // end

return (x1-x0+1) * (y1-y0+1);   // area
} // setWin


/*##################################################
	Ajouté depuis les drivers pour AT91SAM7
  #################################################*/

// *****************************************************************************
// Clears the LCD screen to single color (BLACK)
// *****************************************************************************
void LCDClearScreen(void) {
	long i; // loop counter
	// Row address set (command 0x2B)
	WriteSpiCommand(PASET);
	WriteSpiData(0);
	WriteSpiData(131);
	// Column address set (command 0x2A)
	WriteSpiCommand(CASET);
	WriteSpiData(0);
	WriteSpiData(131);
	// set the display memory to BLACK
	WriteSpiCommand(RAMWR);
	for (i = 0; i < ((131 * 131) / 2); i++) {
		WriteSpiData(BLACK);
		WriteSpiData(BLACK);
		WriteSpiData(BLACK);
	}
}

// *****************************************************************************
// LCDSetXY.c
//
// Sets the Row and Column addresses
//
// Inputs: x = row address (0 .. 131)
// y = column address (0 .. 131)
//
// Returns: nothing
// *****************************************************************************
void LCDSetXY(int x, int y) {
	// Row address set (command 0x2B)
	WriteSpiCommand(PASET);
	WriteSpiData(x);
	WriteSpiData(x);
	// Column address set (command 0x2A)
	WriteSpiCommand(CASET);
	WriteSpiData(y);
	WriteSpiData(y);
}

// *************************************************************************************
// LCDSetPixel.c
//
// Lights a single pixel in the specified color at the specified x and y addresses
//
// Inputs: x = row address (0 .. 131)
// y = column address (0 .. 131)
// color = 12-bit color value rrrrggggbbbb
// rrrr = 1111 full red
// 0000 red is off
//
// gggg = 1111 full green
// 0000 green is off
//
// bbbb = 1111 full blue
// 0000 blue is off
//
// Returns: nothing
//
// Note: see lcd.h for some sample color settings
// *************************************************************************************

void LCDPixelColor(int color) {
	// Colorie le pixel pointé
	int comp;
	WriteSpiCommand(RAMWR);
	WriteSpiData(0x00);	// Pour avoir les 3 segments en 12 bits
	comp= (color>>8) & 0x00F;
	WriteSpiData(comp); // 0 Blue
	comp = color & 0x0FF;
	WriteSpiData(comp);	// Green Red
	WriteSpiCommand(NOP);
}

void LCDSetPixel(int x, int y, int color) {
	LCDSetXY(x, y);
	LCDPixelColor(color);
}

// *************************************************************************************************
// LCDSetLine.c
//
// Draws a line in the specified color from (x0,y0) to (x1,y1)
//
// Inputs: x = row address (0 .. 131)
// y = column address (0 .. 131)
// color = 12-bit color value rrrrggggbbbb
//
// Returns: nothing
//
// Note: good write-up on this algorithm in Wikipedia (search for Bresenham's line algorithm)
// see lcd.h for some sample color settings
//
// Authors: Dr. Leonard McMillan, Associate Professor UNC
// Jack Bresenham IBM, Winthrop University (Father of this algorithm, 1962)
//
// Note: taken verbatim from Professor McMillan's presentation:
// http://www.cs.unc.edu/~mcmillan/comp136/Lecture6/Lines.html
//
// *************************************************************************************************
void LCDSetLine(int x0, int y0, int x1, int y1, int color) {
	int dy = y1 - y0;
	int dx = x1 - x0;
	int stepx, stepy;
	if (dy < 0) { dy = -dy; stepy = -1; } else { stepy = 1; }
	if (dx < 0) { dx = -dx; stepx = -1; } else { stepx = 1; }
	dy <<= 1; // dy is now 2*dy
	dx <<= 1; // dx is now 2*dx
	LCDSetPixel(x0, y0, color);
	if (dx > dy) {
		int fraction = dy - (dx >> 1); // same as 2*dy - dx
		while (x0 != x1) {
			if (fraction >= 0) {
				y0 += stepy;
				fraction -= dx; // same as fraction -= 2*dx
			}
			x0 += stepx;
			fraction += dy; // same as fraction -= 2*dy
			LCDSetPixel(x0, y0, color);
		}
	} else {
		int fraction = dx - (dy >> 1);
		while (y0 != y1) {
			if (fraction >= 0) {
			x0 += stepx;
			fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			LCDSetPixel(x0, y0, color);
		}
	}
}

// *****************************************************************************************
// LCDSetRect.c
//
// Draws a rectangle in the specified color from (x1,y1) to (x2,y2)
// Rectangle can be filled with a color if desired
//
// Inputs: x = row address (0 .. 131)
// y = column address (0 .. 131)
// fill = 0=no fill, 1-fill entire rectangle
// color = 12-bit color value for lines rrrrggggbbbb
// Returns: nothing
//
// Notes:
//
// The best way to fill a rectangle is to take advantage of the "wrap-around" featute
// built into the Philips PCF8833 controller. By defining a drawing box, the memory can
// be simply filled by successive memory writes until all pixels have been illuminated.
//
// 1. Given the coordinates of two opposing corners (x0, y0) (x1, y1)
// calculate the minimums and maximums of the coordinates
//
// xmin = (x0 <= x1) ? x0 : x1;
// xmax = (x0 > x1) ? x0 : x1;
// ymin = (y0 <= y1) ? y0 : y1;
// ymax = (y0 > y1) ? y0 : y1;
//
// 2. Now set up the drawing box to be the desired rectangle
//
// WriteSpiCommand(PASET); // set the row boundaries
// WriteSpiData(xmin);
// WriteSpiData(xmax);
// WriteSpiCommand(CASET); // set the column boundaries
// WriteSpiData(ymin);
// WriteSpiData(ymax);
//
// 3. Calculate the number of pixels to be written divided by 2
//
// NumPixels = ((((xmax - xmin + 1) * (ymax - ymin + 1)) / 2) + 1)
//
// You may notice that I added one pixel to the formula.
// This covers the case where the number of pixels is odd and we
// would lose one pixel due to rounding error. In the case of
// odd pixels, the number of pixels is exact.
// in the case of even pixels, we have one more pixel than
// needed, but it cannot be displayed because it is outside
// the drawing box.
//
// We divide by 2 because two pixels are represented by three bytes.
// So we work through the rectangle two pixels at a time.
//
// 4. Now a simple memory write loop will fill the rectangle
//
// for (i = 0; i < ((((xmax - xmin + 1) * (ymax - ymin + 1)) / 2) + 1); i++) {
// WriteSpiData((color >> 4) & 0xFF);
// WriteSpiData(((color & 0xF) << 4) | ((color >> 8) & 0xF));
// WriteSpiData(color & 0xFF);
// }
//
// In the case of an unfilled rectangle, drawing four lines with the Bresenham line
// drawing algorithm is reasonably efficient.
//
// Author: James P Lynch July 7, 2007
// *****************************************************************************************
void LCDSetRect(int x0, int y0, int x1, int y1, unsigned char fill, int color) {
	int xmin, xmax, ymin, ymax;
	int i;
	// check if the rectangle is to be filled
	if (fill == FILL) {
		// best way to create a filled rectangle is to define a drawing box
		// and loop two pixels at a time
		// calculate the min and max for x and y directions
		xmin = (x0 <= x1) ? x0 : x1;
		xmax = (x0 > x1) ? x0 : x1;
		ymin = (y0 <= y1) ? y0 : y1;
		ymax = (y0 > y1) ? y0 : y1;
		// specify the controller drawing box according to those limits
		// Row address set (command 0x2B)
		WriteSpiCommand(PASET);
		WriteSpiData(xmin);
		WriteSpiData(xmax);
		// Column address set (command 0x2A)
		WriteSpiCommand(CASET);
		WriteSpiData(ymin);
		WriteSpiData(ymax);
		// WRITE MEMORY
		WriteSpiCommand(RAMWR);
		// loop on total number of pixels / 2
		for (i = 0; i < ((((xmax - xmin + 1) * (ymax - ymin + 1)) / 2) + 1); i++) {
			// use the color value to output three data bytes covering two pixels
			LCDPixelColor(color);
		}
	}
	else
	{
		// best way to draw un unfilled rectangle is to draw four lines
		LCDSetLine(x0, y0, x1, y0, color);
		LCDSetLine(x0, y1, x1, y1, color);
		LCDSetLine(x0, y0, x0, y1, color);
		LCDSetLine(x1, y0, x1, y1, color);
	}
}

// *************************************************************************************
// LCDSetCircle.c
//
// Draws a line in the specified color at center (x0,y0) with radius
//
// Inputs: x0 = row address (0 .. 131)
// y0 = column address (0 .. 131)
// radius = radius in pixels
// color = 12-bit color value rrrrggggbbbb
//
// Returns: nothing
//
// Author: Jack Bresenham IBM, Winthrop University (Father of this algorithm, 1962)
//
// Note: taken verbatim Wikipedia article on Bresenham's line algorithm
// http://www.wikipedia.org
// *************************************************************************************
void LCDSetCircle(int x0, int y0, int radius, int color) {
	int f = 1 - radius;
	int ddF_x = 0;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	LCDSetPixel(x0, y0 + radius, color);
	LCDSetPixel(x0, y0 - radius, color);
	LCDSetPixel(x0 + radius, y0, color);
	LCDSetPixel(x0 - radius, y0, color);
	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x + 1;
		LCDSetPixel(x0 + x, y0 + y, color);
		LCDSetPixel(x0 - x, y0 + y, color);
		LCDSetPixel(x0 + x, y0 - y, color);
		LCDSetPixel(x0 - x, y0 - y, color);
		LCDSetPixel(x0 + y, y0 + x, color);
		LCDSetPixel(x0 - y, y0 + x, color);
		LCDSetPixel(x0 + y, y0 - x, color);
		LCDSetPixel(x0 - y, y0 - x, color);
	}
}

// *****************************************************************************
// LCDPutChar.c
//
// Draws an ASCII character at the specified (x,y) address and color
//
// Inputs: c = character to be displayed
// x = row address (0 .. 131)
// y = column address (0 .. 131)
// size = font pitch (SMALL, MEDIUM, LARGE)
// fcolor = 12-bit foreground color value rrrrggggbbbb
// bcolor = 12-bit background color value rrrrggggbbbb
//
//
// Returns: nothing
//
//
// Notes: Here's an example to display "E" at address (20,20)
//
// LCDPutChar('E', 20, 20, MEDIUM, WHITE, BLACK);
//
// (27,20) (27,27)
// | |
// | |
// ^ V V
// : _ # # # # # # # 0x7F
// : _ _ # # _ _ _ # 0x31
// : _ _ # # _ # _ _ 0x34
// x _ _ # # # # _ _ 0x3C
// : _ _ # # _ # _ _ 0x34
// : _ _ # # _ _ _ # 0x31
// : _ # # # # # # # 0x7F
// : _ _ _ _ _ _ _ _ 0x00
//
// ------y------->
// ^ ^
// | |
// | |
// (20,20) (20,27)
//
//
// The most efficient way to display a character is to make use of the "wrap-around" feature
// of the Philips PCF8833 LCD controller chip.
//
// Assume that we position the character at (20, 20) that's a (row, col) specification.
// With the row and column address set commands, you can specify an 8x8 box for the SMALL and MEDIUM
// characters or a 16x8 box for the LARGE characters.
//
// WriteSpiCommand(PASET); // set the row drawing limits
// WriteSpiData(20); //
// WriteSpiData(27); // limit rows to (20, 27)
//
// WriteSpiCommand(CASET); // set the column drawing limits
// WriteSpiData(20); //
// WriteSpiData(27); // limit columns to (20,27)
//
// When the algorithm completes col 27, the column address wraps back to 20
// At the same time, the row address increases by one (this is done by the controller)
//
// We walk through each row, two pixels at a time. The purpose is to create three
// data bytes representing these two pixels in the following format (as specified by Philips
// for RGB 4 : 4 : 4 format (see page 62 of PCF8833 controller manual).
//
// Data for pixel 0: RRRRGGGGBBBB
// Data for Pixel 1: RRRRGGGGBBBB
//
// WriteSpiCommand(RAMWR); // start a memory write (96 data bytes to follow)
//
// WriteSpiData(RRRRGGGG); // first pixel, red and green data
// WriteSpiData(BBBBRRRR); // first pixel, blue data; second pixel, red data
// WriteSpiData(GGGGBBBB); // second pixel, green and blue data
// :
// and so on until all pixels displayed!
// :
// WriteSpiCommand(NOP); // this will terminate the RAMWR command
//
//
// Author: James P Lynch July 7, 2007
// *****************************************************************************
void LCDPutChar(char c, int x, int y, int size, int fColor, int bColor) {
	extern const unsigned char FONT6x8[97][8];
	extern const unsigned char FONT8x8[97][8];
	extern const unsigned char FONT8x16[97][16];
	int i,j;
	unsigned int nCols;
	unsigned int nRows;
	unsigned int nBytes;
	unsigned char PixelRow;
	unsigned char Mask;
	unsigned int Word0;
	unsigned int Word1;
	unsigned char *pFont;
	unsigned char *pChar;
	unsigned char *FontTable[] = {(unsigned char *)FONT6x8,
	(unsigned char *)FONT8x8,
	(unsigned char *)FONT8x16};
	// get pointer to the beginning of the selected font table
	pFont = (unsigned char *)FontTable[size];
	// get the nColumns, nRows and nBytes
	nCols = *pFont;
	nRows = *(pFont + 1);
	nBytes = *(pFont + 2);
	// get pointer to the last byte of the desired character
	pChar = pFont + (nBytes * (c - 0x1F)) + nBytes - 1;
	// Row address set (command 0x2B)
	WriteSpiCommand(PASET);
	WriteSpiData(x);
	WriteSpiData(x + nRows - 1);
	// Column address set (command 0x2A)
	WriteSpiCommand(CASET);
	WriteSpiData(y);
	WriteSpiData(y + nCols - 1);


	  WriteSpiCommand(DATCTL);
  WriteSpiData(0x01); // all inversions off, column direction
  WriteSpiData(0x03); // RGB sequence
  WriteSpiData(0x01); // Grayscale -> 16


	// WRITE MEMORY
	WriteSpiCommand(RAMWR);
	// loop on each row, working backwards from the bottom to the top
	for (i = nRows - 1; i >= 0; i--) {
		// copy pixel row from font table and then decrement row
		PixelRow = *pChar--;
		// loop on each pixel in the row (left to right)
		// Note: we do two pixels each loop
		Mask = 0x80;
			for (j = 0; j < nCols; j += 2) {
			// if pixel bit set, use foreground color; else use the background color
			// now get the pixel color for two successive pixels
			if ((PixelRow & Mask) == 0)
				Word0 = bColor;
			else
				Word0 = fColor;
			Mask = Mask >> 1;
			if ((PixelRow & Mask) == 0)
				Word1 = bColor;
			else
				Word1 = fColor;
			Mask = Mask >> 1;
			// use this information to output three data bytes
			WriteSpiData((Word0 >> 4) & 0xFF);
			WriteSpiData(((Word0 & 0xF) << 4) | ((Word1 >> 8) & 0xF));
			WriteSpiData(Word1 & 0xFF);
			}
		}
	// terminate the Write Memory command
	WriteSpiCommand(NOP);

	  WriteSpiCommand(DATCTL);
  WriteSpiData(0x00); // all inversions off, column direction
  WriteSpiData(0x03); // RGB sequence
  WriteSpiData(0x01); // Grayscale -> 16
}
// *************************************************************************************************
// LCDPutStr.c
//
// Draws a null-terminates character string at the specified (x,y) address, size and color
//
// Inputs: pString = pointer to character string to be displayed
// x = row address (0 .. 131)
// y = column address (0 .. 131)
// Size = font pitch (SMALL, MEDIUM, LARGE)
// fColor = 12-bit foreground color value rrrrggggbbbb
// bColor = 12-bit background color value rrrrggggbbbb
//
//
// Returns: nothing
//
// Notes: Here's an example to display "Hello World!" at address (20,20)
//
// LCDPutChar("Hello World!", 20, 20, LARGE, WHITE, BLACK);
//
//
// Author: James P Lynch July 7, 2007
// *************************************************************************************************

void LCDPutStr(char *pString, int x, int y, int Size, int fColor, int bColor) {
	// loop until null-terminator is seen
	while (*pString != 0x00) {
		// draw the character
		LCDPutChar(*pString++, x, y, Size, fColor, bColor);
		// advance the y position
		if (Size == SMALL)
			y = y + 6;
		else if (Size == MEDIUM)
			y = y + 8;
		else
			y = y + 8;
		// bail out if y exceeds 131
		if (y > 131) break;
	}
}

void LCDPutInt(long int nb, int nb_char_min, int x, int y, int Size, int fColor, int bColor) {
	char nb_str[10];
	char chiffre;
	char pos=0;
	int puissance=10; //1

	nb_char_min--; // on ffiche toujours aumoins 1 chiffre

	while(nb/puissance!=0) {
		puissance = puissance*10;
		nb_char_min--;
		}
	puissance = puissance / 10;

	while(nb_char_min>0) {
		nb_char_min--;
		nb_str[pos]=32;
		pos++;
		}
	

	if(nb<0) {
		nb=-nb;
		nb_str[pos]=45; //"-"
		pos++;
	}
	while(puissance>0) {
		chiffre = nb/(puissance); 
		nb_str[pos]= 48 + chiffre;
		pos++;
		nb= nb - chiffre * puissance;
		puissance=puissance/10;
	}	

	nb_str[pos]=0; // fin de chaine
		
	LCDPutStr(nb_str, x, y, Size, fColor, bColor);


}

void LCDPutFloat(float nb, int nb_char_min, int precision, int x, int y, int Size, int fColor, int bColor) {
	char nb_str[10];
	char chiffre;
	char pos=0;
	int puissance=10;

	nb_char_min = nb_char_min - precision - 1 -1 ; // -1 pour le point du float, -1 pour 1 chiffre minimum

	while( (nb/puissance>1) || (nb/puissance<-1) ) {
		puissance = puissance*10;
		nb_char_min--;
		}
	puissance = puissance / 10;

	

	while(nb_char_min>0) {
		nb_char_min--;
		nb_str[pos]=32;	// " "
		pos++;
		}


	if(nb<0) {
		nb=-nb;
		nb_str[pos]=45; //"-"
		pos++;
	}
	while(puissance>0) {
		chiffre = nb/(puissance); 
		nb_str[pos]= 48 + chiffre;
		pos++;
		nb= nb - chiffre * puissance;
		puissance=puissance/10;
	}

	nb_str[pos]=46; // "."	
	pos++;

	while(precision>0)
	{
		nb=nb*10;
		chiffre=(int)nb; // int
		nb_str[pos]= 48 + chiffre;
		nb=nb-chiffre;
		pos++;
		precision--;
	}
	LCDPutInt(0,3,10,10, MEDIUM, YELLOW, BLACK);
	nb_str[pos]=0; // fin de chaine
		
	LCDPutStr(nb_str, x, y, Size, fColor, bColor);


}

// *****************************************************************************
// Delay.c
//
// Simple for loop delay
//
// Inputs: a - loop count
//
// Author: James P Lynch June 27, 2007
// *****************************************************************************

//void Delay (unsigned long a) {
//while (--a!=0);
//}





/* End of file lcd_STR912.c */
