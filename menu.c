#include "menu.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// ----------------------------------------------------------------------------------
// Global functions used in game.c
// ----------------------------------------------------------------------------------

Menu DrawMenu(void)
{
	Menu option = PAUSE, selection = RUN;
	
	SaveHighscore();

	while (option == PAUSE)
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawHighscore();
		
		if (selection == RUN)
		{
			fontMeasure = MeasureTextEx(font1, "PLAY", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "PLAY", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 - 3 * fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, WHITE);

			fontMeasure = MeasureTextEx(font1, "SETTINGS", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "SETTINGS", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 - fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);

			fontMeasure = MeasureTextEx(font1, "QUIT", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "QUIT", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x, WINDOW_HEIGHT / 2 + fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);
		}
		else if (selection == SETTINGS)
		{
			fontMeasure = MeasureTextEx(font1, "PLAY", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "PLAY", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x, WINDOW_HEIGHT / 2 - 3 * fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);

			fontMeasure = MeasureTextEx(font1, "SETTINGS", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "SETTINGS", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 3, WINDOW_HEIGHT / 2 - fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, WHITE);

			fontMeasure = MeasureTextEx(font1, "QUIT", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "QUIT", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x, WINDOW_HEIGHT / 2 + fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);
		}
		else if (selection == QUIT)
		{
			fontMeasure = MeasureTextEx(font1, "PLAY", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "PLAY", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x, WINDOW_HEIGHT / 2 - 3 * fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);

			fontMeasure = MeasureTextEx(font1, "SETTINGS", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "SETTINGS", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 - fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);

			fontMeasure = MeasureTextEx(font1, "QUIT", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "QUIT", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 + fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, WHITE);
		}

		if (IsKeyPressed(KEY_DOWN) && selection == RUN)
		{
			PlaySound(buttonSelect1);
			selection = SETTINGS;
		}
		else if (IsKeyPressed(KEY_DOWN) && selection == SETTINGS)
		{
			PlaySound(buttonSelect1);
			selection = QUIT;
		}
		else if (IsKeyPressed(KEY_UP) && selection == SETTINGS)
		{
			PlaySound(buttonSelect1);
			selection = RUN;
		}
		else if (IsKeyPressed(KEY_UP) && selection == QUIT)
		{
			PlaySound(buttonSelect1);
			selection = SETTINGS;
		}

		if (IsKeyPressed(KEY_ENTER) && selection == RUN)
		{
			option = RUN;
		}
		if (IsKeyPressed(KEY_ENTER) && selection == SETTINGS)
		{
			option = SETTINGS;
		}
		if (IsKeyPressed(KEY_ENTER) && selection == QUIT)
		{
			option = QUIT;
		}

		EndDrawing();
	}
	// Pause duration
	plane.timeSinceRestart = GetTime() - plane.timeSincePause;
	PlaySound(buttonSelect0);
	WaitTime(0.5);
	return option;
}

Menu DrawRestartMenu(void)
{
	Menu option = RUN, selection = RESTART;
	SaveHighscore();

	while (option != RESTART && option != QUIT)
	{
		BeginDrawing();

		ClearBackground(DARKGRAY);
		CheckWindowSize();

		fontMeasure = MeasureTextEx(font1, "GAME OVER", TEXT_FONT_SIZE2, FONT_SPACING);
		DrawTextEx(font1, "GAME OVER", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 - 3 * fontMeasure.y}, TEXT_FONT_SIZE2, FONT_SPACING, BLACK);
		DrawHighscore();

		if (selection == RESTART)
		{
			fontMeasure = MeasureTextEx(font1, "RESTART", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "RESTART", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 3, WINDOW_HEIGHT / 2 - fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, WHITE);

			fontMeasure = MeasureTextEx(font1, "QUIT", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "QUIT", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x, WINDOW_HEIGHT / 2 + fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);
		}
		else if (selection == QUIT)
		{
			fontMeasure = MeasureTextEx(font1, "RESTART", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "RESTART", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 - fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);

			fontMeasure = MeasureTextEx(font1, "QUIT", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "QUIT", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 + fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, WHITE);
		}

		if (IsKeyPressed(KEY_DOWN) && selection == RESTART)
		{
			selection = QUIT;
			PlaySound(buttonSelect0);
		}
		else if (IsKeyPressed(KEY_UP) && selection == QUIT)
		{
			selection = RESTART;
			PlaySound(buttonSelect0);
		}

		if (IsKeyPressed(KEY_ENTER) && selection == RESTART)
		{
			option = RESTART;
		}
		if (IsKeyPressed(KEY_ENTER) && selection == QUIT)
		{
			option = QUIT;
		}
		EndDrawing();
	}
	PlaySound(buttonSelect1);
	WaitTime(0.5);
	return option;
}

