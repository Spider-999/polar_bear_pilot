#ifndef GAME_H
#define GAME_H

#include "plane.h"
#include "enemy.h"
#include "boss.h"
#include "menu.h"

// ----------------------------------------------------------------------------------
// Global functions used in main.c
// ----------------------------------------------------------------------------------
void    InitializeGame(void);
void		   RunGame(void);

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------
static void ScrollBackground(void);
static void   CreateElements(void);
static void    DrawElements(Stage);
static void  UpdateElements(Stage);
static void  CheckWindowSize(void);
static void	      UnloadData(void);

#endif 