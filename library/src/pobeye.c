/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : pobeye.c
* Author             : UTC E=M6 Team
* Date First Issued  : 16/03/08 : Version 1.0
* Description        : pobeye fonctions.
********************************************************************************/

#include "91x_lib.h"

void Init_Pobeye(void)
{
 	//PobCouleur = COULEUR_VIDE;
	/* gMemory :
		- POBEYE_BALLE_KEY
		- POBEYE_TERRAIN_KEY
	*/
}

void Pobeye_TraiterBalles(void)
{
 int position_barillet, emplacement;
 int save_memory;
 int couleur_balle;

 position_barillet = read_Memory_Sizeof(BARILLET_RETURN_KEY ,MEMORY_WAIT);

 if( !(position_barillet & 0x01) ) // Position Paire = Balle potentiellement à l'entrée
 {
 	emplacement = position_barillet/2; // 5 emplacements (10 positions, 5 positions paires)
	couleur_balle = read_Memory_Sizeof(POBEYE_BELLE_KEY, MEMORY_WAIT);

	if (Barillet[emplacement] != COULEUR_VIDE) // Nouvelle balle à l'entrée
	{
		save_memory = read_Memory_Sizeof(NBBALLE_TOTAL_KEY, MEMORY_WAIT) +1;
		write_Memory_Sizeof(NBBALLE_TOTAL_KEY, save_memory);

		if(couleur_balle == CouleurTeam) // Balle de la couleur de l'équipe
		{
			Barillet[emplacement] = CouleurTeam;
			Barillet_AddTask(BarTask_ENTREE_VIDE, 0);
			save_memory = read_Memory_Sizeof(NBBALLE_TEAM_KEY, MEMORY_WAIT) +1;
			write_Memory_Sizeof(NBBALLE_TEAM_KEY, save_memory);

		}
		else
		{
			if(couleur_balle == COULEUR_BLANCHE)
			{
				Barillet[emplacement] = COULEUR_BLANCHE;
				Barillet_AddTask(BarTask_ENTREE_VIDE, 0);
				save_memory = read_Memory_Sizeof(NBBALLE_BLANCHE_KEY, MEMORY_WAIT) +1;
				write_Memory_Sizeof(NBBALLE_BLANCHE_KEY, save_memory);
			}
			else
			{ // Balle de couleur adverse
				Barillet[emplacement] = CouleurAdverse;
				Barillet_AddTask(BarTask_EJECTER_ADVERSE, BarPosition);
				save_memory = read_Memory_Sizeof(NBBALLE_ADVERSE_KEY, MEMORY_WAIT) +1;
				write_Memory_Sizeof(NBBALLE_ADVERSE_KEY, save_memory);
			}
		}
	}
 }
}

/* End of file pobeye.c */
