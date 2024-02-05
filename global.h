#ifndef GLOBAL_H
#define GLOBAL_H

#include "raylib.h"
#include "raymath.h"

#include "constants.h"

#include "stdlib.h"

// ----------------------------------------------------------------------------------
// Struct definitions used in multiple modules
// ----------------------------------------------------------------------------------

typedef struct EntityProperties
{
	int		  health;
	Vector2   position;
	Vector2	  speed;
	Rectangle body;
}EntityProperties;

typedef struct EntityTexture
{
	Rectangle	 frameBody;
	Texture2D	 entityTexture;
	unsigned int frames;
	unsigned int currentFrame;
}EntityTexture;

typedef struct Plane
{
	EntityTexture	 texture;
	EntityProperties properties;
	Sound			 plane_sounds[2];
	unsigned int	 reload;
	double			 timer;		       // used for reload
	int  	         gameTime;	       // used to keep track of in-game time
	int			     timeSinceRestart; // used to restart the game time variable
	int				 timeSincePause;
	int				 score;
	int				 highscore;
}Plane;

typedef struct Projectile
{
	EntityTexture texture;
	Rectangle     body;
	Vector2		  speed;
	Vector2		  position;
	Vector2       direction;
	float         rotation;
	float		  distance;
	Color	      color;
	double		  timer;
	unsigned int  fire;
	unsigned int  inactive;
}Projectile;

typedef struct Enemy
{
	EntityProperties properties;
	EntityTexture    texture;
}Enemy;

typedef struct Boss
{
	EntityProperties properties;
	EntityTexture	 texture;
	Projectile       projectile[PENGUIN_PROJECTILES];
	double           movementTimer;
	double			 projectileTimer; // Used to spawn only one projectile at a time in ShootWalrus()
	int				 activate;
}Boss;


// ----------------------------------------------------------------------------------
// Enum definitions used in game.c
// ----------------------------------------------------------------------------------
typedef enum Menu
{
	QUIT = -1, PAUSE = 0, RUN = 1, RESTART = 2, MENU = 3, WIN = 4, SETTINGS = 5
} Menu;

typedef enum Stage
{
	STAGE1 = 0, STAGE2 = 1, STAGE3 = 2, STAGE4 = 3
}Stage;

typedef enum Level
{
	LEVEL1 = 0, LEVEL2 = 1, LEVEL3 = 2
}Level;

// ----------------------------------------------------------------------------------
// Global variables used in multiple modules
// ----------------------------------------------------------------------------------
Plane	   plane;
Enemy	   enemy[MAX_ENEMIES];
Boss       penguin;
Projectile projectile[MAX_PROJECTILES];

 /*I didn't put the sounds in the Enemy / Projectile structs, because if I did that,
 every projectile and enemy would've gotten the sound, thus more space would be occupied,
 I need only one sound object so I put them outside of the structs.*/
Music gameMusic;
Sound penguinDeath;
Sound shootSound;
Sound buttonSelect0;
Sound buttonSelect1;

// Font
Font font1;
Vector2 fontMeasure;

// Textures
float scrollingForeground;
float scrollingBackground;
Texture2D background;
Texture2D foreground;

// Images
Image icon;

#endif
