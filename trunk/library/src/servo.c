/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : servo.c
* Author             : UTC E=M6 Team
* Date First Issued  : 13/02/08 : Version 1.0
* Description        : Servo motor fonctions.
********************************************************************************/

/*
Fonctions utilisant les servo moteurs
*/

#include "servo.h"


void load_all_servos(void)
{
	int i,j;
	s32	val;
	for(i=0; i<NB_SERVO; i++)
	{
		for(j=0; j<NB_POSITIONS_SERVO; j++)
		{
			val = Read_Servo(i,j);
			if(val<0)  // lecture d'une adresse sans valeur =-1 par defaut dans la flash
				val=0;
			tab_servo[i].position[j] = val;
		}
		//change_servo(i, j, tab_servo[i].position[0]);
		write_Memory_Sizeof(SERVO_BASE_KEY + i, tab_servo[i].position[0]);
	}
}

void save_all_servos(void)
{
	int i,j;
	
	LCDPutStr("Write Flash     ", 10, 10, MEDIUM , YELLOW, BLACK);
	Erase_Bank(); // ON NE SAUVEGARDE QUE LES SERVOS POUR L'INSTANT
	
	for(i=0; i<NB_SERVO; i++)
	{
		for(j=0; j<NB_POSITIONS_SERVO; j++)
		{
			Write_Servo(i, j, tab_servo[i].position[j]);
		}
	}
	LCDPutStr("Write Flash OK", 10, 10, MEDIUM , YELLOW, BLACK);
}


void config_servo(u8 num, u8 pos, u16 value)
{
	tab_servo[num].position[pos] = value;
	tab_servo[num].current = pos;
	
	write_Memory_Sizeof(SERVO_BASE_KEY + num, value); 
}

void move_servo(u8 num, u8 pos) // On est en Repeat
{
 	write_Memory_Sizeof(SERVO_BASE_KEY + num, tab_servo[num].position[pos]);
}

/* End of file servo.c */
