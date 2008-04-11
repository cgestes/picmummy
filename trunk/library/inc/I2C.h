/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : I2C.h
* Author             : UTC E=M6 Team
* Date First Issued  : 05/02/08 : Version 1.0
* Description        : I2C commandes and features.
********************************************************************************/



#include "91x_type.h"


#define I2C_MyAdress 				0xA8

#define I2C_ServoAdress 			54
#define I2C_AsservissementAdress 	32
#define	I2C_BarilletAdress			0x40

// servo de test (numéro 0)
#define Servo_Test		0
#define Servo_Test_pos1	10
#define Servo_Test_pos2	150



#define I2C_FREE 0
#define I2C_BUSY 1


#define I2C0_BUFFER_SIZE 4

#define I2C0_GLOBAL_BUFFER_TX_SIZE 	20
#define I2C0_LOCAL_BUFFER_SIZE 		10


extern u8 I2C0_Global_Buffer_Tx[I2C0_GLOBAL_BUFFER_TX_SIZE][I2C0_LOCAL_BUFFER_SIZE];
extern u8 I2C0_Local_Buffer_Tx_Size[I2C0_GLOBAL_BUFFER_TX_SIZE];
extern u8 I2C0_Local_Buffer_Tx_Adress[I2C0_GLOBAL_BUFFER_TX_SIZE];
extern u8 I2C0_Global_Buffer_Tx_Position;
extern u8 I2C0_Global_Buffer_Tx_Current;
extern u8 I2C0_Local_Buffer_Tx_Position;
extern u8 I2C0_Tx_Idx, I2C0_Rx_Idx, I2C0_Slave_Adress, I2C0_Direction;
extern u8 I2C0_Buffer_Tx[I2C0_LOCAL_BUFFER_SIZE], I2C0_Buffer_Rx[I2C0_LOCAL_BUFFER_SIZE];
extern u8 I2C0_State;

extern u8 I2C0_State;
extern u8 I2C0_ReadState;
extern u32 I2C0_ReadTemp;

//void I2C0_Add_Buffer(u8 data);
//void I2C0_Send_Buffer(u8 adress);


void I2C0_Add_message(int pSlave, int RW,int pRepeat,int pCommand,int pMemoryKey);

void I2C0_Start_Message (void);

void I2C0_PostTraitement(void);

/* Brochage GP2Y0D02YK (80cm Num)

	  __	__
     |	|__|  |	     1 = Vo
	 |  |  |  |		 2 = GND
	/  1 2 3   \	 3 = VCC
	------------
*/

/* End of file I2C.h */

