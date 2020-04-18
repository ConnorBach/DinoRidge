#ifndef _PLAYERH_
#define _PLAYERH_

#include <raylib.h>
#include <stdlib.h>

typedef enum PlayerType {
    Cowboy,
    Ninja, 
    Grace,
    Michael
} PlayerType;

typedef struct Player {
    int x;
    int y;
    int hp;
    int max_hp;
    float percent_hp;
    PlayerType type;
} Player;

Player *playerCreate(int x, int y, int hp, int max_hp);
void playerMove(Player *p, size_t x, size_t y);
void playerUpdateHP(Player *p, int change);
void playerUpdatePercentHP(Player *p);
Rectangle *playerGetRectangle(Player *p);

#endif
