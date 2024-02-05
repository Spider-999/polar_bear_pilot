#ifndef MENU_H
#define MENU_H

#include "global.h"
#include "enemy.h"

// ----------------------------------------------------------------------------------
// Global functions used in game.c
// ----------------------------------------------------------------------------------
Menu DrawMenu(void);
Menu DrawRestartMenu(void);
Menu DrawSettingsMenu(void);
Menu DrawWinMenu(void);
void RunCase(Menu*, Stage*, int*, int*);
void DrawGameBar(void);

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------
static void SaveHighscore(void);
static void DrawHighscore(void);
static void CheckWindowSize(void);
static void ScaleUpToWindow(void);
static void ScaleDownToWindow(void);

#endif
