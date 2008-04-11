/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : pobeye.h
* Author             : UTC E=M6 Team
* Date First Issued  : 25/03/08 : Version 1.0
* Description        : Mouvements élementaires
********************************************************************************/

/* Mouvements élementaires :


Aller à
-------
Description : Aller à une position donnée en utilisant le PathFinding et en gérant les bloquages
Paramètres :
	- Xdest : Point X à atteindre
	- Ydest : Point Y à atteindre
Retour :
	- Point non-accessible
	- RETOUR_OK

Algo:
- enlever la prise en compte de l'adversaire dans le terrain <
	- Verifier Obstacle devant le robot	(si non_inhibé)		 <
		si obstacle alors									 <
			placer l'adversaire dans le terrain				 <
			activer la prise en compte de l'adversaire		 <
	- Calculer PathFinding									 <
	- Si point non-accessible (score) alors
		retour POINT_INACCESSIBLE
	- Donner à l'asservissement les 2 prochains points (on ne vérifie pas qu'un point est atteind, on recalcule en permanance)
		- si les points envoyés sont la destination alors :
			vérifier si on est arrivé (XRobot = XDest ..)
			=> retour POINT_ATTEIND	 

Stop
----
Description : Arréter le robot
Paramètre : RIEN
Retour : RETOUR_OK ou BLOCAGE ou TIMEOUT
Algo :
	- envoyer à l'asservissement l'ordre de s'arréter
		peut être fait en demandant d'aller à la position courante.

Stop mou
--------
Description : Arréter le robot et coupe l'asservissement.
Paramètre : RIEN
Retour : RETOUR_OK ou BLOCAGE ou TIMEOUT
Algo :
	- envoyer à l'asservissement l'ordre de s'arréter
		peut être fait en demandant d'aller à la position courante.

Aller_a_passage
---------------
Description : Aller à un point en enchainant avec un autre point.
Paramètres : int pX : position x donnée à l'asservissement
			 int pY : position y donnée à l'asservissement
			 int pDistancePassage : distance entre le point de passage et le robot considéré pour passer au point suivant
			 int pTimeOut : temps (en ms) après lequel on considerera le mouvement échoué.
Retour : RETOUR_OK ou BLOCAGE ou TIMEOUT
Algo :
	- mettre à jour les données envoyées à l'asservissement
	- attendre que soit (lu a partir des données envoyées par l'asservissement):
		- un bloquage
		- la fin du TIMEOUT
		- la distance dépassée.

Aller_a_destination
-------------------
Description : Aller à un point en enchainant avec un autre point.
Paramètres : int pX : position x donnée à l'asservissement
			 int pY : position y donnée à l'asservissement
			 int pTimeOut : temps (en ms) après lequel on considerera le mouvement échoué.
Retour : RETOUR_OK ou BLOCAGE ou TIMEOUT

Algo :
	- mettre à jour les données envoyées à l'asservissement
	- attendre que soit (lu a partir des données envoyées par l'asservissement):
		- un bloquage
		- la fin du TIMEOUT
		- la destinnation est atteinte selon le retour de l'asservissement
	- arrété le robot (fait tout seul par l'asservissement, ou fait en soft)


Avancer
-------
Description : Faire une ligne droite à partir la position actuelle su robot.
			  L'asservissement est fait en distance et en orientation.
			  Si blocage, alors on retourne un blocage en s'arrétant.
			  La vitesse peut être négative pour indiquer une marche arrière
Paramètres : int Distance : Donne la distance max à atteindre.
			 int Vitesse
Retour : RETOUR_OK ou BLOCAGE
Algo :
		- Calculer la position du point à atteindre pour avancer de la distance voulue
		- envoyer les ordres à l'asservissement
		- Attendre la fin du mouvement


Orientation
-----------
Description : Demande au robot de s'orienter vers un angle donné par rapport au repère du terrain
			  On ne tient pas comte des télémètres avant.
Paramètres : Variation voulue (en degré par rapport au terrain)
			 Vitesse Max de rotation
Retour : RETOUR_OK ou Blocage



Calage Bordure :
----------------
Description : Demander au robot d'avancer (lentement) en ligne droite, asservissement en orientation desactivé,
			  sur une courte distance (30 cm max)
			  Doit fonctionner avec une marche avant ou une marche arrière
			  Les Télémètres ne sont pas pris en compte
			  demander à l'asservissement d'atteindre un point en dehors du terrain (2 points de suite comme d'hab)
			  prévoir un timeout
Paramètre : Vitesse (négative = marche arrière)
			Distance Max (après quoi on considère le point atteind
Retour : RETOUR_OK ou Blocage ou Calage_non_atteind	ou TIME_OUT


*/

#include "strategie.h"


#ifndef __MOUVEMENT_H
#define __MOUVEMENT_H

// Defines :

#define VITESSE_LENTE	0x01
#define VITESSE_MOYENNE	0x02
#define VITESSE_RAPIDE	0x03
// Variables Globales :


// Prototypes



#endif

/* End of file mouvement.h */
