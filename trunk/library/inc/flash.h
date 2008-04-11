/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : flash.h
* Author             : UTC E=M6 Team
* Date First Issued  : 05/02/08 : Version 1.0
* Description        : Flash commands.
********************************************************************************/

#define BASE_FMI	0x80000


#define BASE_SERVO	0 // 10 servos, 5 positions => fin = 50 
#define BASE_ASSER	50


/* 	Pour faire une écritue, on est obligé d'effacer la bank avant.
	Si l'on veut sauvegarder plusieurs données dans une même bank,
	il faut charger toutes les données avant de reprogrammer toutes les nouvelles. */

void Erase_Bank(void);

void Write_Flash(u32 adr, u32 data);

u32 Read_Flash(u32 adr);

void Write_Servo(u32 num, u32 position, u32 val);

u32 Read_Servo(u32 num, u32 position);



/* End of file flash.h */
