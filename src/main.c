#include <raylib.h>

#include "globalGameFunctions.h"
#include "player.h"

int main() {
	// Initialization
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Dino Ridge");

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

	// De-Initialization
	CloseWindow();

	return 0;
}
