#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "global.h"

// ----------------------------------------------------------------------------------
// Global functions used in game.c and plane.c
// ----------------------------------------------------------------------------------
void   CreateProjectiles(void);
void    UpdateProjectile(void);
void    ReloadProjectile(void);

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------
static void ProjectileCollision(void);
static void	  MoveProjectile(void);
static void      DrawProjectile(void);

#endif