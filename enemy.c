#include "enemy.h"

// ----------------------------------------------------------------------------------
// Global functions used in game.c
// ----------------------------------------------------------------------------------
void CreateEnemy(void)
{
	int i;
	for (i = 0; i < MAX_ENEMIES; i++)
	{
		// Enemy texture
		enemy[i].texture.entityTexture        = LoadTexture("graphics/penguin.png");
		enemy[i].texture.entityTexture.width  = ENEMY_WIDTH;
		enemy[i].texture.entityTexture.height = ENEMY_HEIGHT;
		enemy[i].texture.frameBody.x		 = 0.0f;
		enemy[i].texture.frameBody.y		 = 0.0f;
		enemy[i].texture.frameBody.width     = (float)enemy[i].texture.entityTexture.width / 3;
		enemy[i].texture.frameBody.height    = (float)enemy[i].texture.entityTexture.height;
		enemy[i].texture.frames = 0;
		enemy[i].texture.currentFrame = 0;

		// Enemy Properties
		enemy[i].properties.body.x			     = GetRandomValue(WINDOW_WIDTH, WINDOW_WIDTH * 2);
		enemy[i].properties.body.y			     = GetRandomValue(PADDING, WINDOW_HEIGHT - PADDING);
		enemy[i].properties.body.width			 = ENEMY_RECT_WIDTH;
		enemy[i].properties.body.height			 = ENEMY_RECT_HEIGHT;
		enemy[i].properties.speed.x				 = ENEMY_SPEED;
		enemy[i].properties.speed.y				 = ENEMY_SPEED;
		enemy[i].properties.health				 = ENEMY_ALIVE;
	}
	// Sound initialization, there is no point in loading the same sound for each individual enemy
	penguinDeath = LoadSound("sounds/penguin_death.wav");
}

void DrawEnemy(void)
{
	int i;
	for (i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemy[i].properties.health == ENEMY_ALIVE)
		{
			enemy[i].texture.frames++;
			if (enemy[i].texture.frames >= (FPS / FRAME_SPEED))
			{
				enemy[i].texture.frames = 0;
				if (enemy[i].texture.currentFrame > 4)
					enemy[i].texture.currentFrame = 0;
				enemy[i].texture.frameBody.x = (float)enemy[i].texture.currentFrame * (float)enemy[i].texture.entityTexture.width / 3;
				enemy[i].texture.currentFrame++;
			}
			enemy[i].properties.position.x = enemy[i].properties.body.x;
			enemy[i].properties.position.y = enemy[i].properties.body.y;
			DrawTextureRec(enemy[i].texture.entityTexture, enemy[i].texture.frameBody, enemy[i].properties.position, WHITE);
			// DrawRectangleLines(enemy[i].properties.body.x, enemy[i].properties.body.y, ENEMY_RECT_WIDTH, ENEMY_RECT_HEIGHT, RED);
		}
	}
}

void UpdateEnemy(void)
{
	MoveEnemy();
}

void RespawnEnemy(void)
{
	int i;
	for (i = 0; i < MAX_ENEMIES; i++)
	{
		enemy[i].properties.body.x = GetRandomValue(WINDOW_WIDTH, WINDOW_WIDTH * 2);
		enemy[i].properties.body.y = GetRandomValue(PADDING, WINDOW_HEIGHT - PADDING);
		enemy[i].properties.health = ENEMY_ALIVE;
	}
}

// ----------------------------------------------------------------------------------
// Local function used in this module
// ----------------------------------------------------------------------------------
static void MoveEnemy(void)
{
	int i;
	for (i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemy[i].properties.health == ENEMY_ALIVE)
		{
			if (enemy[i].properties.body.x > -ENEMY_WIDTH)
				enemy[i].properties.body.x -= enemy[i].properties.speed.x;
			else
			{
				enemy[i].properties.body.x = GetRandomValue(WINDOW_WIDTH, WINDOW_WIDTH * 2);
				enemy[i].properties.body.y = GetRandomValue(PADDING, WINDOW_HEIGHT - PADDING);
			}
		}
	}
}
