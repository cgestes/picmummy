/*

Divers 
regroupe les fonctions inclassables ^^
*/

#include "divers.h"

/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
* Output         : None
* Return         : None
*******************************************************************************/
static void Delay(u32 nCount)
{
  u32 j = 0;

  for(j = nCount; j != 0; j--);
}




 /*******************************************************************************
* Function Name  : Jouer_note
auteur : Thierry Lechevallier
* Description    : joue des notes de musiques
*******************************************************************************/



void Jouer_note(u32 freq, u32 duree)
{
	u32 i = 0;
	u32 fin = duree*REF_TPS;
	
	if(GPIO_ReadBit(GPIO6,GPIO_Pin_4) == Bit_SET)
		{
			//GPIO_WriteBit(GPIO6,GPIO_Pin_4,Bit_RESET);
		}
	else
		{
			//GPIO_WriteBit(GPIO6,GPIO_Pin_4,Bit_SET);
		}
	
	do
	{
		Delay(freq);
		GPIO_WriteBit(GPIO4,GPIO_Pin_6,Bit_SET);
		Delay(freq);
		GPIO_WriteBit(GPIO4,GPIO_Pin_6,Bit_RESET);
		i=i+freq*2;
	} while (i<fin);
}

void Depart(void)
{
	int couleur;
	int last_couleur;
	int jack;
	last_couleur=10;

	do // L'écran clignotte jaune tant que le jack n'est pas mis
	{
		fillWin(setWin(0,0,131,131),YELLOW);
		fillWin(setWin(0,0,131,131),0);
		jack = GPIO_ReadBit(GPIO2, GPIO_Pin_5);	
	} while (jack == SET);

	do
	{
		// on regarde la position de l'interrupteur
		couleur = GPIO_ReadBit(GPIO2, GPIO_Pin_4);
		if(couleur != last_couleur)
		{
			Init_Positions(couleur); // Calcule les positions sur le terrain utilisées pendant le match
			// Envoyer à l'asservissement la nouvelle position (couleur au moins)
			last_couleur = couleur;
			if(couleur == SET)
			{
			CouleurTeam = COULEUR_BLEU;
			CouleurAdverse = COULEUR_ROUGE;
			fillWin(setWin(0,0,131,131),BLUE); // On met l'écran LCD de la couleur de l'écran
			}
			else
		   	{
				CouleurTeam = COULEUR_ROUGE;
				CouleurAdverse = COULEUR_BLEU;
				fillWin(setWin(0,0,131,131),RED);
			}
		}
	 
	
		jack = GPIO_ReadBit(GPIO2, GPIO_Pin_5); // Tant que le Jack est mis, on boucle sur la couleur
	} while (jack == RESET); 


	Global_temps=0; // RAZ du compteur temps
	//fillWin(setWin(0,0,131,131),0); // efface l'écran

}


