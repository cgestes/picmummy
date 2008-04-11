 /* Xt-6

 Fonction
 */

#include "91x_lib.h"
#include "terminal.h"

/*
extern u8 UART0_TxBuffer[10];
extern u8 UART0_RxBuffer[10];
extern u8 NbrOfDataToTransfer;
extern u8 NbrOfDataToRead;

extern u16 RxCounter;
extern u16 TxCounter ;
extern u8 Terminal_Command;
extern u8 Terminal_Task;
*/

	 

// Retourn la tache à faire

	

void send_int_to_terminal(int nb)
{
	int i;
	char j;

 	if (nb > 9999)
		nb = 0;

	i = nb / 1000;
	j = '0' + i;
	UART_SendData (UART0, j);

	nb = nb - i*1000;
	i= nb / 100;
	j= '0' + i ;
	UART_SendData (UART0, j);

	nb = nb - i* 100 ;
	i = nb / 10;
	j = '0' + i;
	UART_SendData (UART0, j);

	i = nb - i*10;
	j = '0' + i ;
	UART_SendData (UART0, j);

}



void envoie_coord (int X, int Y, int angle )
{
	int i =0;
	char j;
	
	///////////////////////////
	//// X ////////////////////
	///////////////////////////

	while(UART0_Tx_state == UART_BUSY); // On empèche d'écrire plulsieurs données différentes en même temps
	UART0_Tx_state = UART_BUSY;

	UART_SendData (UART0, 'X'); 
	send_int_to_terminal(X);
/*
	//envoie des millièmes
	i= X/1000;
	j= '0' + i;
	UART_SendData (UART0, j);

	//envoie des centièmes
	X= X - i*1000;
	i=+X/100;
	j= '0' + i ;
	UART_SendData (UART0, j);

	X= X - i* 100 ;
	i=X/10;
	j= '0' + i;
	UART_SendData (UART0, j);

	i=X - i*10;
	j= '0' + i ;
	UART_SendData (UART0, j);
	*/
	///////////////////////////
	//// Y ////////////////////
	///////////////////////////
	UART_SendData (UART0, 'Y');
	//envoie des millièmes
	i= Y/1000;
	j= '0' + i;
	UART_SendData (UART0, j);

	//envoie des centièmes
	Y= Y - i*1000;
	i=+Y/100;
	j= '0' + i ;
	UART_SendData (UART0, j);

	Y= Y - i* 100 ;
	i=Y/10;
	j= '0' + i;
	UART_SendData (UART0, j);

	i=Y - i*10;
	j= '0' + i ;
	UART_SendData (UART0, j);
	//////////////////////////
	///// ANGLE //////////////
	//////////////////////////
	UART_SendData (UART0, 'Z');
	//envoie des millièmes
	i= angle/100;
	j= '0' + i;
	UART_SendData (UART0, j);

	//envoie des centièmes
	angle= angle - i*100;
	i=+angle/10;
	j= '0' + i ;
	UART_SendData (UART0, j);

	angle= angle - i* 10 ;
	j= '0' + angle;
	UART_SendData (UART0, j);

	UART0_Tx_state = UART_AVAILABLE;

}


/* End of file terminal.c */
