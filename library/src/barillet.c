/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : barillet.c
* Author             : UTC E=M6 Team
* Date First Issued  : 16/03/08 : Version 1.0
* Description        : barillet fonctions.
********************************************************************************/

#include "91x_lib.h"

void Init_Barillet(void)
{
	int i;
	// Global du barillet
	BarTask_Courant.type = BarTask_FREE;
	BarState = BARILLET_BUSY; // � l'initialisation, on attend d'�tre en position 0
	BarListe_Taille = 0;
	BarTask_CptTask = 0;
	BarListe_Available = 1;
	BarPosition =0; // � l'initialisation, le barillet va en position 0
	BarTask_TaskMainNum = BARILLET_FREE_FROM_MAIN;
	Barillet_Mode = Barillet_AUTOMATIQUE;
	for(i=0; i<5; i++)
		Barillet[i]=COULEUR_VIDE;
	// gMemory
	write_Memory_Sizeof(BARILLET_TASK_KEY , BarTask_FREE);
	write_Memory_Sizeof(BARILLET_BLOQUER_ENTREE_KEY, 0);
	write_Memory_Sizeof(NBBALLE_TOTAL_KEY, 0);
	write_Memory_Sizeof(NBBALLE_BLANCHE_KEY, 0);
	write_Memory_Sizeof(NBBALLE_TEAM_KEY, 0);
	write_Memory_Sizeof(NBBALLE_ADVERSE_KEY,0);
}

int Barillet_AddTask(int pType, int pData)
{
	while(!BarListe_Available);
	BarListe_Task[BarListe_Taille].type = pType;
	BarListe_Task[BarListe_Taille].num = BarListe_Taille;
	BarListe_Task[BarListe_Taille].data = pData;
	BarListe_Taille++;
	BarTask_CptTask++;
	return BarTask_CptTask;
}


void Barillet_SaveTask(int pType, int pNum, int pData)
{
	while(!BarListe_Available);
	BarListe_Task[BarListe_Taille].type = pType;
	BarListe_Task[BarListe_Taille].num = pNum;
	BarListe_Task[BarListe_Taille].data = pData;
	BarListe_Taille++;
}

void BarListe_Trier(void)
{
	char i;
	int type_temp, num_temp, data_temp;
	int task_pos;
	type_temp=0;
	while(!BarListe_Available);
	BarListe_Available=0; // On monopolise la liste pour la trier
	if(BarListe_Taille>1)
	{
		task_pos=0;
		type_temp=BarListe_Task[0].type;
		for(i=1;i<(BarListe_Taille);i++)
		{
		 	if(BarListe_Task[i].type>type_temp)
				{
				 	type_temp=BarListe_Task[i].type;
					task_pos=i;
				}
		}
		if(type_temp != 0)
			{
				 num_temp = BarListe_Task[task_pos].num; // sav temp
				 data_temp = BarListe_Task[task_pos].data;
				 BarListe_Task[task_pos].type = BarListe_Task[0].type & BarTask_TaskMask; // RESET de la tache n�0
				 BarListe_Task[task_pos].num = BarListe_Task[0].num;
				 BarListe_Task[task_pos].data = BarListe_Task[0].data;
				 BarListe_Task[0].type = type_temp;  // La tache de plus haute priorit� est mise � la place 0
				 BarListe_Task[0].num = num_temp;
				 BarListe_Task[0].data = data_temp;

			}
	}
	BarListe_Available=1;
}

void BarListe_RemoveTaskNum(int pNum) // Enl�ve l'�l�ment num�ro pNum de la liste des t�ches
{
	char i;
	if( pNum<BarListe_Taille)
	{
		if(BarListe_Task[pNum].num != BarTask_TaskMainNum) // On ne peut pas supprimer une t�che demand�e par le main
		{
			while(!BarListe_Available);
			BarListe_Available=0; // On monopolise la liste pour la trier
			for(i=pNum; i<(BarListe_Taille - 1); i++)
			{
				BarListe_Task[i].type = BarListe_Task[i+1].type;
				BarListe_Task[i].num = BarListe_Task[i+1].num;
				BarListe_Task[i].data = BarListe_Task[i+1].data;
			}
			BarListe_Taille--;
			BarListe_Available=1;	
		}
	}
}

