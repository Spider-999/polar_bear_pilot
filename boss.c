#include "boss.h"

// ----------------------------------------------------------------------------------
// Global functions used in game.c
// ----------------------------------------------------------------------------------
void CreatePenguin(void)
{
	int i;
	// Penguin texture
	penguin.texture.entityTexture = LoadTexture("graphics/boss_penguin.png");
	penguin.texture.entityTexture.width = PENGUIN_WIDTH;
	penguin.texture.entityTexture.height = PENGUIN_HEIGHT;
	penguin.texture.frameBody.x = 0.0f;
	penguin.texture.frameBody.y = 0.0f;
	penguin.texture.frameBody.width = (float)penguin.texture.entityTexture.width;
	penguin.texture.frameBody.height = (float)penguin.texture.entityTexture.height;

	// Penguin properties
	penguin.properties.body.x	  = WINDOW_WIDTH + 200;
	penguin.properties.body.y	  = WINDOW_HEIGHT / 2;
	penguin.properties.position.x  = penguin.properties.body.x;
	penguin.properties.position.y  = penguin.properties.body.y;
	penguin.properties.body.width  = PENGUIN_WIDTH;
	penguin.properties.body.height = PENGUIN_HEIGHT;
	penguin.properties.speed.x	  = PENGUIN_SPEED;
	penguin.properties.speed.y	  = PENGUIN_SPEED;
	penguin.properties.health      = PENGUIN_HEALTH;
	penguin.activate				  = 0;
	
	// Penguin projectiles
	for (i = 0; i < PENGUIN_PROJECTILES; i++)
	{
		// Penguin projectile texture 
		penguin.projectile[i].texture.entityTexture = LoadTexture("graphics/penguin_bullet.png");
		penguin.projectile[i].texture.entityTexture.width = 40;
		penguin.projectile[i].texture.entityTexture.height = 30;
		penguin.projectile[i].texture.frameBody.x = 0.0f;
		penguin.projectile[i].texture.frameBody.y = 0.0f;
		penguin.projectile[i].texture.frameBody.width = (float)penguin.projectile[i].texture.entityTexture.width;
		penguin.projectile[i].texture.frameBody.height = (float)penguin.projectile[i].texture.entityTexture.height;

		// Penguin projectile properties
		penguin.projectile[i].position.x = penguin.properties.body.x + penguin.properties.body.width / 2;
		penguin.projectile[i].position.y = penguin.properties.body.y + penguin.properties.body.height / 2;
		penguin.projectile[i].body.width  = 40;
		penguin.projectile[i].body.height = 30;
		penguin.projectile[i].fire		 = 1;
		penguin.projectile[i].inactive    = 0;
	}
	
}

void DrawPenguin(void)
{
	if (penguin.properties.health > PENGUIN_DEAD)
	{
		DrawPenguinProjectile();
		DrawTextureRec(penguin.texture.entityTexture,
			penguin.texture.frameBody,
			penguin.properties.position,
			WHITE);
		DrawBossHealthBar();
	}
}

void UpdatePenguin(void)
{
	if (penguin.properties.health > PENGUIN_DEAD)
	{
		ShootPenguin();
		MovePenguin();
		CollisionPenguin();
	}
}

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------

static void DrawBossHealthBar(void)
{
	DrawRectangleRec((Rectangle) { WINDOW_WIDTH / 2 - PENGUIN_HEALTH * 2.5, WINDOW_HEIGHT / 8 + 40, penguin.properties.health * 5, 40 }, RED);
	DrawRectangleLinesEx((Rectangle) { WINDOW_WIDTH / 2 - PENGUIN_HEALTH * 2.5, WINDOW_HEIGHT / 8 + 40, PENGUIN_HEALTH * 5, 40 }, 2, BLACK);
}

static void DrawPenguinProjectile(void)
{
	int i;
	for (i = 0; i < PENGUIN_PROJECTILES; i++)
	{
		if (penguin.projectile[i].fire == 1)
		{
			DrawTextureEx(penguin.projectile[i].texture.entityTexture, penguin.projectile[i].position, penguin.projectile[i].rotation, 2.5f, WHITE);
		}
	}
}

