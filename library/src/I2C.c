/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : I2C.c
* Author             : UTC E=M6 Team
* Date First Issued  : 05/02/08 : Version 1.0
* Description        : PathFinding fonctions.
********************************************************************************/

#include "91x_lib.h"
#include "I2C.h"
#include "serial_message.h"

/*
void I2C0_Add_Buffer(u8 data)
{
	  	I2C0_Global_Buffer_Tx[I2C0_Global_Buffer_Tx_Position][I2C0_Local_Buffer_Tx_Size[I2C0_Global_Buffer_Tx_Position]] = data;
		I2C0_Local_Buffer_Tx_Size[I2C0_Global_Buffer_Tx_Position]++;
}

void I2C0_Send_Buffer(u8 adress)
{

	if(I2C0_State == I2C_FREE)
	{
	  	I2C0_State = I2C_BUSY ;
	  	I2C0_Direction = I2C_MODE_TRANSMITTER;
	  	I2C0_Local_Buffer_Tx_Position = 0;
	  	I2C0_Global_Buffer_Tx_Current = I2C0_Global_Buffer_Tx_Position;

		I2C0_Global_Buffer_Tx_Position++;
		if (I2C0_Global_Buffer_Tx_Position >= I2C0_GLOBAL_BUFFER_TX_SIZE)
			I2C0_Global_Buffer_Tx_Position=0;
		I2C0_Local_Buffer_Tx_Size[I2C0_Global_Buffer_Tx_Position]=0; // RAZ du buffer local

	  	I2C0_Slave_Adress=adress;
	  	I2C_ITConfig(I2C0, ENABLE);
	  	I2C_GenerateStart(I2C0, ENABLE);
	}
	else
	{
		I2C0_Local_Buffer_Tx_Adress[I2C0_Global_Buffer_Tx_Position] = adress;
		I2C0_Global_Buffer_Tx_Position++;
		if (I2C0_Global_Buffer_Tx_Position >= I2C0_GLOBAL_BUFFER_TX_SIZE)
			I2C0_Global_Buffer_Tx_Position=0;
		I2C0_Local_Buffer_Tx_Size[I2C0_Global_Buffer_Tx_Position]=0; // RAZ du buffer local
	}


} */

void I2C0_Add_message(int pSlave, int RW,int pRepeat,int pCommand,int pMemoryKey)
{	
	add_serial_message(&liste_serial[SERIAL_I2C0], pSlave, RW, pRepeat, pCommand, pMemoryKey);

	if(liste_serial[SERIAL_I2C0].state == SERIAL_FREE)
	{
	  	liste_serial[SERIAL_I2C0].state = SERIAL_BUSY;
	  	I2C_ITConfig(I2C0, ENABLE);
		I2C_GenerateStart(I2C0, ENABLE);
	}
}

void I2C0_Start_Message(void)
{
if(liste_serial[SERIAL_I2C0].state == SERIAL_FREE)
	{
	  	liste_serial[SERIAL_I2C0].state = SERIAL_BUSY;
	  	I2C_ITConfig(I2C0, ENABLE);
		I2C_GenerateStart(I2C0, ENABLE);
	}
}

void I2C0_PostTraitement(void)
{

	// On met à jour les variables (globales et gMemory) en fonction de ce qui a été lu sur l'I2C

	// Barillet:
	if(read_Memory_Sizeof(BARILLET_RETURN_KEY, MEMORY_WAIT) == BarPosition)
	{
		BarState = BARILLET_FREE;
	}
}


/* End of file I2C.c */
