/* Terminal Série */


#ifndef __TERMINAL_H
#define __TERMINAL_H

#define COORD_X 0
#define COORD_Y 1


// Commandes :
#define NO_COM	0
#define COM_INIT		'I'
#define COM_SAVE_FLASH	'S'
#define COM_SERVO		's'
#define COM_READ_SERVO	'J'


// Taches :
#define NO_TASK				0
#define TASK_SERVO			1
#define TASK_READ_SERVO		2


#define RxBufferSize   0xFF

#define UART_BUSY		1
#define UART_AVAILABLE	0


// Terminal :
void send_int_to_terminal(int nb);


extern u8 Term_Task;
extern u8 Term_Command;


// liaison série :
extern u8 UART0_TxBuffer[10];
extern u8 UART0_RxBuffer[10];
extern u8 NbrOfDataToTransfer;
extern u8 NbrOfDataToRead;

extern u16 RxCounter;
extern u16 TxCounter;

extern u8 UART0_Tx_state;

void envoie_coord (int X, int Y, int angle);

void cmd_trappe_barillet (void);


#endif
