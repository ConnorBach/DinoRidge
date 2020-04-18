#ifndef _PLAYERH_
#define _PLAYERH_

#include <raylib.h>
#include <stdlib.h>

typedef struct Player {
    int x;
    int y;
    int hp;
    int max_hp;
    float percent_hp;
} Player;

Player *playerCreate(int x, int y, int hp, int max_hp);
void playerMove(Player *p, size_t x, size_t y);
void playerUpdateHP(Player *p, int change);
void playerUpdatePercentHP(Player *p);

#endif
