#include <raylib.h>

#include "dino.h"
#include "globalGameFunctions.h"
#include "player.h"

extern int screenWidth;
extern int screenHeight;

int n_dinos = 5;

Texture2D playerTexture;
Texture2D greenRaptorTexture;
Texture2D blueRaptorTexture;
Texture2D orangeBrontTexture;
Texture2D purpleRexTexture;

/* Init 
 * Called to setup game
 * */
GameState *InitGameState() {
	//load textures 
    Image playerImage = LoadImage("../assets/PlayerCharacter.png");
    ImageResize(&playerImage, playerImage.width*.4, playerImage.height*.4);
	playerTexture = LoadTextureFromImage(playerImage);
	greenRaptorTexture = LoadTexture("../assets/dino1.png");
	blueRaptorTexture = LoadTexture("../assets/dino2.png");
	orangeBrontTexture= LoadTexture("../assets/dino3.png");
	purpleRexTexture = LoadTexture("../assets/dino4.png");

	// setup game state
	GameState *state = malloc(sizeof(GameState));

	Player *p = playerCreate(.1 * screenWidth, 200, 100);
	state->player = p;

	Dino **dinos = malloc(sizeof(Dino) * n_dinos);
	for(int i = 0; i < n_dinos; i++) {
		dinos[i] = dinoCreate(GetRandomValue(0, 800), GetRandomValue(0, 450), GetRandomValue(0, 3));
	}
	state->dinos = dinos;

	return state;
}

/* Update Game State */
void Update(GameState *state) {
    /* Update screen width/height if resized*/
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();


	/* read user input, update player position */
	if (IsKeyDown(KEY_RIGHT)) state->player->x += 2.0f;
	if (IsKeyDown(KEY_LEFT)) state->player->x -= 2.0f;
	if (IsKeyDown(KEY_UP)) state->player->y -= 2.0f;
	if (IsKeyDown(KEY_DOWN)) state->player->y += 2.0f;

    /* update dino position */


    /* check for collisions, lower player hp */
}

/* Draw Game state */
void Draw(GameState *state) {
	BeginDrawing();

	ClearBackground(GREEN);

	Player *player = state->player;
	DrawTexture(playerTexture, player->x, player->y, RAYWHITE);

    Dino **dinos = state->dinos;
    for(int i = 0; i < n_dinos; i++) {
        Texture2D dinoTexture;
        switch(dinos[i]->type) {
            case GreenRaptor:
                dinoTexture = greenRaptorTexture;
                break;
            case BlueRaptor:
                dinoTexture = blueRaptorTexture;
                break;
            case OrangeBront:
                dinoTexture = orangeBrontTexture;
                break;
            case PurpleRex:
                dinoTexture = purpleRexTexture;
                break;
        }

        DrawTexture(dinoTexture, dinos[i]->x, dinos[i]->y, RAYWHITE);
    }

	EndDrawing();
}