void BarListe_RemoveTaskType(int pType) // Enl�ve l'�l�ment num�ro pNum de la liste des t�ches
{
	char i, save_taille;
	char type_trouve=0;
	while(!BarListe_Available);
	BarListe_Available=0; // On monopolise la liste pour la trier
	i=0;
	save_taille = BarListe_Taille; 
	do
	{
		if ((BarListe_Task[i+type_trouve].type & BarTask_TaskMask) == pType)
		{
			if(BarListe_Task[i+type_trouve].num != BarTask_TaskMainNum) // On ne peut pas supprimer une t�che demand�e par le main
			{
				type_trouve++; 
				save_taille--;
			}
		}
		
		if(type_trouve>0)
		{
			BarListe_Task[i].type = BarListe_Task[i+type_trouve].type;
			BarListe_Task[i].num = BarListe_Task[i+type_trouve].num;
			BarListe_Task[i].data = BarListe_Task[i+type_trouve].data;
		}

		i++;
	} while( (i< (save_taille-1)) && ( (i+type_trouve)<save_taille) );
	BarListe_Taille = save_taille;
	BarListe_Available=1;	
}

int BarGet_VideAvant(void) // Mettre un case vide � l'avant (trouver la position du barillet)
{
 	// Les emplacement Paire sont ouvert � l'avant
	char i=0;
	int pos_courant, pos_vide = -1;
	int pos_g, pos_d;

	pos_courant = BarPosition;
	if( (pos_courant & 0x01) )// Position impaire
		pos_courant++;
	if(pos_courant>9)
		pos_courant = pos_courant -10;
	
	do{
			pos_g = pos_courant + i;
			pos_d = pos_courant - i;
	
			if(pos_g>9)
				pos_g = pos_g - 10;
	
			if(pos_d>9)
				pos_d = pos_d - 10;
	
			if(pos_g<0)
				pos_g = pos_g + 10;
	
			if(pos_d<0)
				pos_d = pos_d + 10;

			if(Barillet[pos_d/2] == COULEUR_VIDE)
				pos_vide = pos_d;
			if(Barillet[pos_g/2] == COULEUR_VIDE)
				pos_vide = pos_g;

			i += 2;

		} while ( (i<6) && (pos_vide == -1) );
	return pos_vide;
}

int BarGet_CouleurArriere(int pCouleur) // Amener � l'arri�re une balle de la couleur demand�e
{
	char i=0;
	int pos_arriere, pos_couleur = -1;
	int pos_g, pos_d;

	pos_arriere = BarPosition + 5; // +5 = 180�
	if( (pos_arriere & 0x01) ) // Position impaire
		pos_arriere++;
	if(pos_arriere>9)
		pos_arriere = pos_arriere - 10;
	
	do{
			pos_g = pos_arriere + i;
			pos_d = pos_arriere - i;
	
			if(pos_g>9)
				pos_g = pos_g - 10;
	
			if(pos_d>9)
				pos_d = pos_d - 10;
	
			if(pos_g<0)
				pos_g = pos_g + 10;
	
			if(pos_d<0)
				pos_d = pos_d + 10;

			if(Barillet[pos_d/2] == pCouleur)
				pos_couleur = pos_d;
			if(Barillet[pos_g/2] == pCouleur)
				pos_couleur = pos_g;

			i += 2;

		} while ( (i<6) && (pos_couleur == -1) );
	return pos_couleur;
}




int BarGet_Bloquer(void)
{
	int pos_bloquer = BarPosition;
	if( (BarPosition & 0x01) == 0)
	{
		pos_bloquer ++;
		if(pos_bloquer>9)
			pos_bloquer -= 10;
	}
	return pos_bloquer;
}

