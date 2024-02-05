#ifndef ENEMY_H
#define ENEMY_H

#include "plane.h"

// ----------------------------------------------------------------------------------
// Global functions used in game.c
// ----------------------------------------------------------------------------------
void  CreateEnemy(void);
void    DrawEnemy(void);
void  UpdateEnemy(void);
void RespawnEnemy(void);

// ----------------------------------------------------------------------------------
// Local function used in this module
// ----------------------------------------------------------------------------------
static void MoveEnemy(void);

#endif