static void MovePenguin(void)
{
		if (penguin.properties.body.x > WINDOW_WIDTH - PENGUIN_WIDTH * 2 && penguin.activate == 0)
		{
			penguin.properties.body.x -= PENGUIN_SPEED;
		}
		else
		{
			// Figure 8 movement (research Watt's curve if you want to learn move or lemniscate figures)
			penguin.activate = 1;
			penguin.properties.body.x = 100.0f * sinf(2 * (GetTime())) + WINDOW_WIDTH - PENGUIN_WIDTH * 2;
			penguin.properties.body.y = 150.0f * 2 * cosf(GetTime()) + WINDOW_HEIGHT / 2;
		}
	
	penguin.properties.position.x = penguin.properties.body.x;
	penguin.properties.position.y = penguin.properties.body.y;
}

static void ShootPenguin(void)
{
	int i;
	for (i = 0; i < PENGUIN_PROJECTILES; i++)
	{
		if (GetTime() - penguin.projectile[i].timer >= 1)
		{
			if (penguin.projectile[i].position.x > plane.properties.position.x - 20 && penguin.projectile[i].inactive == 0)
			{
				// This math is used for the seeking projectile of the boss
				penguin.projectile[i].direction = Vector2Subtract(plane.properties.position, penguin.projectile[i].position);
				penguin.projectile[i].distance = Vector2Length(penguin.projectile[i].direction);
				if (penguin.projectile[i].distance != 0)
				{
					penguin.projectile[i].direction.x /= penguin.projectile[i].distance;
					penguin.projectile[i].direction.y /= penguin.projectile[i].distance;
				}
				penguin.projectile[i].rotation = atan2f(penguin.projectile[i].direction.y, penguin.projectile[i].direction.x) * RAD2DEG;
				penguin.projectile[i].speed.x = penguin.projectile[i].direction.x * PENGUIN_PROJECTILE_SPEED;
				penguin.projectile[i].speed.y = penguin.projectile[i].direction.y * PENGUIN_PROJECTILE_SPEED;
				penguin.projectile[i].position = Vector2Add(penguin.projectile[i].position, penguin.projectile[i].speed);
				penguin.projectile[i].body.x = penguin.projectile[i].position.x;
				penguin.projectile[i].body.y = penguin.projectile[i].position.y;
			}
			else
			{
				// If the projectile passes the plane, the guidance system becomes inactive
				// remove the inactive variable from the if and from this else branch to see
				// what happens if this variable isn't here.
				penguin.projectile[i].inactive = 1;
				penguin.projectile[i].position = Vector2Add(penguin.projectile[i].position, penguin.projectile[i].speed);
				penguin.projectile[i].body.x = penguin.projectile[i].position.x;
				penguin.projectile[i].body.y = penguin.projectile[i].position.y;
			}
		}
		else
		{
			penguin.projectile[i].position.x = penguin.properties.body.x + penguin.properties.body.width / 2;
			penguin.projectile[i].position.y = penguin.properties.body.y + penguin.properties.body.height / 2;
		}
	}
}

static void CollisionPenguin(void)
{
	int i;
	// Check for wall collision
	for (i = 0; i < PENGUIN_PROJECTILES; i++)
	{
		if (penguin.projectile[i].position.x < 0 || penguin.projectile[i].position.y >= WINDOW_HEIGHT || penguin.projectile[i].position.y < 0)
		{
			penguin.projectile[i].position.x = penguin.properties.body.x + penguin.properties.body.height / 2;
			penguin.projectile[i].position.y = penguin.properties.body.y + penguin.properties.body.height / 2;
			penguin.projectile[i].body.x = penguin.properties.body.x + penguin.properties.body.height / 2;
			penguin.projectile[i].body.y = penguin.properties.body.y + penguin.properties.body.height / 2;
			penguin.projectile[i].inactive = 0;
			penguin.projectile[i].timer = GetTime();
		}
	}
	
	// Check for plane projectile collision with the boss
	for (i = 0; i < MAX_PROJECTILES; i++)
	{
		if (penguin.activate == 1 && penguin.properties.health > PENGUIN_DEAD && CheckCollisionRecs(penguin.properties.body, projectile[i].body))
		{
			projectile[i].body.x = plane.properties.body.x;
			projectile[i].body.y = plane.properties.body.y;
			projectile[i].speed.x = 0;
			projectile[i].fire = 0;
			penguin.properties.health -= 5;
			PlaySound(penguinDeath);
			plane.score += 10;
		}
	}

	for (i = 0; i < PENGUIN_PROJECTILES; i++)
	{
		if (CheckCollisionRecs(penguin.projectile[i].body, plane.properties.body))
		{
			plane.properties.health = PLANE_DEAD;
		}
	}
}
