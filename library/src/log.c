/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : log.h
* Author             : UTC E=M6 Team
* Date First Issued  : 16/03/08 : Version 1.0
* Description        : barillet fonctions.
********************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include "91x_lib.h"
#include "log.h"				   


void d(const char *format, ...)
{
  char tmp[256];
  char *ptr = tmp;
  va_list args;

  va_start(args, format);
  vsprintf(tmp, format, args);
  
  while (*ptr)
  {
    UART_SendData(UART0, *ptr);
	ptr++;
  }
  va_end(args);
}
