/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : barillet.h
* Author             : UTC E=M6 Team
* Date First Issued  : 16/03/08 : Version 1.0
* Description        : barillet fonctions.
********************************************************************************/

/*
La communication avec le barillet se fait avec I2C0
Utilise la gMemory

----------------------------------------------------
				gMemory :
----------------------------------------------------
#define BARILLET_KEY			12 // I2C communication
#define BARILLET_RETURN_KEY		13
#define BARILLET_NUM_TACHE		14
#define BARILLET_POSITION		15
#define	BARILLET_BLOQUER_ENTREE	16	
#define NBBALLE_TOTAL			17
#define NBBALLE_BLANCHE			18
#define	NBBALLE_TEAM			19
#define	NBBALLE_ADVERSE			20
-----------------------------------------------------

La gestion des balles (couleur...) est faite ici
*/


#ifndef __BARILLET_H
#define __BARILLET_H

// defines :

#define COULEUR_VIDE	0
#define COULEUR_BLANCHE	1
#define	COULEUR_ROUGE	2
#define COULEUR_BLEU	3

// Etats Barillet
#define BARILLET_BUSY	0x10
#define BARILLET_FREE	0x20

// Etat tache avec .data :
#define TASK_NEW	-1
// Etat avec BarTask_TaskMainNum :
#define BARILLET_FREE_FROM_MAIN	-1

// Machine à état
#define BarTask_TaskMask		0xf0
#define BarTask_StepMask		0x0f
#define BarTask_EMPTY			0xff
#define BarTask_FREE			0x01
#define BarTask_ENTREE_VIDE		0x10
#define	BarTask_BALLE_EJECTEUR	0x20
#define BarTask_EJECTER_ADVERSE	0x30
#define BarTask_BLOQUER_ENTREE	0x40

// Etat du barillet :
#define Barillet_AUTOMATIQUE	0
#define Barillet_MANUEL			1


// Structures

typedef struct
{
 	int type;
	int num;
	int data;
} task;


// Variables globales

extern int CouleurTeam;
extern int CouleurAdverse;

extern int CouleurTeam_NbVoulu;
extern int CouleurTeam_NbCourant;
extern int CouleurBlanc_NbVoulu;
extern int CouleurBlanc_NbCourant;
extern task BarTask_Courant;
extern int BarListe_Taille;
// Taches en attente
extern task BarListe_Task[10];
// Utilisé pour donné un numéro à chaque tache. Lien entre le "main" et les interruptions 
extern int BarTask_CptTask;
extern int BarListe_Available;

// 5 emplacements dans le Barillet
extern int Barillet[5]; 

// Position courante(voulue) du barillet
extern int BarPosition;
extern int BarState; // FREE ou BUSY

extern int BarTask_SaveTime;
extern int BarTask_TimeOut;

extern int BarCouleur_Ejecter;
extern int BarTask_TaskMainNum;

extern int Barillet_Mode;

// Fonctions (méthodes ^^)
void Init_Barillet(void);
int Barillet_AddTask(int pNumTask, int pData);
void Barillet_SaveTask(int pType, int pNum, int pData);
void BarListe_Trier(void);
void BarListe_RemoveTaskNum(int pNum);
void BarListe_RemoveTaskType(int pType);
int BarGet_VideAvant(void);
int BarGet_CouleurArriere(int pCouleur);
int BarGet_Bloquer(void);
void Barillet_MachineEtat(void);
int BarBalle_RemoveArriere(int pPos, int pCoul);

/* strategic function */
bool bar_Empty();
bool bar_Full();
void bar_FindEmptyPos();
void bar_Expulse();



#endif

/* End of file barillet.h */
