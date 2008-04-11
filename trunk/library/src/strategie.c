/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : strategie.c
* Author             : UTC E=M6 Team
* Date First Issued  : 02/04/08 : Version 1.0
* Description        : fonctions gérant la stratégie du robot
********************************************************************************/

#include "91x_lib.h"
#include "strategie.h"

void Init_Strategie(void)
{
 	Fin_TE=0;
}

void wait_fin_TE(void)
{
	Fin_TE=0;
	while(!Fin_TE)
	  ;
}

/* End of file strategie.c */
