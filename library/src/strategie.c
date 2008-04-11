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

/* return the number of ball in a container 
 * the value may not be accurate (could be less than what we think)
 */
char container_count(t_container container)
{
  return mget(CONTAINER_KEY + container);
}


#define BE_SMART 1
#define LOST_THE_GAME 0
void start()
{
  if (LOST_THE_GAME)
	maximilien('eepc');
  if (BE_SMART)
	donnetout();
  else
	bfj();
}



/************************* DIFFERENTS STRATEGIES **************************/

/* Strategie: BFJ
 * BE STUPID, BE FUCKING STUPID, BUT HEY, THAT'S WORKS !!!!!!!!
 */
void bfj()
{
  do_GetBallsFloor();
  do_ExpluseBalls();
  do_GetBallsContainer(CONTAINER_TEAM, 2);
  if (bar_team_count() == 0)
	do_GetBallsContainer(CONTAINER_OPPONENT, 2);
	
  do_GetBallsContainer(CONTAINER_WHITE1, 3);
  if (!bar_Full())
	do_GetBallsContainer(CONTAINER_WHITE2, 3);
  do_ExpluseBalls();

}

/* Strategie: ChiChe, mode donne tout
 * very advanced rules !!!!
 * try to get the maximum point
 * try to defend our point
 */
void donnetout()
{
  do_GetBallsFloor();
  while (!timeout)
  {
	if (bar_Full())
	  do_ExpluseBalls();
	if (container_count(CONTAINER_TEAM) != 0)
	  do_GetBallsContainer(CONTAINER_TEAM, 5)
  }
}

/* Strategie: Maximilien
 * Very very very very advanced strategie
 * need two or three fpga to get it right
 *
 * warning: if you dont want to burn your cpu, dont call me
 * ps: It's works on my eeepc ^^
 */
#define NOT_YET_IMPLEMENTED 42
#define STUPID_BRAIN		12
int maximilien(int neurone)
{
  int rn = 'sux';
  int amistupid = 1;
  int donnetout = 0;

  rn = NOT_YET_IMPLEMENTED;
  if (neurone == STUPID_BRAIN)
	return rn;
  neurone++;
  while(amistudid)	
  {
	donnetout = maximilien(neurone);	
  }
  return NOT_YET_IMPLEMENTED;
}

/* End of file strategie.c */
