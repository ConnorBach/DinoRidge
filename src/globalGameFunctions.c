#include <raylib.h>

#include "dino.h"
#include "globalGameFunctions.h"
#include "player.h"

Texture2D playerTexture;
Texture2D raptorTexture;

/* Init 
 * Called to setup game
 * */
GameState *InitGameState() {
    //load textures 
    playerTexture = LoadTexture("../assets/dino1.png");
    raptorTexture = LoadTexture("../assets/dino1.png");

    // setup game state
    GameState *state = malloc(sizeof(GameState));

    Player *p = playerCreate(20, 350, 100);
    state->player = p;

    for(int i = 0; i < 5; i++) {
        //dinoCreate(GetRandomValue(0, 800), GetRandomValue(0, 450), Raptor)
    }

    return state;
}

/* Update Game State */
void Update(GameState *state) {
}

/* Draw Game state */
void Draw(GameState *state) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    Player *player = state->player;

    DrawTexture(playerTexture, player->x, player->y, RAYWHITE);

    EndDrawing();
}
