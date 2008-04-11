
#include "91x_lib.h"
#include "serial_message.h"


/* init a list of serial message
 *  pListe : the list to handle
 */
void serial_list_init(serial_list * pListe)
{
	pListe->size = 0;
	pListe->position = 0;
	pListe->state = SERIAL_FREE;
}

/* add a message to a list of serial message
 * pListe : the list where the message need to be added
 */
void add_serial_message(serial_list * pListe, int pSlave, int RW,int pRepeat,int pCommand,int pMemoryKey)
{
	insert_serial_message( pListe, pSlave, RW,pRepeat,pCommand,pMemoryKey,pListe->size);
	pListe->size++; // official add of the new message
}
/*  insert a message into a list of serial message
 *   pPosition  : position where the message is insert
 */
void insert_serial_message(serial_list * pListe, int pSlave, int RW, int pRepeat,int pCommand, int pMemoryKey, int pPosition)
{
	message_serial * message;
	
	message = &pListe->message[pPosition]; // get a pointer on the new message
	
	message->slave = pSlave;
	message->RW    = RW;	
	message->repeat = pRepeat;
	message->command = pCommand;
	message->index = 0;
	message->memoryKey = pMemoryKey;
}

/* repeat serial message that need to be repeated when all of them have been transmit
 *  pListe : the list to handle
 */

void repeat_serial_list(serial_list * pListe)
{
	int i=0 , j=0;
	message_serial * message;
		
	for (i=0; i<pListe->size; i++)
	{
		message = &pListe->message[i];
		if (message->repeat )
		{
			insert_serial_message( pListe, message->slave, message->RW,message->repeat,message->command,message->memoryKey,j);
			j++;
		}
		else
		{
			if(message->index == 0) // On n'a pas encore envoyé le message
			{
				insert_serial_message( pListe, message->slave, message->RW,message->repeat,message->command,message->memoryKey,j);
				j++;
			}
		}
	}
	
	pListe->size = j;
	pListe->position = 0; // Pret pour un nouvel envoie
}


//serial_list liste_serial[2];

//serial_list_init(&liste_serial[0]);
//serial_list_init(&liste_serial[1]);



