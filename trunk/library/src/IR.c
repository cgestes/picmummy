/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : IR.c
* Author             : UTC E=M6 Team
* Date First Issued  : 03/04/08 : Version 1.0
* Description        : Infrarouges
********************************************************************************/

#include "91x_lib.h"
#include "IR.h"

void IR_Lecture(void)
{
	int c[5];
	//int i;						
	//int conv;

	// Lecture des capteurs
 	while(ADC_GetFlagStatus(ADC_FLAG_ECV) == RESET)
	  ;
	c[0] = ADC_GetConversionValue(ADC_Channel_0);
	c[1] = ADC_GetConversionValue(ADC_Channel_1);
	c[2] = ADC_GetConversionValue(ADC_Channel_2);
	c[3] = ADC_GetConversionValue(ADC_Channel_3);
	c[4] = ADC_GetConversionValue(ADC_Channel_5);

	/* Clear the end of conversion flag */
	ADC_ClearFlag(ADC_FLAG_ECV);
	
	write_Memory(IR_C_KEY, 0, c[0]/6);
	write_Memory(IR_C_KEY, 1, c[1]/6);
	write_Memory(IR_C_KEY, 2, c[2]/6);
	write_Memory(IR_C_KEY, 3, c[3]/6);
	write_Memory(IR_C_KEY, 4, c[4]/6);
	// Conversion en cm	: de 0cm à 60cm
	/*
	for(i=0;i<4;i++)
	{
		if(c[i]<IR_SEUIL_MIN)
		{
			write_Memory(IR_C_KEY, IR_DEFAULT_VALUE, i);
		}
		else
		{
			conv = IR_TO_CM_CST + IR_TO_CM_X*c[i] + IR_TO_CM_X2*c[i];
			write_Memory(IR_C_KEY, c[i], i);
		}	
	} */
}

int IR_Traiter_Adverse(void)
{
	// Calculer la position de l'adversaire
	int Xr,Yr,Or; // Robot
	float Xa,Ya; // Adverse
	int c[4]; // mesures de infrarouges en cm
			  // 10cm entre chaque capteur
	int nb_IR;
	int Yc; // centre des capteurs actifs selon Y du robot
	int Xc; // Distance entre les capteurs et le robot adverse (min de d[])

	int i;

// Simulation

	Xr=read_Memory_Sizeof(ASS_COORDONEES_X_KEY, MEMORY_WAIT);
	Yr=read_Memory_Sizeof(ASS_COORDONEES_Y_KEY, MEMORY_WAIT);
	Or=read_Memory_Sizeof(ASS_ORIENTATION_KEY, MEMORY_WAIT);;

	for(i=0;i<4;i++) // Récupère les distance des capteurs
		c[i] = read_Memory(IR_C_KEY, MEMORY_WAIT, i);

	nb_IR=0;
	Xc=0;
	Yc=0;
	for(i=0; i<4; i++)
	{
		if(c[i] != IR_DEFAULT_VALUE)
		{
			Xc = Xc + c[i]; // servira pour faire une moyenne devant le robot
			nb_IR++;
			
			switch(i)
			{
			case 0:
				Yc+=IR_Yc0;
				break;
			case 1:
				Yc+=IR_Yc1;
				break;
			case 2:
				Yc+=IR_Yc2;
				break;
			case 3:
				Yc+=IR_Yc3;
				break;
			}
		}
	}
	if(nb_IR>0)
	{
		Yc=Yc/nb_IR;
		Xc=Xc/nb_IR + IR_DIST_AVANT_MIN + IR_RAYON_ADVERSE;
		//cout<<"Robot détecté\n Yc="<<Yc<<" Xc="<<Xc<<"\n";
		Xa = Xr + Yc*cos(Or+90) + Xc*cos(Or);
		Ya = Yr + Yc*sin(Or+90) + Xc*sin(Or);
		//cout<<"Xa ="<<Xa<<" Ya="<<Ya<<"\n";
		if( ((Xa-MARGE_TERRAIN)>TERRAIN_X_MIN) && ((Xa+MARGE_TERRAIN)<TERRAIN_X_MAX) &&	((Ya-MARGE_TERRAIN)>TERRAIN_Y_MIN) && ((Ya+MARGE_TERRAIN)<TERRAIN_Y_MAX) )
		{	// Robot adverse = point dans le terrain
			Adverse_State = ADVERSE_PRESENT;
			Position_Adverse.X = Xa;
			Position_Adverse.Y = Ya;
		}

		if(Xc<IR_SEUIL_MIN_BLOCAGE)
			return BLOCAGE;

	}

  	return RETOUR_OK;

}

/* End of file IR.c */
