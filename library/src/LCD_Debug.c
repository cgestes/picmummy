// UTC 2008 - Ti
// STR-E912 Olimex
// Foncions de debug utilisant l'écran LCD (132x132)
// librairies utilisées :
//		- LCD_STR912 : librairie des fonctions basiques

// includes
#include "LCD_Debug.h"

int LCD_position_gch = 2;
int LCD_position_drt = 2;		

void LCD_Debug_Int_Left (int entier, int nb_char_min)
{ 
	int i =0;
	for (i=0; i<nb_char_min+1; i++ )
		{
		LCDPutStr( " ", LCD_position_gch, 1, MEDIUM, YELLOW, BLACK); 
		}
	LCDPutInt(entier, nb_char_min,LCD_position_gch,1, MEDIUM, YELLOW, BLACK);
		  
	LCD_position_gch = LCD_position_gch +10;
	if ( LCD_position_gch > 131)
		  	LCD_position_gch = 2;
}

void LCD_Debug_Int_Right (int entier, int nb_char_min)
{ 
	int i =0;
	for (i=0; i<nb_char_min+1; i++ )
	{
		LCDPutStr( " ", LCD_position_gch, 1, MEDIUM, YELLOW, BLACK); 
	}
	LCDPutInt(entier, nb_char_min,LCD_position_drt,130-nb_char_min, MEDIUM, YELLOW, BLACK);
		  
	LCD_position_drt = LCD_position_drt + 10 ;
	if ( LCD_position_drt > 131)
		  	LCD_position_drt = 2;
}

void LCD_Debug_String (char *pString)
{
	LCDPutStr( "                ", LCD_position_gch, 1, MEDIUM, YELLOW, BLACK); 
		
	LCDPutStr( pString, LCD_position_gch, 1, MEDIUM, YELLOW, BLACK);	  
	LCD_position_gch = LCD_position_gch +10;
	if ( LCD_position_gch > 70) // 131
		  LCD_position_gch = 1;
}

void LCD_Debug_Float_Left ( float nb, int nb_char_min, int precision)
{
	int i =0;
	for (i=0; i<nb_char_min+1; i++ )
	{
		LCDPutStr( " ", LCD_position_gch, 1, MEDIUM, YELLOW, BLACK); 
	}

	LCDPutFloat(nb,nb_char_min,precision, LCD_position_gch, 1, MEDIUM, YELLOW, BLACK);

	LCD_position_gch = LCD_position_gch + 10 ;
	if ( LCD_position_gch > 131)
		  	LCD_position_gch = 2;
}

void LCD_Debug_Float_Right ( float nb, int nb_char_min, int precision)
{
	int i =0;
	for (i=0; i<nb_char_min+1; i++ )
	{
		LCDPutStr( " ", LCD_position_drt, 1, MEDIUM, YELLOW, BLACK); 
	}

	LCDPutFloat(nb, nb_char_min, precision, LCD_position_drt, 1, MEDIUM, YELLOW, BLACK);

	LCD_position_drt = LCD_position_drt + 10 ;
	if ( LCD_position_drt > 131)
		  	LCD_position_drt = 2;
}

#include <stdio.h>
#include <stdarg.h>
#include "91x_lib.h"
#include "lcd_STR912.h"
#include "log.h"				   


void d_LCD(const char *format, ...)
{
  char tmp[256];
  char *ptr = tmp;
  va_list args;

  va_start(args, format);
  vsprintf(tmp, format, args);
  
  LCD_Debug_String (ptr);
  
  va_end(args);
}

void LCD_Afficher_Font(void)
{
 	fillWin(setWin(0,0,131,131),0); // Font noir
	sDelay(10000);	
	LCDSetLine(0, 70, 131, 70, BLUE); // ligne de séparation
	LCDSetLine(90, 70, 90, 131, BLUE); // ligne de séparation
	LCDSetLine(0, 69, 131, 69, BLUE); // ligne de séparation
	LCDSetLine(91, 70, 91, 131, BLUE); // ligne de séparation
	// Texte :
	LCDPutStr("X =", 71, 2, SMALL, WHITE, BLACK);
	LCDPutStr("Y =", 71, 45, SMALL, WHITE, BLACK);
	LCDPutStr("O =", 81, 2, SMALL, WHITE, BLACK);
	LCDPutStr("Xa=",91, 2, SMALL, YELLOW, BLACK);
	LCDPutStr("Ya=", 91, 45, SMALL,YELLOW, BLACK);
	LCDPutStr("Sy :", 101, 2, MEDIUM, WHITE, BLACK);
	LCDPutStr("i =", 111, 2, MEDIUM, PINK, BLACK);
	LCDPutStr("T =", 121, 2 , MEDIUM, GREEN, BLACK);
	LCDPutStr("'", 121, 50 , MEDIUM, GREEN, BLACK);
}

