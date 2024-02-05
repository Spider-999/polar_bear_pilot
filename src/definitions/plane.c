#include "plane.h"

// ----------------------------------------------------------------------------------
// Global functions used in game.c
// ----------------------------------------------------------------------------------
void CreatePlane(void)
{
	// Plane texture
	plane.texture.entityTexture	 	   = LoadTexture("graphics/plane.png");
	plane.texture.entityTexture.width  = PLANE_WIDTH;
	plane.texture.entityTexture.height = PLANE_HEIGHT;
	plane.texture.frameBody.x		   = 0.0f;
	plane.texture.frameBody.y		   = 0.0f;
	plane.texture.frameBody.width	   = (float)plane.texture.entityTexture.width / 4;
	plane.texture.frameBody.height	   = (float)plane.texture.entityTexture.height;
	plane.texture.frames			   = 0;
	plane.texture.currentFrame	       = 0;

	// Sound initialization
	plane.plane_sounds[0] = LoadSound("sounds/player_death.wav");
	plane.plane_sounds[1] = LoadSound("sounds/player_reload.wav");

	// Plane body
	plane.reload		   = MAX_PROJECTILES;
	plane.score			   = 0;
	plane.highscore        = 0;
	plane.timer			   = 0;
	plane.gameTime         = 0;
	plane.timeSinceRestart = 0;

	// Plane properties
	plane.properties.body.x		 = PLANE_POS_X;
	plane.properties.body.y		 = PLANE_POS_Y;
	plane.properties.body.width  = PLANE_RECT_WIDTH;
	plane.properties.body.height = PLANE_RECT_HEIGHT;
	plane.properties.speed.x	 = PLANE_SPEED;
	plane.properties.speed.y	 = PLANE_SPEED;
	plane.properties.health		 = PLANE_ALIVE;
}

void DrawPlane(void)
{
	if (plane.properties.health == PLANE_ALIVE)
	{
		plane.texture.frames++;

		if (plane.texture.frames >= (FPS / FRAME_SPEED))
		{
			plane.texture.frames = 0;

			if (plane.texture.currentFrame > 4)
				plane.texture.currentFrame = 0;

			plane.texture.frameBody.x = (float)plane.texture.currentFrame * (float)plane.texture.entityTexture.width / 4;
			plane.texture.currentFrame++;
		}

		plane.properties.position.x = plane.properties.body.x;
		plane.properties.position.y = plane.properties.body.y;
		DrawTextureRec(plane.texture.entityTexture, plane.texture.frameBody, plane.properties.position, WHITE);
		// DrawRectangleLines(plane.properties.position.x, plane.properties.position.y, PLANE_RECT_WIDTH, PLANE_RECT_HEIGHT, RED);
	}
}

void UpdatePlane(void)
{
	MovePlane();
	CollisionPlane();
	ShootPlane();
}

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------
static void MovePlane(void)
{
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
		plane.properties.body.x += plane.properties.speed.x;
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
		plane.properties.body.y += plane.properties.speed.y;
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
		plane.properties.body.x -= plane.properties.speed.x;
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
		plane.properties.body.y -= plane.properties.speed.y;
}

static void ShootPlane(void)
{
	int i;
	if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && plane.reload != 0)
	{
		for (i = 0; i < MAX_PROJECTILES; i++)
		{
			if (projectile[i].fire != 1)
			{
				projectile[i].body.x = plane.properties.body.x + 50;
				projectile[i].body.y = plane.properties.body.y + 50;
				projectile[i].fire = 1;
				PlaySound(shootSound);
				plane.reload--;
				break;
			}
		}
	}
	else if (plane.reload == 0)
	{
		ReloadProjectile();
	}
}

static void CollisionPlane(void)
{
	// Wall collision
	if (plane.properties.body.x <= 0)
		plane.properties.body.x = 0;
	if (plane.properties.body.x >= WINDOW_WIDTH / 3)
		plane.properties.body.x = WINDOW_WIDTH / 3;
	if (plane.properties.body.y <= WINDOW_HEIGHT / 8)
		plane.properties.body.y = WINDOW_HEIGHT / 8;
	if (plane.properties.body.y + plane.properties.body.height >= WINDOW_HEIGHT)
		plane.properties.body.y = WINDOW_HEIGHT - plane.properties.body.height;

	// Enemy collision
	int i;
	for (i = 0; i < MAX_ENEMIES; i++)
	{
		if (plane.properties.health == PLANE_ALIVE &&
			enemy[i].properties.health  == ENEMY_ALIVE      &&
			CheckCollisionRecs(plane.properties.body, enemy[i].properties.body))
		{
			plane.properties.health = PLANE_DEAD;
			PlaySound(plane.plane_sounds[0]);
			for(i = 0; i < MAX_ENEMIES; i++)
				enemy[i].properties.health  = ENEMY_DEAD;
			break;
		}
	}
}
