/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : servo.h
* Author             : UTC E=M6 Team
* Date First Issued  : 13/02/08 : Version 1.0
* Description        : Servo motor fonctions.
********************************************************************************/


#ifndef __SERVO_H
#define __SERVO_H

/*
Fonctions utilisant les servo moteurs
*/

#include "91x_lib.h"

#define	NB_POSITIONS_SERVO	5
#define NB_SERVO			10

// Pour chaque servo, on autorise 5 positions différentes
// Un index donne la valeur courante

/* SERVOS : */

// Numéro servo
#define SERVO_EJECTION	0 
// positions
#define SERVO_EJECTION_RENTRER	0 
#define SERVO_EJECTION_EJECTER	1
// Temps de mouvement en 10ms : 100 = 1 sec
#define SERVO_EJECTION_TEMPS	100 





typedef struct 
	{
	u8 current;
	u16 position[NB_POSITIONS_SERVO];
	}type_servo;

// Un tableau contient les positions de chaque servos
// Il faut charger ce tableau à l'initialisation à partir de la flash
 
extern type_servo tab_servo[NB_SERVO];


void load_all_servos(void);
void save_all_servos(void);
void config_servo(u8 num, u8 pos, u16 value);
void move_servo(u8 num, u8 pos);

#endif

/* End of file servo.h */
