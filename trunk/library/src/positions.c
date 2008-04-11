/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : pobeye.h
* Author             : UTC E=M6 Team
* Date First Issued  : 16/03/08 : Version 1.0
* Description        : positions sur le terrain en fonction de la couleur du robot
********************************************************************************/

#include "91x_lib.h"

/* Calcul des positions selon la couleur du robot 
   Tout est calculé pour le départ ROUGE. On fait une symétrie pour
   obteninr les positions Bleues.
   Toutes les positions sont mises dans un tableau "Global" */

// Positions :
#define NB_POSITIONS	16

#define DEPART		0
#define NB_PT_MOISSON	7
#define	MOISSON_P0	1
#define	MOISSON_P1	2
#define	MOISSON_P2	3
#define	MOISSON_P3	4
#define	MOISSON_P4	5
#define	MOISSON_P5	6
#define	MOISSON_P6	7

#define RESERVOIR_BLANC_TEAM	8
#define RESERVOIR_BLANC_ADVERSE	9
#define RESERVOIR_TEAM			10

#define	LARGAGE_2_3	11
#define	LARGAGE_3_3	12
#define LARGAGE_1_3	13

#define DEFENSE_P0	14
#define DEFENSE_P1	15

void Init_Positions(int pCouleur)
{
	char i;

	PositionsListe[DEPART].X = 0;
	PositionsListe[DEPART].Y = 0;
	PositionsListe[DEPART].A = 0;

	// ...

 	if(pCouleur == COULEUR_BLEU)
	{
		for(i=0;i<NB_POSITIONS;i++)
		{
			PositionsListe[i].X = TERRAIN_X - PositionsListe[i].X;
			if(PositionsListe[i].A>90)
				PositionsListe[i].A = 90 - (PositionsListe[i].A - 90);

			if(PositionsListe[i].A<-90)
				PositionsListe[i].A = -90 + ( -90 - PositionsListe[i].A);

			if( (PositionsListe[i].A<90) && (PositionsListe[i].A>=0) )
				PositionsListe[i].A = 180 - PositionsListe[i].A;

			if( (PositionsListe[i].A>-90) && (PositionsListe[i].A<0) )
				PositionsListe[i].A = - 180 -PositionsListe[i].A;
		}
	}
}



/* End of file positions.c */
