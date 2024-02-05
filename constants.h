#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window size variables
int OLD_WINDOW_WIDTH;
int OLD_WINDOW_HEIGHT;
int WINDOW_WIDTH;
int WINDOW_HEIGHT;
int SCALE_X;
int SCALE_Y;
int PADDING;

// FPS variable
#define FPS		    60
#define FRAME_SPEED 15

// Plane constants (player constants)
#define PLANE_POS_X		  1
#define PLANE_POS_Y		  (WINDOW_HEIGHT / 2)
#define PLANE_WIDTH		  500
#define PLANE_HEIGHT	  100
#define PLANE_RECT_WIDTH  100
#define PLANE_RECT_HEIGHT 80
#define PLANE_SPEED		  5
#define PLANE_COLOR		  BLUE
#define RELOAD_TIME	      1.5
#define PLANE_ALIVE		  1
#define PLANE_DEAD		  0

// Projectile constants
#define MAX_PROJECTILES	  10
#define PROJECTILE_WIDTH  80
#define PROJECTILE_HEIGHT 50
#define PROJECTILE_SPEED  12

// Enemy constants
#define MAX_ENEMIES		  20
#define ENEMY_WIDTH		  380
#define ENEMY_HEIGHT	  80
#define ENEMY_RECT_WIDTH  80
#define ENEMY_RECT_HEIGHT 50
#define ENEMY_SPEED		  8
#define ENEMY_COLOR		  RED
#define ENEMY_ALIVE		  1
#define ENEMY_DEAD		  0

// Penguin boss constants
#define PENGUIN_PROJECTILES 1
#define PENGUIN_PROJECTILE_SPEED 6
#define PENGUIN_WIDTH	   150
#define PENGUIN_HEIGHT	   150
#define PENGUIN_HEALTH      100
#define PENGUIN_DEAD        0
#define PENGUIN_SPEED       5

// Text variables
int TEXT_FONT_SIZE;
int TEXT_FONT_SIZE2;
#define FONT_SPACING 8

// Sound variables
float musicVolume;
float gameSounds;

#endif