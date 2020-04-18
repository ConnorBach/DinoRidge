#include <raylib.h>

#include "globalGameFunctions.h"
#include "player.h"

int screenWidth;
int screenHeight;

int main() {
	// Initialization
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    // Window configuration flags
	InitWindow(screenWidth, screenHeight, "Dino Ridge");

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