int BarBalle_RemoveArriere(int pPos, int pCoul)
{
	int sav_memory;
	if( (pPos & 0x01) == 0 ) // Poisiton Paire = arri�re ferm� = erreur
		return -1;
	pPos += 5;
	if(pPos>9)
		pPos -= 10;
	pPos = pPos/2; // On passe des positions aux emplacements
	if(Barillet[pPos] == pCoul)
	{

		if(pCoul == COULEUR_BLANCHE)
		{
			sav_memory = read_Memory_Sizeof(NBBALLE_BLANCHE_KEY,MEMORY_WAIT) - 1; // MAJ du barillet
			write_Memory_Sizeof(NBBALLE_BLANCHE_KEY,sav_memory);
		
		}

		if(pCoul == CouleurTeam)
		{
				sav_memory = read_Memory_Sizeof(NBBALLE_TEAM_KEY,MEMORY_WAIT) - 1; // MAJ du barillet
				write_Memory_Sizeof(NBBALLE_TEAM_KEY,sav_memory);
		}

		if(pCoul == CouleurAdverse)
		{
				sav_memory = read_Memory_Sizeof(NBBALLE_ADVERSE_KEY,MEMORY_WAIT) - 1; // MAJ du barillet
				write_Memory_Sizeof(NBBALLE_ADVERSE_KEY,sav_memory);
		}
		sav_memory = read_Memory_Sizeof(NBBALLE_TOTAL_KEY,MEMORY_WAIT) - 1;
		write_Memory_Sizeof(NBBALLE_TOTAL_KEY,sav_memory);
		return 1;
	}
	return -1;
}

