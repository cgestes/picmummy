/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : pobeye.h
* Author             : UTC E=M6 Team
* Date First Issued  : 25/03/08 : Version 1.0
* Description        : deplacements fonctions.
********************************************************************************/
#include "strategie.h"

#ifndef __DEPLACEMENT_H
#define __DEPLACEMENT_H

typedef enum e_container {
  CONTAINER_TEAM      = 0,
  CONTAINER_NTEAM     = 1,
  CONTAINER_W_TEAM    = 2,
  CONTAINER_W_NTEAM   = 3
} t_container;


typedef enum e_color {
	COLOR_NONE = 0,
	COLOR_TEAM,
	COLOR_NTEAM,
	COLOR_WHITE
} t_color;


/* empty the barillet if is not empty */
void do_ExpulseBalls();

/* get balls on the floor 
 *  return if the barillet is full, or all position seen
 */
void do_GetBallsFloor();

/* get balls in the container
 *  return when barrillet is full or the container empty
 */
void do_GetBallsContainer(t_container container, char count);

/* defend the base !!!!
 */
void do_defend();


#endif

/* End of file deplacements.h */
