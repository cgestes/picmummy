/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : positions.h
* Author             : UTC E=M6 Team
* Date First Issued  : 16/03/08 : Version 1.0
* Description        : positions sur le terrain en fonction de la couleur du robot
********************************************************************************/

#ifndef __POSITIONS_H
#define __POSITIONS_H

/* Positions du robot utilisées lors de ses déplacements.
   Positions dépendantes de la couleur (CouleurTeam) 
   Tout est en mm */

// Defines :
/* Les marges et distances d'arrêt sont données par des #define */


#define MARGE_BORDURE	400

// Marge dans laquelle on considère que le robot adverse ne peut être (limite IR)
#define MARGE_TERRAIN	200

#define TERRAIN_X	3000
#define	TERRAIN_Y	2100
#define TERRAIN_X_MIN	0
#define TERRAIN_X_MAX	3000
#define TERRAIN_Y_MIN	0
#define TERRAIN_Y_MAX	2100

// Variables Globales :

typedef struct
{
	float X;
	float Y;
	float A;
} position;

extern position PositionsListe[20];

extern position Position_Depart;
extern position Position_Destination;
extern position Position_Adverse;
extern ListePoints PointPassage[20];

void Init_Positions(int pCouleur);


#endif

/* End of file positions.h */
