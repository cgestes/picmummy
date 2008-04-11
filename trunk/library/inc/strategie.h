/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : strategie.h
* Author             : UTC E=M6 Team
* Date First Issued  : 02/04/08 : Version 1.0
* Description        : fonctions g�rant la strat�gie du robot.
********************************************************************************/


#ifndef __STRATEGIE_H
#define __STRATEGIE_H

// Defines :

/* Utilis� par toutes le fonctions retourant une information pour  la strat�gie (pathfinding, mouvement, deplacement...) */
#define RETOUR_OK			1
#define	BLOCAGE				2
#define TIME_OUT			3
#define	CIBLE_INACCESSIBLE	4

// Variables Globales :

extern int Fin_TE;

// Prototypes :

void Init_Strategie(void);

void wait_fin_TE(void);

#endif

/* End of file strategie.h */
