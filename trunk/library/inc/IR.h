/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : IR.h
* Author             : UTC E=M6 Team
* Date First Issued  : 03/04/08 : Version 1.0
* Description        : Infrarouges.
********************************************************************************/

/* 4 capteur infrarouges sur les convertisseurs A/N */

#ifndef __IR_H
#define __IR_H

// Define :

// Transformation A/N=>cm de la forme :
// Dist_cm = IR_TO_CM_CST + x*IR_TO_CM_X + x²*IR_TO_CM_X2
#define IR_TO_CM_CST	1
#define IR_TO_CM_X		1
#define IR_TO_CM_X2	1

// Seuil (A/N) sous lequel on ne considère pas le capteur comme fiable
#define IR_SEUIL_MIN	80
// Valuer prise si A/N<Seuil_Min
#define IR_DEFAULT_VALUE 255	

// Distance entre les capteurs et l'avant du robot
#define IR_DIST_AVANT_MIN	250

// Distance entre le bord du robot adverse et son centre
#define IR_RAYON_ADVERSE	250

// Position des capteurs infrarouges sur la largeur, par rapport au centre du robot :
#define IR_Yc0	15
#define IR_Yc1	5
#define IR_Yc2	-5
#define IR_Yc3	-15

// Seuil en cm sous lequel on considère (anticipe) un blocage
#define IR_SEUIL_MIN_BLOCAGE	350


// Variables Globales :


// Prototypes :

void IR_Lecture(void);

int IR_Traiter_Adverse(void);


#endif

/* End of file IR.h */
