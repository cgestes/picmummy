
#include "91x_lib.h"
#include "memory.h"

#ifndef _SERIAL_MESSAGE_H
#define _SERIAL_MESSAGE_H

#define SERIAL_MESSAGE_MAX_SIZE 30
#define SERIAL_LIST_MAX_MESSAGE 10

#define SERIAL_WRITE 1
#define SERIAL_READ  0
#define SERIAL_READ_COMMAND_SEND  2

#define SERIAL_REPEAT_OFF 0
#define SERIAL_REPEAT_ON  1

#define SERVO_BOARD 0x30  // serial adress of servo pic
#define MOTOR_BOARD 0x40  // i2c adress of motor pic

#define SERIAL_FREE	0
#define SERIAL_BUSY	1
#define SERIAL_BUG  2


#define NB_SERIES		2 // nb de liaisons séries
#define SERIAL_I2C0		0
#define SERIAL_UART0	1


typedef struct 
{
	int slave;	// adress of the slave
	int RW;			// flag to choose between write and read
	int repeat;		// 
	int index;	// index used during transmission/receive : position in the 32 bits word
	int command; // command written before reading a device
	int memoryKey; // index in Memory
}message_serial;

typedef struct 
{
	int size;	  // number of message handled
	int position; // position in the list
	message_serial  message[SERIAL_LIST_MAX_MESSAGE];
	int state; //  to know serial state : FREE or BUSY
}serial_list;


extern serial_list liste_serial[NB_SERIES];


/* init a list of serial message
 *  pListe : the list to handle
 */
void serial_list_init(serial_list * pListe);


/* add a message to a list of serial message
 * pListe : the list where the message need to be added
 */
void add_serial_message(serial_list * pListe, int pSlave, int RW,int pRepeat,int pCommand,int pMemoryKey);

/*  insert a message into a list of serial message
 *   pPosition  : position where the message is insert
 */
void insert_serial_message(serial_list * pListe, int pSlave, int RW, int pRepeat,int pCommand, int pMemoryKey, int pPosition);

/* repeat serial message that need to be repeated when all of them have been transmit
 *  pListe : the list to handle
 */

void repeat_serial_list(serial_list * pListe);



//serial_list_init(&liste_serial[0]);
//serial_list_init(&liste_serial[1]);

#endif

/* End of file serial_message.h */
