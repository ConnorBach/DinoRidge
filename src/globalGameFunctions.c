#include <raylib.h>
#include <stdio.h>

#include "dino.h"
#include "globalGameFunctions.h"
#include "player.h"

extern int screenWidth;
extern int screenHeight;

int n_dinos = 5;
int pause = 0;
int gameOverScore = 0;

Texture2D playerTexture;
Texture2D greenRaptorTexture;
Texture2D blueRaptorTexture;
Texture2D orangeBrontTexture;
Texture2D purpleRexTexture;

Music chaseMusic;

Camera2D camera = {0};

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

    // load and start music
    chaseMusic = LoadMusicStream("../assets/ChaseMusic.ogg");
    PlayMusicStream(chaseMusic);

	// setup game state
	GameState *state = malloc(sizeof(GameState));
    state->gameOver = 0;

    //printf(" ====== %d %d ======\n", screenWidth, screenHeight);
	Player *p = playerCreate(screenWidth / 2, screenHeight/ 2, 100, 100);
	state->player = p;
    playerUpdatePercentHP(p);

    // always need one t rex to make it interesting
	Dino **dinos = malloc(sizeof(Dino) * n_dinos);
    Vector2 dinoSpawn = dinoGetSpawn(p->x, p->y);
    dinos[0] = dinoCreate(dinoSpawn.x, dinoSpawn.y, PurpleRex);
    dinos[0]->bounds = dinoGetRectangles(dinos[0]);

	for(int i = 1; i < n_dinos; i++) {
        Vector2 dinoSpawn = dinoGetSpawn(p->x, p->y);
        dinos[i] = dinoCreate(dinoSpawn.x, dinoSpawn.y, GetRandomValue(0, 2));
        dinos[i]->bounds = dinoGetRectangles(dinos[i]);
	}
	state->dinos = dinos;

    state->score = 0;

    //setup camera
    camera.target = (Vector2){ p->x, p->y };
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

	return state;
}

/* Update Game State */
void Update(GameState *state) {
    /* Reset Game */
    if(IsKeyDown(KEY_SPACE) && state->gameOver == 1) {
        Reset(state);
    }

    /* Update screen width/height if resized*/
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    /* Update music */
    UpdateMusicStream(chaseMusic);

    // Pause/Resume music playing
    if (IsKeyPressed(KEY_P))
    {
        pause = !pause;

        if (pause) PauseMusicStream(chaseMusic);
        else ResumeMusicStream(chaseMusic);
    }

	/* read user input, update player position */
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) playerMove(state->player, 2, 0);
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) playerMove(state->player, -2, 0);
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) playerMove(state->player, 0, -2);
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) playerMove(state->player, 0, 2);


    state->player->bound = playerGetRectangle(state->player);

    printf("after state player bound\n");

    /* have camera follow player */

    /* update dino position */
    Dino **dinos = state->dinos;

    printf("state dino\n");

    for(int i = 0; i < n_dinos; i++) {
        dinoChase(dinos[i], state->player); 
        printf("dino chase\n");
        dinos[i]->bounds = dinoGetRectangles(dinos[i]);
        printf("dino bounds\n");
    }

    printf("dino position, bounds\n");


    /* check for collisions, lower player hp */
    for(int i = 0; i < n_dinos; i++) {
        Rectangle *playerRect = state->player->bound;
        Rectangle **dinoRects = dinos[i]->bounds;
        for(int j = 0; j < 3; j++) {
            Rectangle *dinoRect = dinoRects[j];
            if(CheckCollisionRecs(*playerRect, *dinoRect)) {
                int dmg = 0;
                switch(dinos[i]->type) {
                    case GreenRaptor:
                        dmg -= 5;
                        break;
                    case BlueRaptor:
                        dmg -= 10;
                        break;
                    case OrangeBront:
                        dmg -= 40;
                        break;
                    case PurpleRex:
                        dmg -= 60;
                        break;
                }
                playerUpdateHP(state->player, dmg);
                playerUpdatePercentHP(state->player);

                if(state->player->hp == 0) {
                    state->gameOver = 1;
                    gameOverScore = gameOverScore == 0 ? state->score : gameOverScore;
                }
            }
        }
    }


    /* update score */
    state->score++;
}

/* Draw Game state */
void Draw(GameState *state) {
    /* Render */
	BeginDrawing();

	ClearBackground(GREEN);

    if(state->gameOver) {
        DrawText("Game Over: Press Space to restart", .15 * screenWidth, .5 * screenHeight, 40, BLACK);
    } else {
        //BeginMode2D(camera);

        Player *player = state->player;
        DrawTexture(playerTexture, player->x, player->y, RAYWHITE);
        Rectangle *bound = state->player->bound;
        //DrawRectangle(bound->x, bound->y, bound->width, bound->height, RED);

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

            /*Rectangle **recs = dinos[i]->bounds;
            for(int i = 0; i < 3; i++) {
                Rectangle *r = recs[i];
                //DrawRectangle(r->x, r->y, r->width, r->height,  BLUE);
            }*/
        }

        //EndMode2D();
    }
    
    /* Draw UI */

    /* Draw HP bar */
    float hp_bar_width = state->player->percent_hp * (.1 * screenWidth - 4);

    printf("percent_hp: %f, hp_bar_width: %f\n", state->player->percent_hp, hp_bar_width);

    DrawRectangle(.9 * screenWidth, .05 * screenHeight, hp_bar_width, .05 * screenHeight - 4, RED);

    /* Draw HP Bar outline */
    DrawRectangleLines(.9 * screenWidth, .05 * screenHeight, .1 * screenWidth, .05 * screenHeight, BLACK);

    /* Draw Score */
    int curScore = state->gameOver ? gameOverScore : state->score;
    printf("curScore: %d\n", curScore);
    int len = snprintf(NULL, 0, "Score: %d", curScore);
    char *score = malloc(sizeof(char)*len+1);
    snprintf(score, len+1, "Score: %d", curScore);
    DrawText(score, .9 * screenWidth, .1 * screenHeight, 20, BLACK);
    free(score);

	EndDrawing();
}

/* Cleans up game state and globals in this file */
void CleanUp(GameState *state) {
    /* clean up music */
    //UnloadMusicStream(chaseMusic);
    //CloseAudioDevice();

    /* clean up game state */
}

/* restarts game */
void Reset(GameState *state) {
	// setup game state
    state->gameOver = 0;
    gameOverScore = 0;

    // reset player
    state->player->x = screenWidth / 2;
    state->player->y = screenHeight / 2;
    playerUpdateHP(state->player, 100);
    playerUpdatePercentHP(state->player);

    // reset dinos
	for(int i = 0; i < n_dinos; i++) {
        dinoFree(state->dinos[i]);
    }
    free(state->dinos);

    // new random dinos
	Dino **dinos = malloc(sizeof(Dino) * n_dinos);
    Vector2 dinoSpawn = dinoGetSpawn(state->player->x, state->player->y);
    dinos[0] = dinoCreate(dinoSpawn.x, dinoSpawn.y, PurpleRex);
    dinos[0]->bounds = dinoGetRectangles(dinos[0]);

	for(int i = 1; i < n_dinos; i++) {
        Vector2 dinoSpawn = dinoGetSpawn(state->player->x, state->player->y);
        dinos[i] = dinoCreate(dinoSpawn.x, dinoSpawn.y, GetRandomValue(0, 2));
        dinos[i]->bounds = dinoGetRectangles(dinos[i]);
	}

	state->dinos = dinos;

    state->score = 0;
}
