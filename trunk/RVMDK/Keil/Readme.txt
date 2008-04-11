/******************** (C) COPYRIGHT 2006 STMicroelectronics ********************
* File Name          : Readme.txt
* Author             : MCD Application Team
* Date First Issued  : 05/18/2006 : Version 1.0
* Description        : This sub-directory contains all the user-modifiable files 
                       needed to create a new  project linked with the STR91x  
                       library and working with RealView Microcontroller Developper 
                       Kit(RVMDK) software toolchain.(version: µVision3 V3.51 and 
                       later)
********************************************************************************
* History:
* 05/22/2007 : Version 1.2
* 05/24/2006 : Version 1.1
* 05/18/2006 : Version 1.0
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

Directory contents
===================
- project.Uv2/.Opt:A pre-configured project file with the provided library 
                   structure that produces a FLASH\RAM executable image with 
                   RVMDK.
              
- STR91x.s  : This file initializes the exception vectors, stack pointers, RAM              
              size,...,and finally branches to "main".
              It offers also the ability to select the clock source frequency to 
              be OSC, RTC or PLL (@96Mhz by default). 
              
Note:
====
 When booting from bank1, use OSC as the default clock source . 
 If you want to run  CPU @ 66 MHz or higher, PLL configuration might
 be done out in C code and the  Flash wait states configuration should be 
 executed from SRAM  to avoid read while writing in same bank.
               
- IRQ.s    : IRQ handler
- DAbt.s   : Data Abort Handler
- FIQ.s    : FIQ handler
- SWI.s    : SWI handler
- Undef.s  : Undefined Handler
- PAbt.s   : Prefetch Abort Handler


Note
====
The files listed above should be only used with the RealView Microcontroller 
Developper Kit software toolchain.

How to use it
=============
In order to make the program work, you must do the following:
- Double click on project.Uv2 file.
- Rebuild all target files(Project->Rebuild all target files)
- Load project image(Flash->Download:only for Flash image)
- Run program:Debug->Start/Stop Debug Session(Ctrl+F5)


******************* (C) COPYRIGHT 2006 STMicroelectronics *****END OF FILE****/
