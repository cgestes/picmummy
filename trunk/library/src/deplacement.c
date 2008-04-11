/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : deplacement.c
* Author             : UTC E=M6 Team
* Date First Issued  : 16/03/08 : Version 1.0
* Description        : deplacement fonctions.
********************************************************************************/

#include "91x_lib.h"
#include "deplacement.h"

/* TODO
 - container
  init container values
  init last_expulsed (to white)
 - 
*/


/* 1) lock the rouleau
 * 2) set the barillet to automatic mode
 */
void rouleau_Lock()
{ 
  /*  1 */
  //cervo_blabla
  /* FIXME */
}

/* 1) unlock the rouleau
 * 2) set the barillet to manual mode
 */
void rouleau_Unlock()
{
  
 /* FIXME */	
}

/* update the ball count in a container */
void container_RmBall(t_container container)
{
  char ccount; 

  ccount = mget(CONTAINER_KEY + container);
  ccount++;
  mset(CONTAINER_KEY + container, ccount);	
}

/*
 * return the color seen by the pobeyes
 */
t_color pe_Color()
{
  switch (mget(POBEYE_BALLE_KEY))
  {
	/* FIXME */
    case 1: 
	  return COLOR_TEAM;
	case 2:
	  return COLOR_NTEAM; 
  }
  return COLOR_NONE;
}

/**************************** MOVEMENT *********************************/
/*
- lire IR avant (de gauche à droite, numéros = [0 ; 1 ; 2 ; 3], avec 10cm entre les n°1 et 2)
	- si IR[1] = PROCHE & IR[2] = PROCHE alors bug (passer à l'étape suivante ?)
	- si IR[1] = PROCHE & IR[2] = LOIN alors
		petite rotation sur la gauche
	- si IR[1] = LOIN & IR[2] = PROCHE alors
		petite rotation sur la droite
	- si IR[1] = LOIN & IR[2]=LOIN alors
		continuer
		- sinon, nouvelle lecture de IR ...
- Avancer de 20cm jusqu'à blocage (Recaler les coordonées et orientation)
*/


/*
 *  go to a position
 * return 1 on success
 */
char go_To(char pos)
{ 
  /* FIXME: call patchfinding */
  return 0;
}

/*
 * 1) read IR
 * 2) adjust pos
 * 3) recalage
 */
void go_ContainerFront()
{
	IR_Lecture();
  /* FIXME */
}

/*
 * 1) shutdown brain
 * 2) go forward like a mad cow
 * 3) WoW this is the border, now I know where i'am
 */
void go_NextToBorder()
{
  /* FIXME */	
}


/******************* EXPORTED *******************/

/*
 * Vider les balles du robot
 *
 * 1) find a valid position (2/3 -> 3/3 -> 1/3)
   2) recalage
   3) push each ball
*/
void do_ExpulseBalls()
{
  char pos = LARGAGE_2_3;

  /* barrillet empty => nothing to do here */
  if (bar_Empty())
	return;

  /* 1 */
  while (!go_To(pos))
  {
    pos++;
    if (pos > LARGAGE_3_3)
      pos = LARGAGE_1_3;
  }

  /* 2 */
  go_NextToBorder();

  /* 3 */
  while (!bar_Empty())
	bar_Expulse();
}



/* get balls on the ground
 * 1) try each position
 * 2) signal that the floor is now empty (in our point of view)
 * return if the barillet is full or if each position have been tried
 */
void do_GetBallsOnFloor()
{
  char pos = MOISSON_P0;
		
  while (pos < MOISSON_P0 + NB_PT_MOISSON && !bar_full())
    go_To(pos);
  mset(CONTAINER_FLOOR, 0);
}

/*
 * 1) go to the container
 * 2) unlock the rouleau && barillet = manuel
 * 3) find an empty position for the barillet
 * 4) recalage
 * 5) while(count) get the ball, goto 4)
 * 6) go backwar, lock rouleau,  barillet = auto
 */
void do_GetBallsContainer(t_container container, char count)
{
  char ccount = 0;
  /* nothing to do */
  if (bar_Full())
	return;
	
  /*  1 */	
  go_to(RESERVOIR + container);

  /*  2 */
  rouleau_unlock();

  /*  3 */
  bar_FindEmptyPos();

  /*  4 */
  go_ContainerFront();

  /* update the container balls count */
  if (pe_Color() != COLOR_NONE)
	container_RmBall(container);
	
  while (!bar_Full() && count)
  {
	if (pe_Color() == COLOR_NONE)
	  break; //FIXME: what to do? wait a little and retry? 
    else
	  container_RmBall(container);
    /* get the ball and find a new empty position */
	bar_FindEmptyPos();
	count--;
  }
  /*  6 */
  go_to(container);
  rouleau_lock();
}

/* defend the base !!!!
 */
void do_defend()
{
	/* donne tout */;
}


/* End of file deplacement.c */
