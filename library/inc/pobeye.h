/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : pobeye.h
* Author             : UTC E=M6 Team
* Date First Issued  : 16/03/08 : Version 1.0
* Description        : pobeye fonctions.
********************************************************************************/

/* Use the PobEye video camera */

/*
La communication avec la PobEye se fait avec le PortCom2
*/

#ifndef __POBEYE_H
#define __POBEYE_H

// Variables Globales :
	/* gMemory :
		- POBEYE_BALLE_KEY
		- POBEYE_TERRAIN_KEY
	*/

void Init_Pobeye(void);

void Pobeye_TraiterBalles(void);

#endif

/* End of file pobeye.h */
