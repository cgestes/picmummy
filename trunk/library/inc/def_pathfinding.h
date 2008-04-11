/*
Variables globales au module PathFinding
*/

#include "pathfinding.h" // pour les structures
#include "robot.h" // fichier généré par le simulateur de PathFinding
#include "maths.h"
#include "strategie.h"


#ifndef __DEF_PATHFINDING_H
#define __DEF_PATHFINDING_H


CaseXY Case_Depart;
CaseXY Case_Destination;
CaseXY Case_Adverse;
CaseXY Liste_Points_Passage[20];
u16 Nb_Points_Passage;


u16 Adverse_MAT[5][5];
CaseXY Adverse_Centre;
CaseXY Adverse_Dim;




CaseXY Liste_PF_Ouvert[700];
u16 Nb_Noeuds_Ouverts ;
u16 Last_Nb_Noeuds_Ouverts;


CaseINFO Mat_PF_Case[30][21];
u16 Mat_PF_Terrain[30][21];
CaseXY Liste_Points_Passage_avant_simplification[100];
u16 Nb_Points_Passage_avant_simplification;



u16 Coef_PF_Distance;
u16 Coef_PF_Temps;
u16 Coef_PF_Cross;		 
u16 Coef_PF_Reservoir;
u16 Coef_PF_Adverse;
u16 Coef_PF_Seuil_Droite;
u16 Fin_PF;




#endif
