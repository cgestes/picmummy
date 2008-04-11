/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : pobeye.h
* Author             : UTC E=M6 Team
* Date First Issued  : 25/03/08 : Version 1.0
* Description        : deplacements fonctions.
********************************************************************************/

/* Moving functions */

/* D�placements et strat�gie :

Moisson :
---------
R�colter les balles au d�but du match
	- suivre de points programm�s
		- si probl�me avec un point, on passe au suivant
	- � la fin, on enchaine avec "Largage"

Largage :
---------
Vider les balles du robot
	- aller � la position de largage (2/3 de notre bordure)
		- si position inaccessible, alors tendre vers 3/3
		- si position inaccessible, alors tendre vers 1/3
	- faire un 180�
	- reculer de 20cm, si choc, continuer	  
	- larguer les balles
	- mettre � jour le barillet et la couleur du conteneur
	- � la fin, on enchaine avec Recolter ou defendre

Recolter :
----------
Aller chercher les balles des reservoirs
	- Aller devant le reservoir de notre couleur
	- Lancer Recolte_reservoir avec 2 ou 3 balles, selon couleur_conteneur
	- reculer de 20cm, si choc, continuer
	- Aller devant le reservoir blanc de notre cot�
		- si position inaccessible, aller � l'autre reservoir blanc
	- Lancer Recolte_reservoir avec 2 ou 3 balles, selon couleur_conteneur
	- reculer de 20cm, si choc, continuer
	- mettre � jour le barillet et la couleur du conteneur
	- � la fin, on enchaine avec Largage

Recolter_reservoir :
--------------------
Prendre un certain nombre de balles dans le reservoir
On est plac� � 20cm environ du reservoir
	- Passer le barillet en mode "Manuel"
	- demander un emplacement vide � l'avant
	- lire IR avant (de gauche � droite, num�ros = [0 ; 1 ; 2 ; 3], avec 10cm entre les n�1 et 2)
		- si IR[1] = PROCHE & IR[2] = PROCHE alors bug (passer � l'�tape suivante ?)
		- si IR[1] = PROCHE & IR[2] = LOIN alors
			petite rotation sur la gauche
		- si IR[1] = LOIN & IR[2] = PROCHE alors
			petite rotation sur la droite
		- si IR[1] = LOIN & IR[2]=LOIN alors
			continuer
			- sinon, nouvelle lecture de IR ...
	- Avancer de 20cm jusqu'� blocage (Recaler les coordon�es et orientation)
	- si PobCouleur != COULEUR_VIDE et Nb_balle_couleur_x < Nb_balle_couleur_x_voulue alors
		- tourner le barillet pour "fermer"
		- Nb_balle_couleur_x ++
		- si Nb_balle_couleur_x < Nb_balle_couleur_x_voulue alors
			- demander emplacement vide � l'avant
			- attendre fin barillet
			- recommencer r�colte
			sinon continuer
	- reculer de 20cm, si blocage, continuer
	- demander un emplacement libre � l'avant 
	- Passer le barillet en mode "auto"
*/

/*
	prendre en compte que si le barillet est plein, la seule tache que l'on peut faire est "larguer"

*/

#include "strategie.h"

#ifndef __DEPLACEMENT_H
#define __DEPLACEMENT_H

// Variables Globales :




#endif

/* End of file deplacements.h */
