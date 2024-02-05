/********************************************************************************************
* This game has been created using raylib(www.raylib.com)                                   *
* raylib is licensed under an unmodified zlib / libpng license(View raylib.h for details)   *
*                                                                                           *
* Author: Hary Patrascu                                                                     *
* Title:  Polar Pilot                                                                        *
*                                                                                           *
********************************************************************************************/
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "game.h"

int main(void)
{
    InitializeGame();
    RunGame();
    return 0;
}