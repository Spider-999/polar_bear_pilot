#include "projectile.h"
#include <stdio.h>

// ----------------------------------------------------------------------------------
// Global functions used in game.c and plane.c
// ----------------------------------------------------------------------------------
void CreateProjectiles(void)
{
	int i;
	for (i = 0; i < MAX_PROJECTILES; i++)
	{
		// Projectile texture
		projectile[i].texture.entityTexture        = LoadTexture("graphics/fish1.png");
		projectile[i].texture.entityTexture.width  = PROJECTILE_WIDTH;
		projectile[i].texture.entityTexture.height = PROJECTILE_HEIGHT;
		projectile[i].texture.frameBody.x		   = 0.0f;
		projectile[i].texture.frameBody.y          = 0.0f;
		projectile[i].texture.frameBody.width	   = (float)projectile[i].texture.entityTexture.width;
		projectile[i].texture.frameBody.height	   = (float)projectile[i].texture.entityTexture.height;
		

		// Projectile body
		projectile[i].body.width  = PROJECTILE_WIDTH;
		projectile[i].body.height = PROJECTILE_HEIGHT;
		projectile[i].fire		  = 0;
	}
	shootSound = LoadSound("sounds/shoot.wav");
}

void UpdateProjectile(void)
{
	DrawProjectile();
	MoveProjectile();
	ProjectileCollision();
}

void ReloadProjectile(void)
{
	int i;
	if (IsKeyPressed(KEY_R))
	{
		plane.timer = GetTime();
		if(!IsSoundPlaying(plane.plane_sounds[1])) // This if makes the sound playable only once
			PlaySound(plane.plane_sounds[1]);
	}
	// Two second reload time
	if (GetTime() - plane.timer < RELOAD_TIME)
	{
		fontMeasure = MeasureTextEx(font1, "RELOADING", TEXT_FONT_SIZE, FONT_SPACING);
		DrawTextEx(font1, "RELOADING...", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x, 20 }, TEXT_FONT_SIZE, FONT_SPACING, BLACK);
	}
	if (GetTime() - plane.timer >= RELOAD_TIME && plane.timer != 0)
	{
		plane.timer  = 0;
		plane.reload = MAX_PROJECTILES;
	}
}

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------
static void MoveProjectile(void)
{
	int i;
	for (i = 0; i < MAX_PROJECTILES; i++)
	{
		if (projectile[i].fire == 1 && projectile[i].body.x < WINDOW_WIDTH)
		{
			projectile[i].body.x += PROJECTILE_SPEED;
		}
		else
		{
			projectile[i].fire = 0;
			projectile[i].speed.x = 0;
		}
	}
}

static void DrawProjectile(void)
{
	int i;
	for (i = 0; i < MAX_PROJECTILES; i++)
	{
		if (projectile[i].fire == 1)
		{
			projectile[i].position.x = projectile[i].body.x;
			projectile[i].position.y = projectile[i].body.y;
			DrawTextureRec(projectile[i].texture.entityTexture, projectile[i].texture.frameBody, projectile[i].position, WHITE);
			//DrawRectangleRec(projectile[i].body, projectile[i].color);
		}
	}
}

static void ProjectileCollision(void)
{
	int i, j;
	for (i = 0; i < MAX_PROJECTILES; i++)
	{
		if (projectile[i].fire == 1)
		{
			for (j = 0; j < MAX_ENEMIES; j++)
			{
				if (enemy[j].properties.health == ENEMY_ALIVE && CheckCollisionRecs(projectile[i].body, enemy[j].properties.body))
				{
					projectile[i].body.x = plane.properties.body.x;
					projectile[i].body.y = plane.properties.body.y;
					projectile[i].speed.x = 0;
					projectile[i].fire = 0;
					enemy[j].properties.body.x = GetRandomValue(WINDOW_WIDTH + ENEMY_WIDTH, WINDOW_WIDTH + 250);
					enemy[j].properties.body.y = GetRandomValue(0, WINDOW_HEIGHT);
					enemy[j].properties.health = ENEMY_DEAD;
					PlaySound(penguinDeath);
					plane.score += 10;
				}
			}
		}
	}
}
