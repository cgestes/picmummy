// UTC 2008 - Ti
// STR-E912 Olimex
// Foncions de debug utilisant l'écran LCD (132x132)
// librairies utilisées :
//		- LCD_STR912 : librairie des fonctions basiques

#include "lcd_STR912.h"

#ifndef _LCD_Debug
#define _LCD_Debug


//definition de constante de controle


//appel des variable globale de controle de la position du texte

void LCD_Debug_Int_Left (int entier, int nb_char_min);
void LCD_Debug_Int_Right (int entier, int nb_char_min);
void LCD_Debug_String (char *pString);
void LCD_Debug_Float_Left ( float nb, int nb_char_min, int precision);
void LCD_Debug_Float_Right ( float nb, int nb_char_min, int precision);
void d_LCD(const char *format, ...);

void LCD_Afficher_Font(void);
void LCD_MAJ_Affichage(void);




#endif


/* End of file LCD_debug.h*/
