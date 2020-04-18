#include <raylib.h>

#include "globalGameFunctions.h"
#include "player.h"

int screenWidth = 1280;
int screenHeight = 800;

int main() {
	// Initialization

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    // Window configuration flags
	InitWindow(screenWidth, screenHeight, "Dino Ridge");

    //screenWidth = GetMonitorWidth(0);
    //screenHeight = GetMonitorHeight(0);

    printf("####### %d %d #########\n", GetScreenWidth(), GetScreenHeight());

    InitAudioDevice();

	SetTargetFPS(60);               

    // Create initial game state
    GameState *state = InitGameState();

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
        Update(state);

		// Draw
        Draw(state);
	}
    CleanUp(state);

	// De-Initialization
	CloseWindow();

	return 0;
}
