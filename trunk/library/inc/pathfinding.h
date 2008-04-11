/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : PathFinding.c
* Author             : UTC E=M6 Team
* Date First Issued  : 05/02/08 : Version 1.0
* Description        : PathFinding fonctions.
********************************************************************************/

/* Principe :
- input : 
		position du robot (depart) en mm
		position à atteindre (dest) en mm
		position du robot adverse en mm ( 0,0 = pas d'adverse pris en compte)

- output :
		liste de points à atteindre
*/

#include "91x_type.h"
#include "maths.h"

#ifndef __PATHFINDING_H
#define __PATHFINDING_H

#define SCORE_OUT 1000
// Definir les conditions d'un point inaccessible dans le pathfinding
#define SCORE_CIBLE_INACCESSIBLE	4000
#define NB_MOUVEMENT_MIN			10
#define NB_MOUVEMENT_MAX			100
#define ADVERSE_OUBLIER	0
#define	ADVERSE_PRESENT	1




// Définition des structures:

typedef struct
{
	s16 X;
	s16 Y;
} CaseXY;


typedef struct
{
	u16 Score;
	CaseXY Parent;
	u16 Temps;
	CaseXY Depart_droite;
} CaseINFO;

typedef struct
{
	u16 TailleListe;
	CaseXY Points[30];
} ListePoints;


// Entrées/sorties
extern u8 Adverse_State; // ADVERSE_PRESENT ou ADVERSE_OUBLIER

// Fonctions et procédures


void Init_PathFinding(void);
u16 Calcul_Score_terrain(u16 case_x, u16 case_y, u16 rotation);
u16 Calcul_poids_case(s16 case_x, s16 case_y, u16 new_temps, u16 rot, u16 px, u16 py);
void Calculer_Score_Case(CaseXY case_eval, u16 new_temps, u16 rot, CaseXY case_parent);
void Evaluer_voisins(CaseXY case_eval);
void Start_PathFinding(void);
CaseXY MAJ_PathFinding(CaseXY case_a_fermer);
void Chemin(ListePoints * ListePassage);
void PathFinding(CaseXY Point_Depart, CaseXY Point_Destination, CaseXY Point_Adverse, ListePoints * ListePassage);
void Simplifier_Chemin(ListePoints * Points_Passage_avant_simplification, ListePoints * Points_Passage_apres_simplification) ;
void load_robot_adverse(void);

#endif

/* End of file pathfinding.h */