void Barillet_MachineEtat(void)
{
	int pos_barillet;
// Machine � �tat qui g�re le barillet

	// trier les t�ches :
	BarListe_Trier();
	if( (BarTask_Courant.type<BarListe_Task[0].type ) && (BarState == BARILLET_FREE) ) // Y a-t-il une t�che plus priorit�re que celle en court ?
	{
		Barillet_SaveTask( (BarTask_Courant.type & BarTask_TaskMask), (BarTask_Courant.num), BarTask_Courant.data ); // On remet et r�initialise l'ancienne t�che dans la liste
		BarTask_Courant.type = BarListe_Task[0].type;
		BarTask_Courant.num = BarListe_Task[0].num;
		BarTask_Courant.data = BarListe_Task[0].data;
	    BarListe_RemoveTaskNum(0); // On enl�ve la t�che lanc�e de la liste
		BarTask_TimeOut = Global_temps;
	}

	switch (BarTask_Courant.type)
	{
	/* Pas de t�che en cours */
		case 0x00 :
			break;
	
	/* On lib�re une t�che */	
		case 0xff :
			if(BarTask_Courant.num == BarTask_TaskMainNum) // On lib�re le main si il attendait la fin de cette t�che
				BarTask_TaskMainNum = BARILLET_FREE_FROM_MAIN;
			BarTask_Courant.type = BarTask_EMPTY;
			break;

	/* Entr�e Vide */
		case 0x10 : // d�but
	 		pos_barillet = BarGet_VideAvant();
			if( (pos_barillet != BarPosition) && (pos_barillet != -1) )
			{
				BarPosition = pos_barillet;
				BarState = BARILLET_BUSY; 
			 	write_Memory_Sizeof(BARILLET_KEY, BarPosition); //Bouger le barillet
				BarTask_Courant.type = 0x11; // Signal sortie
			}				 
			else
				BarTask_Courant.type = BarTask_FREE;
			break;

		case 0x11 : // Attente fin barillet
			if(BarState == BARILLET_FREE)
				BarTask_Courant.type = BarTask_FREE; // Signal Sortie
			break;
			 
	/* Ejecter balle Adverse */
		case 0x20 : // d�but
			if(BarTask_Courant.data == -1)
			{	// Retour apr�s interruption de la tache, on a d�j� �ject� la balle
				BarTask_Courant.type = 0x10; // Signal Sortie
				break;
			}	
			pos_barillet = BarTask_Courant.data + 5; // faire un 180�
			if(pos_barillet>9)
				pos_barillet -= 10;
			BarPosition = pos_barillet;    
			BarState = BARILLET_BUSY; 
			write_Memory_Sizeof(BARILLET_KEY, BarPosition); //Bouger le barillet
			BarTask_Courant.type = 0x21; // Signal Sortie
			break;

		case 0x21 : // Attente fin barillet
			if(BarState == BARILLET_FREE)
			{
				BarTask_SaveTime = Global_temps;
				move_servo(SERVO_EJECTION, SERVO_EJECTION_EJECTER); // Bouger le servo d'ejection
				BarTask_Courant.type = 0x22; // Signal Sortie
			}
			break;

		case 0x22 : // Attente fin servo
			if( (Global_temps - BarTask_SaveTime) > SERVO_EJECTION_TEMPS ) // Fin du temps
			{
			 	BarTask_SaveTime = Global_temps;
				move_servo(SERVO_EJECTION, SERVO_EJECTION_RENTRER); // Bouger le servo d'ejection
				// On enchaine la t�che "entr�e vide"
				
				BarTask_Courant.type = 0x23; // Signal Sortie
			}
			break;

		case 0x23 : // Attente fin servo
			if( (Global_temps - BarTask_SaveTime) > SERVO_EJECTION_TEMPS ) // Fin du temps
			{
				BarBalle_RemoveArriere(BarPosition, CouleurAdverse);
				BarTask_Courant.data = -1; // Balle �ject�e, si tache interrompue, on ira dirrectement en 0x10
				// On enl�ve les t�che de type 0x10 car on va l'executer syst�matiquement
				BarListe_RemoveTaskType(0x10);
				// On enchaine la t�che "entr�e vide"
				BarTask_Courant.type = 0x10; // Signal Sortie
			}
			break;

	/* Proposer Balle Ejecteur */
		case 0x30 : // D�but
				pos_barillet = BarGet_CouleurArriere(BarCouleur_Ejecter);
				BarPosition = pos_barillet;    
				BarState = BARILLET_BUSY; 
				write_Memory_Sizeof(BARILLET_KEY, BarPosition); //Bouger le barillet
				BarTask_Courant.type = 0x31; // Signal Sortie
			break;
		
		case 0x31 : // Attente fin barillet
			if(BarState == BARILLET_FREE)
				BarTask_Courant.type = BarTask_FREE; // Signal Sortie
			break;

	/* Bloquer Entr�e */
		case 0x40 : // D�but
			if((BarPosition & 0x01))
			{
				write_Memory_Sizeof(BARILLET_BLOQUER_ENTREE_KEY, 1);
				BarTask_Courant.type = 0x42; // Signal Sortie
			}
			else
			{
				pos_barillet = BarGet_Bloquer();
				BarState = BARILLET_BUSY; 
				write_Memory_Sizeof(BARILLET_KEY, BarPosition); //Bouger le barillet
				BarTask_Courant.type = 0x41; // Signal Sortie
			}
			break;

		case 0x41 : // Attente fin barillet
			if(BarState == BARILLET_FREE)
			{
				write_Memory_Sizeof(BARILLET_BLOQUER_ENTREE_KEY, 1);
				BarTask_Courant.type = 0x42; // Signal Sortie
			}
			break;

		case 0x42 : // Attendre fin du blocage
			if( read_Memory_Sizeof(BARILLET_BLOQUER_ENTREE_KEY, MEMORY_WAIT) == 0)
				BarTask_Courant.type = BarTask_FREE;
	/* Defaut */
		default :
			break;
	}
}		



/* End of file barillet.c */