Menu DrawSettingsMenu(void)
{
	Menu option = SETTINGS;
	GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

	while (option == SETTINGS)
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText("SOUND SETTINGS", PADDING * 2, PADDING / 2, TEXT_FONT_SIZE2, WHITE);
		GuiSliderBar((Rectangle) { PADDING * 2, PADDING, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 10 }, "MUSIC VOLUME:", NULL, &musicVolume, 0.0f, 1.0f);
		GuiSliderBar((Rectangle) { PADDING * 2, PADDING * 2, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 10 }, "GAME VOLUME:", NULL, &gameSounds, 0.0f, 1.0f);

		if (GuiButton((Rectangle) { WINDOW_WIDTH / 2 - PADDING, WINDOW_HEIGHT - WINDOW_HEIGHT / 8, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 10 }, "BACK"))
		{
			PlaySound(buttonSelect1);
			WaitTime(0.5);
			option = MENU;
		}

		EndDrawing();
	}
	
	SetMusicVolume(gameMusic, musicVolume);
	SetSoundVolume(penguinDeath, gameSounds);
	SetSoundVolume(shootSound, gameSounds);
	SetSoundVolume(plane.plane_sounds[0], gameSounds);
	SetSoundVolume(plane.plane_sounds[1], gameSounds);
	
	return option;
}

// This function is now not used because I made the game playable until the player dies
Menu DrawWinMenu(void)
{
	Menu option = RUN, selection = RESTART;

	while (option != RESTART && option != QUIT)
	{
		BeginDrawing();

		ClearBackground(Fade((Color){ 229, 228, 226 }, 0.8f));
		CheckWindowSize();

		fontMeasure = MeasureTextEx(font1, "YOU WON!", TEXT_FONT_SIZE2, FONT_SPACING);
		DrawTextEx(font1, "YOU WON!", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 - 3 * fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, BLACK);

		if (selection == RESTART)
		{
			fontMeasure = MeasureTextEx(font1, "REPLAY", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "REPLAY", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 3, WINDOW_HEIGHT / 2 - fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, WHITE);

			fontMeasure = MeasureTextEx(font1, "QUIT", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "QUIT", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x, WINDOW_HEIGHT / 2 + fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);
		}
		else if (selection == QUIT)
		{
			fontMeasure = MeasureTextEx(font1, "REPLAY", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "REPLAY", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 - fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, GRAY);

			fontMeasure = MeasureTextEx(font1, "QUIT", TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, "QUIT", (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 + fontMeasure.y }, TEXT_FONT_SIZE2, FONT_SPACING, WHITE);
		}

		if (IsKeyPressed(KEY_DOWN) && selection == RESTART)
		{
			selection = QUIT;
			PlaySound(buttonSelect1);
		}
		if (IsKeyPressed(KEY_UP) && selection == QUIT)
		{
			selection = RESTART;
			PlaySound(buttonSelect1);
		}

		if (IsKeyPressed(KEY_ENTER) && selection == RESTART)
		{
			PlaySound(buttonSelect0);
			WaitTime(0.25f);
			option = RESTART;
		}
		else if (IsKeyPressed(KEY_ENTER) && selection == QUIT)
		{
			PlaySound(buttonSelect0);
			WaitTime(0.25f);
			option = QUIT;
		}
		EndDrawing();
	}

	return option;
}

