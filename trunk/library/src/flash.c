/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : flash.c
* Author             : UTC E=M6 Team
* Date First Issued  : 05/02/08 : Version 1.0
* Description        : Flash commands.
********************************************************************************/

#include "91x_lib.h"

//effacer la bank utilisée dans la flash pour sauvegarder des valeurs
void Erase_Bank(void)
{
	FMI_EraseSector(FMI_B1S0);
  	FMI_WaitForLastOperation(FMI_BANK_1, TIMEOUT);
}


// écrire une donnée dans la flash
// Demande un effacement de la bank avant

void Write_Flash(u32 adr, u32 data)
{
	u16 tmp;

	tmp = data;	//LSB	

 	FMI_WriteHalfWord((BASE_FMI + adr*4),tmp);
  	FMI_WaitForLastOperation(FMI_BANK_1, TIMEOUT_WRITE);

	data = data>>16;
	tmp = data; //MSB

 	FMI_WriteHalfWord( (BASE_FMI + adr*4 + 2),tmp);
  	FMI_WaitForLastOperation(FMI_BANK_1, TIMEOUT_WRITE);
}

// lire un 32bits en flash
u32 Read_Flash(u32 adr)
{
	u32 val;
	val = FMI_ReadWord(BASE_FMI + adr*4);
	FMI_WaitForLastOperation(FMI_BANK_1,TIMEOUT_READ);
	return val;
}

// ecrire en flash la position d'un servomoteur
void Write_Servo(u32 num, u32 position, u32 val)
{
	u32 adr;
	adr = BASE_SERVO + num*5 + position;
	Write_Flash(adr, val);
}

// lire en flash la position d'un servomoteur
u32 Read_Servo(u32 num, u32 position)
{
	u32 adr;
	adr = BASE_SERVO + num*5 + position;
	return 	Read_Flash(adr);
}


/* End of file flash.c */
