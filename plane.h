#ifndef PLANE_H
#define PLANE_H

#include     "global.h"
#include  "constants.h"
#include "projectile.h"

#include	  <stdio.h>

// ----------------------------------------------------------------------------------
// Global functions used in game.c
// ----------------------------------------------------------------------------------
void	CreatePlane(void);
void	  DrawPlane(void);
void	UpdatePlane(void);

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------
static void	  MovePlane(void);
static void ShootPlane(void);
static void CollisionPlane(void);

#endif 