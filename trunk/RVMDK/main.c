/*
* File Name          : main.c
* Author             : Xt-6
* Date First Issued  : 03/02/2008 : Version 1.0
* Description        : Main program body
********************************************************************************
* History:
*
*******************************************************************************/

#include "91x_lib.h"
#include "declare.h" // déclaration des variables globales


#ifdef LOG_MAIN
# define log(...) { d(__VA_ARGS__); }
#else
# define log(...) ;
#endif
 
 int main()
{
	int i, tmp;

	Globali=0;
	initialisation ();
	Init_PathFinding();

	//Depart(); //procédure de départ avec le jack	
	Position_Depart.X = 45;
	Position_Depart.Y = 45;
	Position_Destination.X = 255;
	Position_Destination.Y = 45;
	Position_Adverse.X = 150;
	Position_Adverse.Y = 45;

	log("\r\nStarting MAIN()\r\n");
	while(1)
	{
		int pos = 30;
		/* Get the conversion value */
		//Globali++;
		//LCD_Debug_String("Start");
	
		//PathFinding(Point_Depart, Point_Destination, Point_Adverse, &PointPassage);

		//LCDPutInt(PointPassage.TailleListe, 8, 90, 50, MEDIUM, YELLOW, BLACK);
		
		LCDPutInt(PobCouleur, 8, 90, 50, MEDIUM, YELLOW, BLACK);
		LCDPutInt(Globali, 8, 110, 50, MEDIUM, YELLOW, BLACK);
		tmp = read_Memory_Sizeof(BARILLET_RETURN_KEY, MEMORY_WAIT);
		LCDPutInt(tmp, 8, 100, 50, MEDIUM, GREEN, BLACK);
		LCDPutInt(Global_temps, 8, 120, 50, MEDIUM, BLUE, BLACK);


		// display the value of each IR sensor on the LCD
		for (i = 0; i < 5; i++)
		{
		  int c = read_Memory(IR_C_KEY, i, MEMORY_WAIT);
		  LCDPutInt(c, 8, pos, 50, MEDIUM, WHITE, BLACK); 
		  pos += 10;
		}
		//wait til the end of acquision to start a new loop
		//wait_fin_TE();
	}
	
}
