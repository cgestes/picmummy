/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : pobeye.h
* Author             : UTC E=M6 Team
* Date First Issued  : 25/03/08 : Version 1.0
* Description        : Mouvements �lementaires
********************************************************************************/

/* Mouvements �lementaires :


Aller �
-------
Description : Aller � une position donn�e en utilisant le PathFinding et en g�rant les bloquages
Param�tres :
	- Xdest : Point X � atteindre
	- Ydest : Point Y � atteindre
Retour :
	- Point non-accessible
	- RETOUR_OK

Algo:
- enlever la prise en compte de l'adversaire dans le terrain <
	- Verifier Obstacle devant le robot	(si non_inhib�)		 <
		si obstacle alors									 <
			placer l'adversaire dans le terrain				 <
			activer la prise en compte de l'adversaire		 <
	- Calculer PathFinding									 <
	- Si point non-accessible (score) alors
		retour POINT_INACCESSIBLE
	- Donner � l'asservissement les 2 prochains points (on ne v�rifie pas qu'un point est atteind, on recalcule en permanance)
		- si les points envoy�s sont la destination alors :
			v�rifier si on est arriv� (XRobot = XDest ..)
			=> retour POINT_ATTEIND	 

Stop
----
Description : Arr�ter le robot
Param�tre : RIEN
Retour : RETOUR_OK ou BLOCAGE ou TIMEOUT
Algo :
	- envoyer � l'asservissement l'ordre de s'arr�ter
		peut �tre fait en demandant d'aller � la position courante.

Stop mou
--------
Description : Arr�ter le robot et coupe l'asservissement.
Param�tre : RIEN
Retour : RETOUR_OK ou BLOCAGE ou TIMEOUT
Algo :
	- envoyer � l'asservissement l'ordre de s'arr�ter
		peut �tre fait en demandant d'aller � la position courante.

Aller_a_passage
---------------
Description : Aller � un point en enchainant avec un autre point.
Param�tres : int pX : position x donn�e � l'asservissement
			 int pY : position y donn�e � l'asservissement
			 int pDistancePassage : distance entre le point de passage et le robot consid�r� pour passer au point suivant
			 int pTimeOut : temps (en ms) apr�s lequel on considerera le mouvement �chou�.
Retour : RETOUR_OK ou BLOCAGE ou TIMEOUT
Algo :
	- mettre � jour les donn�es envoy�es � l'asservissement
	- attendre que soit (lu a partir des donn�es envoy�es par l'asservissement):
		- un bloquage
		- la fin du TIMEOUT
		- la distance d�pass�e.

Aller_a_destination
-------------------
Description : Aller � un point en enchainant avec un autre point.
Param�tres : int pX : position x donn�e � l'asservissement
			 int pY : position y donn�e � l'asservissement
			 int pTimeOut : temps (en ms) apr�s lequel on considerera le mouvement �chou�.
Retour : RETOUR_OK ou BLOCAGE ou TIMEOUT

Algo :
	- mettre � jour les donn�es envoy�es � l'asservissement
	- attendre que soit (lu a partir des donn�es envoy�es par l'asservissement):
		- un bloquage
		- la fin du TIMEOUT
		- la destinnation est atteinte selon le retour de l'asservissement
	- arr�t� le robot (fait tout seul par l'asservissement, ou fait en soft)


Avancer
-------
Description : Faire une ligne droite � partir la position actuelle su robot.
			  L'asservissement est fait en distance et en orientation.
			  Si blocage, alors on retourne un blocage en s'arr�tant.
			  La vitesse peut �tre n�gative pour indiquer une marche arri�re
Param�tres : int Distance : Donne la distance max � atteindre.
			 int Vitesse
Retour : RETOUR_OK ou BLOCAGE
Algo :
		- Calculer la position du point � atteindre pour avancer de la distance voulue
		- envoyer les ordres � l'asservissement
		- Attendre la fin du mouvement


Orientation
-----------
Description : Demande au robot de s'orienter vers un angle donn� par rapport au rep�re du terrain
			  On ne tient pas comte des t�l�m�tres avant.
Param�tres : Variation voulue (en degr� par rapport au terrain)
			 Vitesse Max de rotation
Retour : RETOUR_OK ou Blocage



Calage Bordure :
----------------
Description : Demander au robot d'avancer (lentement) en ligne droite, asservissement en orientation desactiv�,
			  sur une courte distance (30 cm max)
			  Doit fonctionner avec une marche avant ou une marche arri�re
			  Les T�l�m�tres ne sont pas pris en compte
			  demander � l'asservissement d'atteindre un point en dehors du terrain (2 points de suite comme d'hab)
			  pr�voir un timeout
Param�tre : Vitesse (n�gative = marche arri�re)
			Distance Max (apr�s quoi on consid�re le point atteind
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
