#include "player.h"

Player *playerCreate(int x, int y, int hp, int max_hp) {
    Player *p = malloc(sizeof(Player)); 
    p->x =  x;
    p->y =  y;
    p->hp = hp;
    return p;
}

void playerMove(Player *p, size_t x, size_t y) {
    p->x += x;
    p->y += y;
}
