#include "game.h"

// ----------------------------------------------------------------------------------
// Global functions used in main.c
// ----------------------------------------------------------------------------------

void InitializeGame(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	// Window variables init
	WINDOW_WIDTH = 1280;
	WINDOW_HEIGHT = 920;
	OLD_WINDOW_WIDTH = WINDOW_WIDTH;
	OLD_WINDOW_HEIGHT = WINDOW_HEIGHT;

	// Text variables init
	TEXT_FONT_SIZE = 40;
	TEXT_FONT_SIZE2 = 60;
	SCALE_X = 1;
	SCALE_Y = 1;
	PADDING = WINDOW_HEIGHT / 8;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "POLARBEAR PILOT");
	SetWindowMinSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	InitAudioDevice();
	CreateElements();

	SetTargetFPS(FPS);
};

void RunGame(void)
{
	Menu option = MENU;
	Stage stage = STAGE1;
	int *timeSinceScore = 0;
	int previousStage = stage;
	// Game loop
	while (!WindowShouldClose())
	{
		PlayMusicStream(gameMusic);
		switch (option)
		{
			case RUN:
				ResumeMusicStream(gameMusic);
				while (option == RUN)
				{
					UpdateMusicStream(gameMusic);
					BeginDrawing();
					ClearBackground(LIGHTGRAY);

					ScrollBackground();
					RunCase(&option, &stage, &previousStage, &timeSinceScore);

					DrawElements(stage);
					UpdateElements(stage);

					EndDrawing();
				}
				break;
			case MENU:
				// PauseMusicStream(gameMusic);
				// I could've used GetFrameTime() but I didn't know it existed when I wrote this time reset code
				plane.timeSinceRestart = GetTime();
				option = DrawMenu();
				break;
			case PAUSE:
				// PauseMusicStream(gameMusic);
				plane.timeSincePause = GetTime() - plane.timeSinceRestart;
				option = DrawMenu();
				break;
			case RESTART:
				UnloadData();
				CreateElements();
				stage = STAGE1;
				previousStage = stage;
				option = RUN;
				timeSinceScore = 0;
				plane.timeSinceRestart = GetTime();
				break;
			case SETTINGS:
				// PauseMusicStream(gameMusic);
				option = DrawSettingsMenu();
				break;
			case WIN:
				option = DrawWinMenu();
				break;
			case QUIT:
				CloseWindow();
				break;
			default:
				CloseWindow();
				break;
		}
	}
	
	CloseAudioDevice();
	UnloadData();
}

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------

static void ScrollBackground(void)
{
	scrollingBackground -= 1.5f;
	scrollingForeground -= 2.0f;
	if (scrollingForeground <= -foreground.width * 2) scrollingForeground = 0;
	if (scrollingBackground <= -background.width * 2) scrollingBackground = 0;
	DrawTextureEx(background, (Vector2) { scrollingBackground, WINDOW_HEIGHT - background.height }, 0.0f, 2.0f, WHITE);
	DrawTextureEx(background, (Vector2) { background.width * 2 + scrollingBackground, WINDOW_HEIGHT - background.height }, 0.0f, 2.0f, WHITE);
	DrawTextureEx(foreground, (Vector2) { scrollingForeground, WINDOW_HEIGHT - foreground.height }, 0.0f, 2.0f, WHITE);
	DrawTextureEx(foreground, (Vector2) { foreground.width * 2 + scrollingForeground, WINDOW_HEIGHT - foreground.height }, 0.0f, 2.0f, WHITE);

}

static void CreateElements(void)
{
	// Load game music and button sounds
	gameMusic = LoadMusicStream("sounds/game_music.wav");
	buttonSelect0 = LoadSound("sounds/button_select0.wav");
	buttonSelect1 = LoadSound("sounds/button_select1.wav");

	// Font defined up to 255 characters
	font1 = LoadFont("fonts/font4.ttf", TEXT_FONT_SIZE2, 0, 255);

	// Sound variables init
	float musicVolume = 1.0f;
	float gameSounds = 1.0f;
	
	// Window icon image
	icon = LoadImage("graphics/icon.ico");
	SetWindowIcon(icon);

	// Background
	background = LoadTexture("graphics/background.png");
	background.width = WINDOW_WIDTH;
	background.height = WINDOW_HEIGHT / 2;
	scrollingBackground = 0.0f;

	foreground = LoadTexture("graphics/foreground.png");
	foreground.width = WINDOW_WIDTH;
	foreground.height = WINDOW_HEIGHT / 3;
	scrollingForeground = 0.0f;

	// Create objects
	CreatePlane();
	CreateProjectiles();
	CreateEnemy();
	CreatePenguin();
}

static void DrawElements(Stage stage)
{
	if ((stage + 1) % (STAGE4 + 1) != 0)
	{
		DrawPlane();
		DrawEnemy();
		DrawGameBar();
	}
	else
	{
		DrawPlane();
		DrawPenguin();
		DrawGameBar();
	}
}

static void UpdateElements(Stage stage)
{
	if (plane.properties.health == PLANE_ALIVE)
	{
		if ((stage + 1) % (STAGE4 + 1) != 0)
		{
			UpdatePlane();
			UpdateProjectile();
			UpdateEnemy();
		}
		else
		{
			UpdatePlane();
			UpdateProjectile();
			UpdatePenguin();
		}
	}
}

static void UnloadData(void)
{
	int i;
	// Unload textures
	UnloadTexture(plane.texture.entityTexture);
	UnloadTexture(penguin.texture.entityTexture);
	UnloadTexture(foreground);
	UnloadTexture(background);
	for (i = 0; i < MAX_ENEMIES; i++)
	{
		UnloadTexture(enemy[i].texture.entityTexture);
	}
	for (i = 0; i < PENGUIN_PROJECTILES; i++)
	{
		UnloadTexture(penguin.projectile[i].texture.entityTexture);
	}

	// Unload fonts
	UnloadFont(font1);

	// Unload sounds
	UnloadMusicStream(gameMusic);
	UnloadSound(buttonSelect0);
	UnloadSound(buttonSelect1);
	UnloadSound(shootSound);
	UnloadSound(penguinDeath);
	UnloadSound(plane.plane_sounds[0]);
	UnloadSound(plane.plane_sounds[1]);

	UnloadImage(icon);
}
