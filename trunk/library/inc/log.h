/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : log.h
* Author             : UTC E=M6 Team
* Date First Issued  : 16/03/08 : Version 1.0
* Description        : barillet fonctions.
********************************************************************************/


#ifndef __LOG_H
#define __LOG_H

/* ENABLE/DISABLE Debug on UART for each group */				  
//#define LOG_MEMORY
#define LOG_TIMER
#define LOG_MAIN

/* this is the real debug function */
void d(const char *format, ...);

#endif
