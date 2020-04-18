#ifndef _PLAYERH_
#define _PLAYERH_

#include <raylib.h>
#include <stdlib.h>

typedef struct Player {
    size_t x;
    size_t y;
    size_t hp;
} Player;

Player *playerCreate(int x, int y, int hp);
void playerMove(Player *p, size_t x, size_t y);

#endif