void RunCase(Menu *option, Stage *stage, int *previousStage, int *timeSinceScore)
{
		plane.gameTime = GetTime() - plane.timeSinceRestart;

		if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE))
		{
			PauseMusicStream(gameMusic);
			*option = PAUSE;
		}

		if (plane.properties.health == PLANE_DEAD)
		{
			PauseMusicStream(gameMusic);
			*option = DrawRestartMenu();
		}
		
		if (plane.score == (*previousStage + 1) * MAX_ENEMIES * 10 && ((*stage + 1) % (STAGE4 + 1)) != 0)
		{
			if (*timeSinceScore == 0)
			{
				*timeSinceScore = (GetTime() - plane.timeSinceRestart);
			}

			if (*previousStage == *stage)
				(*stage)++;

			if (plane.gameTime - *timeSinceScore >= 3)
			{
				RespawnEnemy();
				*timeSinceScore = 0;
				*previousStage = *stage;
			}

			if (((*stage + 1) % (STAGE4 + 1)) == 0)
			{
				penguin.properties.body.x = WINDOW_WIDTH + 200;
				penguin.properties.body.y = WINDOW_HEIGHT / 2;
				penguin.properties.position.x = penguin.properties.body.x;
				penguin.properties.position.y = penguin.properties.body.y;
				penguin.properties.health = 100;
				penguin.activate = 0;

				penguin.projectile[0].position.x = penguin.properties.body.x + penguin.properties.body.height / 2;
				penguin.projectile[0].position.y = penguin.properties.body.y + penguin.properties.body.height / 2;
				penguin.projectile[0].body.x = penguin.properties.body.x + penguin.properties.body.height / 2;
				penguin.projectile[0].body.y = penguin.properties.body.y + penguin.properties.body.height / 2;
				penguin.projectile[0].inactive = 0;
				penguin.projectile[0].timer = GetTime();
			}
		}

		if (penguin.properties.health <= PENGUIN_DEAD && ((*stage + 1) % (STAGE4 + 1)) == 0)
		{
			if (*timeSinceScore == 0)
			{
				*timeSinceScore = (GetTime() - plane.timeSinceRestart);
			}
			
			if (*previousStage == *stage)
				(*stage)++;

			if (plane.gameTime - *timeSinceScore >= 3)
			{
				*timeSinceScore = 0;
				*previousStage = *stage;
			}
		}

		if (plane.gameTime - *timeSinceScore <= 3)
		{
			fontMeasure = MeasureTextEx(font1, TextFormat("STAGE %04i"), TEXT_FONT_SIZE, FONT_SPACING);
			DrawTextEx(font1, TextFormat("STAGE %04i", *stage + 1), (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 3, WINDOW_HEIGHT / 3 }, TEXT_FONT_SIZE, FONT_SPACING, Fade(BLACK, 0.5f));
		}
}

void DrawGameBar(void)
{
	int i;
	DrawLineEx((Vector2) { 0, WINDOW_HEIGHT / 8 }, (Vector2) { WINDOW_WIDTH, WINDOW_HEIGHT / 8 }, 4, BLACK);
	fontMeasure = MeasureTextEx(font1, TextFormat("SCORE:%04i"), TEXT_FONT_SIZE, FONT_SPACING);

	DrawTextEx(font1, TextFormat("SCORE:%04i", plane.score), (Vector2) { 20, WINDOW_HEIGHT / 8 - fontMeasure.y}, TEXT_FONT_SIZE, FONT_SPACING, BLACK);
	fontMeasure = MeasureTextEx(font1, TextFormat("TIME:%04i"), TEXT_FONT_SIZE, FONT_SPACING);
	DrawTextEx(font1, TextFormat("TIME:%04i", plane.gameTime), (Vector2) { WINDOW_WIDTH - 10 * TEXT_FONT_SIZE, 20 }, TEXT_FONT_SIZE, FONT_SPACING, BLACK);

	fontMeasure = MeasureTextEx(font1, TextFormat("FPS:%04i"), TEXT_FONT_SIZE2, FONT_SPACING);
	DrawTextEx(font1, TextFormat("FPS:%04i", GetFPS()), (Vector2) { WINDOW_WIDTH - 10 * TEXT_FONT_SIZE, 60 }, TEXT_FONT_SIZE, FONT_SPACING, BLACK);

	fontMeasure = MeasureTextEx(font1, TextFormat("AMMO:"), TEXT_FONT_SIZE2, FONT_SPACING);
	DrawTextEx(font1, "AMMO:", (Vector2) {20 , 20 }, TEXT_FONT_SIZE, FONT_SPACING, BLACK);
	for (i = 0; i < plane.reload; i++)
		DrawRectangle(fontMeasure.x - 40 + i * 20, TEXT_FONT_SIZE / 2 + 10, 10, 20, BLUE);
}

