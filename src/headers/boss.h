#ifndef BOSS_H
#define BOSS_H

#include "global.h"
#include <math.h>

// ----------------------------------------------------------------------------------
// Global functions used in game.c
// ----------------------------------------------------------------------------------
void CreatePenguin(void);
void   DrawPenguin(void);
void UpdatePenguin(void);

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------
static void	    DrawBossHealthBar(void);
static void DrawPenguinProjectile(void);
static void			  MovePenguin(void);
static void			 ShootPenguin(void);
static void		 CollisionPenguin(void);

#endif 
