 /*
* File Name          : divers.h
* Author             : Xt-6
* Date First Issued  : 03/02/2008 : Version 1.0
* Description        : regroupe les fonctions de configurations de la carte
********************************************************************************
* History:
*
*******************************************************************************/

#include "91x_lib.h"


#define COEF_SON 3.43
#define DO_0   524280/264*COEF_SON
#define DO_0d  524280/280*COEF_SON
#define RE_0   524280/297*COEF_SON
#define RE_0d  524280/315*COEF_SON
#define MI_0   524280/330*COEF_SON
#define FA_0   524280/352*COEF_SON
#define FA_0d  524280/372*COEF_SON
#define SOL_0  524280/396*COEF_SON
#define SOL_0d 524280/420*COEF_SON
#define LA_0   524280/440*COEF_SON
#define LA_0d  524280/466*COEF_SON
#define SI_0   524280/495*COEF_SON

#define DO_1   524280/528*COEF_SON
#define DO_1d  524280/559*COEF_SON
#define RE_1   524280/594*COEF_SON
#define RE_1d  524280/629*COEF_SON
#define MI_1   524280/660*COEF_SON
#define FA_1   524280/704*COEF_SON
#define FA_1d  524280/745*COEF_SON
#define SOL_1  524280/792*COEF_SON
#define SOL_1d 524280/839*COEF_SON
#define LA_1   524280/880*COEF_SON
#define LA_1d  524280/932*COEF_SON
#define SI_1   524280/990*COEF_SON

#define REF_TPS 52428*COEF_SON // 1/10 sec


void Jouer_note(u32 freq, u32 duree);

static void Delay(u32 nCount);

void Depart(void);
