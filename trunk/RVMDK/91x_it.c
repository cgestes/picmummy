/******************** (C) COPYRIGHT 2006 STMicroelectronics ********************
* File Name          : 91x_it.c
* Author             : MCD Application Team
* Date First Issued  : 05/18/2006 : Version 1.0
* Description        : Main Interrupt Service Routines.
********************************************************************************
*    This file can be used to describe all the exceptions subroutines
*    that may occur within user application.
*    When an interrupt happens, the software will branch automatically
*    to the corresponding routine according to the interrupt vector
*    loaded in the PC register.
*    The following routines are all empty, user can write code for
*    exceptions handlers and peripherals IRQ interrupts.
********************************************************************************
* History:
* 05/22/2007 : Version 1.2
* 05/24/2006 : Version 1.1
* 05/18/2006 : Version 1.0
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH  
* CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS 
* A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
* OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
* CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#include "91x_it.h"
#include "I2C.h"
#include "terminal.h"
//#include "serial_message.h"
//#include "memory.h"

#ifdef LOG_TIMER
# define log(...) { d(__VA_ARGS__); }
#else
# define log(...) ;
#endif


/*******************************************************************************
* Function Name  : Undefined_Handler
* Description    : This function Undefined instruction exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Undefined_Handler(void)
{
	d("EXECEPTION: UNDEFINED\r\n");
	while(1)
	  ;
}
/*******************************************************************************
* Function Name  : SWI_Handler
* Description    : This function handles SW exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SWI_Handler(void)
{
	d("EXECEPTION: SWI\r\n");
	while(1)
	  ;
}
/*******************************************************************************
* Function Name  : Prefetch_Handler
* Description    : This function handles preftetch abort exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Prefetch_Handler(void)
{
	d("EXECEPTION: Prefetch\r\n");
	while(1)
	  ;
}
/*******************************************************************************
* Function Name  : Abort_Handler
* Description    : This function handles data abort exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Abort_Handler(void)
{
	d("EXECEPTION: Abort\r\n");
	while(1)
	  ;
}
/*******************************************************************************
* Function Name  : FIQ_Handler
* Description    : This function handles FIQ exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FIQ_Handler(void)
{
}
/*******************************************************************************
* Function Name  : WDG_IRQHandler
* Description    : This function handles the WDG interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WDG_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : SW_IRQHandler
* Description    : This function handles the SW interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SW_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : ARMRX_IRQHandler
* Description    : This function handles the ARMRX interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARMRX_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : ARMTX_IRQHandler
* Description    : This function handles the ARMTX interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARMTX_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : TIM0_IRQHandler
* Description    : This function handles the TIM0 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM0_IRQHandler(void)
{	

/* COMMUNICATION I2C */

	if(liste_serial[SERIAL_I2C0].state == SERIAL_BUG)
	{
		I2C_Cmd(I2C0, ENABLE);
		liste_serial[SERIAL_I2C0].state = SERIAL_FREE;
	}
	if(liste_serial[SERIAL_I2C0].state == SERIAL_FREE)
	{
		repeat_serial_list(&liste_serial[SERIAL_I2C0]);
		if(liste_serial[SERIAL_I2C0].size>0)
		{
			I2C0_Start_Message();
		}
	}
	else // L'I2C a buggé
	{ // On fait une pause d'un cycle du timer (50ms)
	  log("I2C: Bug\r\n");
	  I2C0_ReadState = 0;
      // Send STOP Condition
	  //I2C_Cmd(I2C0, DISABLE);
      I2C_GenerateSTOP(I2C0, ENABLE);
	  liste_serial[SERIAL_I2C0].state = SERIAL_BUG;
	}

/* TRAITEMENTS POST I2C */

	I2C0_PostTraitement();

/* POBEYE */

	if(Barillet_Mode == Barillet_AUTOMATIQUE)
	{
		//Pobeye_TraiterBalles();
	}

/* BARILLET */

//	Barillet_MachineEtat();