void LCD_MAJ_Affichage(void)
{
	int tps;
	int i;
	// Effacer les anciens textes
	LCDPutStr("    ", 71, 20, SMALL, WHITE, BLACK);
	LCDPutStr("    ", 71, 63, SMALL, WHITE, BLACK);
	LCDPutStr("    ", 81, 20, SMALL, WHITE, BLACK);
	LCDPutStr("    ",91, 20, SMALL, YELLOW, BLACK);
	LCDPutStr("    ", 91, 63, SMALL,YELLOW, BLACK);
	LCDPutStr("     ", 101, 34, MEDIUM, WHITE, BLACK);
	LCDPutStr("     ", 111, 26, MEDIUM, PINK, BLACK);
	LCDPutStr("   ", 121, 26 , MEDIUM, GREEN, BLACK);
	LCDPutStr("   ", 121, 58 , MEDIUM, GREEN, BLACK);

 	// MAJ des textes
	LCDPutInt(read_Memory_Sizeof(ASS_COORDONEES_X_KEY, MEMORY_WAIT), 4, 71, 20, SMALL, WHITE, BLACK);
	LCDPutInt(read_Memory_Sizeof(ASS_COORDONEES_Y_KEY, MEMORY_WAIT), 4, 71, 65, SMALL, WHITE, BLACK);
	LCDPutInt(read_Memory_Sizeof(ASS_ORIENTATION_KEY, MEMORY_WAIT), 4, 81, 20, SMALL, WHITE, BLACK);
	LCDPutInt(read_Memory_Sizeof(ADVERSE_X_KEY, MEMORY_WAIT), 4, 91, 20, SMALL, WHITE, BLACK);
	LCDPutInt(read_Memory_Sizeof(ADVERSE_Y_KEY, MEMORY_WAIT), 4, 91, 65, SMALL, WHITE, BLACK);
	LCDPutStr("....", 45, 101, MEDIUM, WHITE, BLACK); // Stratégie = Strategy_Name
	
	LCDPutInt(Globali, 5, 111, 2, MEDIUM, PINK, BLACK);
	tps = Global_temps/100;
	LCDPutInt(tps, 3, 121, 26, MEDIUM, GREEN, BLACK);
	tps=Global_temps-tps*100;
	LCDPutInt(tps, 3, 121, 58, MEDIUM, GREEN, BLACK);

	// Graphique
		// IR

	for(i=0;i<4;i++)
	{
	 	tps = read_Memory(IR_C_KEY, i, MEMORY_WAIT);
		LCDSetRect(75, 91, 85, (91+tps>>2), FILL, RED);
		LCDSetRect(75+i*5, 91, 80+i*5, (91+70- ((70-tps)>>2)), FILL, BLACK);
	}
		// Barillet
	tps = read_Memory_Sizeof(NBBALLE_TOTAL_KEY, MEMORY_WAIT);
	LCDPutInt(tps, 1, 105, 91, MEDIUM, YELLOW, BLACK);
	for(i=0;i<5;i++)
	{
	 	switch (Barillet[i])
		{
			case COULEUR_VIDE :
				LCDSetRect(105, 100+i*6, 110,105+i*6, FILL, BLACK);
				break;
			case COULEUR_ROUGE :
				LCDSetRect(105, 100+i*6, 110,105+i*6, FILL, RED);
				break;
			case COULEUR_BLEU :
				LCDSetRect(105, 100+i*6, 110,105+i*6, FILL, BLUE);
				break;
			case COULEUR_BLANCHE :
				LCDSetRect(105, 100+i*6, 110,105+i*6, FILL, WHITE);	
				break;
			default :
				break;
		}
	}

	// PobEye
		 	switch (read_Memory_Sizeof(POBEYE_BALLE_KEY, MEMORY_WAIT))
		{
			case COULEUR_VIDE :
				LCDSetRect(115, 95, 125, 105, FILL, BLACK);
				break;
			case COULEUR_ROUGE :
				LCDSetRect(115, 95, 125, 105, FILL, RED);
				break;
			case COULEUR_BLEU :
				LCDSetRect(115, 95, 125, 105, FILL, BLUE);
				break;
			case COULEUR_BLANCHE :
				LCDSetRect(115, 95, 125, 105, FILL, WHITE);	
				break;
			default :
				break;
		}
	LCDSetRect(105, 100+i*6, 110,105+i*6, FILL, BLACK);
	LCDSetRect(105, 100+i*6, 110,105+i*6, FILL, BLACK);



	//void LCDSetRect(int x0, int y0, int x1, int y1, unsigned char fill, int color)

}


/* End of file LCD_debug.c */
