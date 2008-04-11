
#include "91x_type.h"


#ifndef _MEMORY_H
#define _MEMORY_H

// Taille "classiques"
#define MEMORY_SIZE_32	0x04
#define MEMORY_SIZE_24	0x03
#define MEMORY_SIZE_16	0x02
#define MEMORY_SIZE_8	0x01

// Tableau de taille précisé par l'utilisateur
#define MEMORY_TAB		0x10
#define MEMORY_SIZE		0x0f



#define MEMORY_WAIT		100
#define MEMORY_READ		0
#define MEMORY_WRITE	1


#define NB_VARIABLE		50

// Adressage de la gMemory

#define POSITION_X_KEY 	0
#define POSITION_Y_KEY 	1

#define SERVO_BASE_KEY	2
#define SERVO_0_KEY 	2
#define SERVO_1_KEY 	3
#define SERVO_2_KEY 	4
#define SERVO_3_KEY 	5
#define SERVO_4_KEY 	6
#define SERVO_5_KEY 	7
#define SERVO_6_KEY 	8
#define SERVO_7_KEY 	9
#define SERVO_8_KEY 	10
#define SERVO_9_KEY 	11

#define BARILLET_KEY				12 
#define BARILLET_RETURN_KEY			13
#define BARILLET_TASK_KEY			14
#define BARILLET_POSITION_KEY		15
#define	BARILLET_BLOQUER_ENTREE_KEY	16	
#define NBBALLE_TOTAL_KEY			17
#define NBBALLE_BLANCHE_KEY			18
#define	NBBALLE_TEAM_KEY			19
#define	NBBALLE_ADVERSE_KEY			20

//Asservissment
// Write
#define	ASS_WRITE_KEY				21
#define ASS_POINT1_X_KEY			22
#define ASS_POINT1_Y_KEY			23
#define ASS_POINT2_X_KEY			24
#define ASS_POINT2_Y_KEY			25
// Vitesse, condition de sortie ...
#define ASS_CONSIGNE_KEY			26

// Read
#define ASS_READ_KEY				27
#define ASS_COORDONEES_X_KEY		28
#define ASS_COORDONEES_Y_KEY		29
#define ASS_ORIENTATION_KEY			30

// IR Sharp
#define IR_C_KEY					31

// PobEye
#define POBEYE_BALLE_KEY			32
#define POBEYE_TERRAIN_KEY			33

// a faire ...
#define ADVERSE_X_KEY				34
#define ADVERSE_Y_KEY				35

/* container state */
#define CONTAINER_KEY               36

/* useless define, only needed to avoid other to use those key */
#define CONTAINER_TEAM_KEY			36
#define CONTAINER_NTEAM_KEY			37
#define CONTAINER_WHITE1_KEY		38
#define CONTAINER_WHITE2_KEY		39

/* the floor is not really a container, no matter */
#define CONTAINER_FLOOR_KEY         40

#define LAST_EXPULSED_KEY           41




/* COMMANDES de la gMemory : */

// Servo Moteurs => servo.h (commande = numéro du servo)

// Barillet :
#define COM_BARILLET_WRITE	0x10
#define COM_BARILLET_READ	0x20


typedef struct
{
	char value[10];   // the value
	char size;
	int updated; // update flag when a new value has been read from  a slave
	int available; // protect from an interrupt modification is a 0 when interruption is changing this value , not sure if it is enough
}device;

extern device gMemory[NB_VARIABLE];

void init_device(int pMemoryKey,int pValue, u8 pSize);

int acces_Memory(int pMemoryKey, int pWriteData, int pReadWrite, int pIndex);

// Fonctions générales de lecture, écriture
int read_Memory(int pMemoryKey, int pIndex, int pWait);

void write_Memory(int pMemoryKey, int pIndex, int pValue);
// Fonctions spécifiques pour les char, int16 et int 32

int read_Memory_Sizeof(int pMemoryKey, int pWait);

void write_Memory_Sizeof(int pMemoryKey, int pValue);

int Get_Update_Memory(int pMemoryKey);

#define mget(a) read_Memory_Sizeof(a, MEMORY_WAIT)
#define mset(a, b) read_Memory_Sizeof(a, b)

#define mgeta(a, i) read_Memory(a, i, MEMORY_WAIT)
#define mseta(a, i, b) read_Memory(a, i, b)


#endif // _MEMORY_H

/* END of File MEMORY.H */

