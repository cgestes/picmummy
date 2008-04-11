/*
* File Name          : config.c
* Author             : Xt-6
* Date First Issued  : 03/02/2008 : Version 1.0
* Description        : regroupe les fonctions de configurations de la carte
********************************************************************************
* History:
*
*******************************************************************************/

#include "i2c.h"
//#define RCLK_Divisor SCU_RCLK_Div1

void GPIO_config(void);

void ADC_config(void);

void configuration_UART(void);


void config_timer0(void);

void config_interruption(void);

void configuration_I2C(void);

void config_FMI(void);

void Activer_PLL(void);

void Desactiver_PLL(void);

void SCU_Configuration(void);

void initialisation (void);

/* End of file config.h */