/* INFRAROUGES */

	IR_Lecture();


	TIM0->OC1R = TIM0->OC1R + TIM0_TE;

	Global_temps +=5; // 0,05 seconde
	Globali++;
	d("Globali=%d",Globali);		  
	TIM_ClearFlag(TIM0, TIM_FLAG_OC1);// On remez le flag à 0
	Fin_TE=1; // Signal au main la MAJ


}
/*******************************************************************************
* Function Name  : TIM1_IRQHandler
* Description    : This function handles the TIM1 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles the TIM2 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles the TIM3 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : USBHP_IRQHandler
* Description    : This function handles the USBHP interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBHP_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : USBLP_IRQHandler
* Description    : This function handles the USBLP interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBLP_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : SCU_IRQHandler
* Description    : This function handles the SCU interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SCU_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : ENET_IRQHandler
* Description    : This function handles the ENET interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENET_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : DMA_IRQHandler
* Description    : This function handles the DMA interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : CAN_IRQHandler
* Description    : This function handles the CAN interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : MC_IRQHandler
* Description    : This function handles the MC interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MC_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : ADC_IRQHandler
* Description    : This function handles the ADC interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : UART0_IRQHandler
* Description    : This function handles the UART0 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART0_IRQHandler(void) // Liaison série avec le terminal
{
	u32 tmp;
	u8 data_rx=0;

	do
	{
		data_rx=UART_ReceiveData(UART0); // reception d'un caractère	
			
			if(data_rx != '#') // le '#" est utilisé pour remplir la fifo
			{
				
	
				if(NbrOfDataToRead==0) // On attend une commmande
				{
					Term_Command = data_rx;
					//Terminal_Commandes();

					Term_Task = NO_TASK; // Par défaut, on ne fait pas de tache en plus
					switch(Term_Command)
					{
						case COM_INIT :
							initialisation ();
							break;
				
						case COM_SERVO :
							NbrOfDataToRead=6; // demande une lecture de 6 caractères avant de lancer la tache TASK_SERVO
							Term_Task = TASK_SERVO;
							break;
				
						case COM_SAVE_FLASH :
							save_all_servos();
							break;
				
						case COM_READ_SERVO :
							NbrOfDataToRead=2;
							Term_Task = TASK_READ_SERVO;
							break;
				
						default :
							break;
					 }

					RxCounter = 0;
				}
				else
				{
					UART0_RxBuffer[RxCounter] = data_rx - '0'; // On lit une donnée (nombres)
					RxCounter++;						// On enlève le caractère '0'
					NbrOfDataToRead--;
					if(NbrOfDataToRead==0)
					{
					 	//Terminal_Task();
						switch(Term_Task)
						{
							case TASK_SERVO :	  	
								tmp = UART0_RxBuffer[2]*1000 + UART0_RxBuffer[3]*100 + UART0_RxBuffer[4]*10 + UART0_RxBuffer[5];
								config_servo(UART0_RxBuffer[0], UART0_RxBuffer[1], tmp);		
								break;
							
							case TASK_READ_SERVO :
								while(UART0_Tx_state == UART_BUSY); // On empèche d'écrire plusieurs données différentes en même temps
								UART0_Tx_state = UART_BUSY;
								UART_SendData (UART0, 'J'); //ACK	  	
								UART_SendData (UART0, (UART0_RxBuffer[0]+'0') ); // num
								UART_SendData (UART0, (UART0_RxBuffer[1]+'0') ); // position
								send_int_to_terminal(tab_servo[UART0_RxBuffer[0]].position[UART0_RxBuffer[1]]);	
								UART0_Tx_state = UART_AVAILABLE;
								move_servo(UART0_RxBuffer[0], UART0_RxBuffer[1]);
								break;
					
							default :
								break;
						}	
					}
				}	
			}
	} while ( (UART0->FR & 0x10) != 0x10);	// on traite la fifo tant qu'elle n'est pas vide	

	
	UART_ClearITPendingBit(UART0, UART_IT_Receive);// On lève l'interruption
}
/*******************************************************************************
* Function Name  : UART1_IRQHandler
* Description    : This function handles the UART1 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : UART2_IRQHandler
* Description    : This function handles the UART2 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART2_IRQHandler(void)
{
	int tmp;
	tmp = UART_ReceiveData(UART2); // reception d'un caractère
	write_Memory_Sizeof(POBEYE_BALLE_KEY, tmp&0x0F);
	UART_ClearITPendingBit(UART2, UART_IT_Receive);// On lève l'interruption
}
/*******************************************************************************
* Function Name  : I2C0_IRQHandler
* Description    : This function handles the I2C0 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C0_IRQHandler(void)
{

	int key_index=0;
	u32 mot_32;
	int reste=0;

  d("I2C0_ReadState = %d \r\n",I2C0_ReadState);
  switch (I2C_GetLastEvent(I2C0))
  {
    case I2C_EVENT_MASTER_MODE_SELECT:             // EV5
		d("New message I2C0 \r\n");
		if(liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].RW == SERIAL_WRITE)
			{
			I2C_Send7bitAddress(I2C0, liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].slave , I2C_MODE_TRANSMITTER);
			}
		else // READ
		  	if(I2C0_ReadState == 0)
				I2C_Send7bitAddress(I2C0, liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].slave , I2C_MODE_TRANSMITTER);
			else
			{
				reste = gMemory[liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].memoryKey].size&MEMORY_SIZE;
				if ( reste == 1 )
			    {
			    	I2C_AcknowledgeConfig (I2C0, DISABLE); // pas de ACK lors de la prochaine réception, mais STOP
			    
				}
				I2C_Send7bitAddress(I2C0, liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].slave , I2C_MODE_RECEIVER);
			}
	  liste_serial[SERIAL_I2C0].state = SERIAL_BUSY;
      break;

    case I2C_EVENT_MASTER_MODE_SELECTED:           // EV6
      // Clear EV6 by set again the PE bit
      I2C0->CR |=  0x20;
	  I2C_SendData(I2C0,liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].command); // On envoie un mot de commande
      break;

    case I2C_EVENT_MASTER_BYTE_TRANSMITTED:         // EV8
      
	  if(liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].RW == SERIAL_WRITE)
	  {
		if(liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].index == (gMemory[liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].memoryKey].size&MEMORY_SIZE))
		{// on a fini d'envoyer les octets pour une donnée
			I2C_GenerateSTOP (I2C0, ENABLE);
			liste_serial[SERIAL_I2C0].position++;
			if(liste_serial[SERIAL_I2C0].position < (liste_serial[SERIAL_I2C0].size&MEMORY_SIZE)) // il reste encore des données à transmettre
			{
				I2C_ITConfig(I2C0, ENABLE);
				I2C_GenerateStart (I2C0, ENABLE);
			}
			else
			{
				liste_serial[SERIAL_I2C0].state = SERIAL_FREE;
			}
		}
		else // Il reste encore des octets à transmettre pour la donnée courante
		{
		  	key_index =  liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].memoryKey; // lecture de l'adresse dans g_memory
			mot_32 = read_Memory(key_index, liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].index, MEMORY_WAIT); // On décale la donnée pour envoyer seulement 1 octet
			I2C_SendData(I2C0, mot_32);//EV8 just after EV6
			liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].index++;
		}		  

	  }
	  else // on souhaite lire une donnée
	  {
	  		I2C0_ReadState = 1;
			I2C0_ReadTemp = 0; // utilisé comme tampon dans l'écriture de g_memory
			I2C_GenerateSTOP (I2C0, ENABLE);
			I2C_ITConfig(I2C0, ENABLE);
			I2C_GenerateStart (I2C0, ENABLE);
	  }
      break;

    case I2C_EVENT_MASTER_BYTE_RECEIVED:           // EV7	
			
		/*if(liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].RW == SERIAL_WRITE)
		{	 // On ne souhaite pas recevoir de données pour un message en écriture mais on recoit quand même une donnée
			// relance l'I2C avec le message suivant, s'il y en a un
			I2C0_ReadState = 0;
        	// Send STOP Condition
        	I2C_GenerateSTOP(I2C0, ENABLE);
			I2C_AcknowledgeConfig (I2C0, ENABLE);
			liste_serial[SERIAL_I2C0].position++;
			if(liste_serial[SERIAL_I2C0].position < liste_serial[SERIAL_I2C0].size) // il reste encore des données à transmettre
			{
				I2C_ITConfig(I2C0, ENABLE);
				I2C_GenerateStart (I2C0, ENABLE);
			}
			else
			{
				liste_serial[SERIAL_I2C0].state = SERIAL_FREE;
			}			
			break; 
		}*/
			// On calcul combien d'octets il reste a recevoir
		    
			mot_32 = I2C_ReceiveData(I2C0);
			if(I2C0_ReadState == 1)
			{
				key_index =  liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].memoryKey;
				write_Memory(key_index, liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].index, mot_32);
				liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].index ++;	
				//if( (mot_32 !=0) && (mot_32 != 255))
				//	Globali=reste ;//mot_32*10 + gMemory[liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].memoryKey].size; 
				//Globali = mot_32;						
				reste = (gMemory[liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].memoryKey].size&MEMORY_SIZE) - liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].index;

				if ( reste == 1 )
		      	{
		        	I2C_AcknowledgeConfig (I2C0, DISABLE); // pas de ACK lors de la prochaine réception, mais STOP
		      	}
		      	if ( reste == 0 )  // On a recu une donnée en entière
		      	{	
					//Globali = liste_serial[SERIAL_I2C0].position; //liste_serial[SERIAL_I2C0].message[liste_serial[SERIAL_I2C0].position].index;
					
					I2C0_ReadState = 2;
		        	// Send STOP Condition
					I2C_ITConfig(I2C0, ENABLE);
					I2C_AcknowledgeConfig (I2C0, ENABLE);
		        	I2C_GenerateSTOP(I2C0, ENABLE);
					liste_serial[SERIAL_I2C0].position++;
		      	}
			  } // ReadState = 1
			  else // ReadState = 2
			  {
					I2C0_ReadState = 0;
			  		//I2C_ITConfig(I2C0, ENABLE);
					//I2C_AcknowledgeConfig (I2C0, ENABLE);
		        	//I2C_GenerateSTOP(I2C0, ENABLE);
					if(liste_serial[SERIAL_I2C0].position < liste_serial[SERIAL_I2C0].size) // il reste encore des données à transmettre
					{
						I2C_ITConfig(I2C0, ENABLE);
						I2C_GenerateStart (I2C0, ENABLE);
					}
					else
					{
						liste_serial[SERIAL_I2C0].state = SERIAL_FREE;
					}
				}

		break;
    default:
      break;
  }	
}
/*******************************************************************************
* Function Name  : I2C1_IRQHandler
* Description    : This function handles the I2C1 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : SSP0_IRQHandler
* Description    : This function handles the SSP0 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP0_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : SSP1_IRQHandler
* Description    : This function handles the SSP1 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : LVD_IRQHandler
* Description    : This function handles the LVD interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LVD_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles the RTC interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : WIU_IRQHandler
* Description    : This function handles the WIU interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WIU_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXTIT0_IRQHandler
* Description    : This function handles the EXTIT0 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTIT0_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXTIT1_IRQHandler
* Description    : This function handles the EXTIT1 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTIT1_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXTIT2_IRQHandler
* Description    : This function handles the EXTIT2 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTIT2_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : EXTIT3_IRQHandler
* Description    : This function handles the EXTIT3 interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTIT3_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : USBWU_IRQHandler
* Description    : This function handles the USBWU interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWU_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : PFQBC_IRQHandler
* Description    : This function handles the PFQBC interrupt request
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PFQBC_IRQHandler(void)
{
}

/******************* (C) COPYRIGHT 2006 STMicroelectronics *****END OF FILE****/