// ----------------------------------------------------------------------------------
// Local functions used in this module
// ----------------------------------------------------------------------------------

static void SaveHighscore(void)
{
	// This function is used at the start of DrawRestartMenu()
	FILE *highscoreFile = NULL;
	highscoreFile = fopen("highscore.txt", "r+");
	
	if (highscoreFile == NULL)
	{
		printf("Error opening the file %s", "highscore.txt");
		exit(0);
	}

	fseek(highscoreFile, 0, SEEK_SET);
	fscanf(highscoreFile, "%d", &plane.highscore);

	if (plane.score >= plane.highscore)
	{
		// Save the highscore in highscore.txt
		fseek(highscoreFile, 0, SEEK_SET);
		fprintf(highscoreFile, "%d", plane.score);
		rewind(highscoreFile);
		fscanf(highscoreFile, "%d", &plane.highscore);
	}

	fclose(highscoreFile);
}

static void DrawHighscore(void)
{
	fontMeasure = MeasureTextEx(font1, TextFormat("HIGHSCORE:%04i", plane.highscore), TEXT_FONT_SIZE, FONT_SPACING);
	DrawTextEx(font1, TextFormat("HIGHSCORE:%04i", plane.highscore), (Vector2) { WINDOW_WIDTH / 2 - fontMeasure.x / 2, WINDOW_HEIGHT / 2 + 3.5f * fontMeasure.y }, TEXT_FONT_SIZE, FONT_SPACING, GRAY);
}

// I let these functions here but decided to stop working on the game.
// These functions were intended for resizing game objects when resizing the window.
static void ScaleUpToWindow(void)
{
	TEXT_FONT_SIZE *= SCALE_X;
	TEXT_FONT_SIZE2 *= SCALE_X;
}

static void ScaleDownToWindow(void)
{
	TEXT_FONT_SIZE /= SCALE_X;
	TEXT_FONT_SIZE2 /= SCALE_X;
}

static void CheckWindowSize(void)
{
	if (IsWindowResized() && !IsWindowFullscreen())
	{
		if (GetScreenWidth() >= OLD_WINDOW_WIDTH && GetScreenHeight >= OLD_WINDOW_HEIGHT)
		{
			OLD_WINDOW_WIDTH = WINDOW_WIDTH;
			OLD_WINDOW_HEIGHT = WINDOW_HEIGHT;
			WINDOW_WIDTH = GetScreenWidth();
			WINDOW_HEIGHT = GetScreenHeight();
			SCALE_X = WINDOW_WIDTH / OLD_WINDOW_WIDTH;
			SCALE_Y = WINDOW_HEIGHT / OLD_WINDOW_HEIGHT;
			SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
			ScaleUpToWindow();
		}
		else
		{
			OLD_WINDOW_WIDTH = WINDOW_WIDTH;
			OLD_WINDOW_HEIGHT = WINDOW_HEIGHT;
			WINDOW_WIDTH = GetScreenWidth();
			WINDOW_HEIGHT = GetScreenHeight();
			SCALE_X = OLD_WINDOW_WIDTH / WINDOW_WIDTH;
			SCALE_Y = OLD_WINDOW_HEIGHT / WINDOW_HEIGHT;
			SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
			ScaleDownToWindow();
		}
	}
}
