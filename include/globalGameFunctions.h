#ifndef _GLOBALGAMEFUNCTIONSH_
#define _GLOBALGAMEFUNCTIONSH_

#include <raylib.h>
#include "player.h"
#include "dino.h"

typedef struct GameState {
    Player *player;
    Dino **dinos;
} GameState;


GameState *InitGameState();
void Update(GameState *state);
void Draw(GameState *state);

#endif