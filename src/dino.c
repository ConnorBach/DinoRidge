#include <stdlib.h>
#include "dino.h"
#include "player.h"

Dino *dinoCreate(size_t x, size_t y, DinoType type) {
    Dino *dino = malloc(sizeof(Dino));
    dino->x = x;
    dino->y = y;
    dino->type = type;
    return dino;
}

/* Moves dino towards player based on type */
void dinoChase(Dino *dino, Player *player) {
    switch(dino->type) {
        case GreenRaptor:
            greenRaptorChase(dino, player);
            break;
        case BlueRaptor:
            blueRaptorChase(dino, player);
            break;
        case OrangeBront:
            orangeBrontChase(dino, player);
            break;
        case PurpleRex:
            purpleRexChase(dino, player);
            break;
    }
}

void greenRaptorChase(Dino *dino, Player *player) {
}

void blueRaptorChase(Dino *dino, Player *player) {
}

void orangeBrontChase(Dino *dino, Player *player) {
}

/* TRex Chases towards the player */
void purpleRexChase(Dino *dino, Player *player) {
    int dirX = 0, dirY = 0;

    printf("X - X: %d", player->x - dino->x);
    if(player->x > dino->x) {
        dirX = 1;
    } else {
        dirX = -1;
    }

    if(player->y > dino->y) {
        dirY = 1;
    } else {
        dirY = -1;
    }

    /*
    printf("Player X, Y: %d, %d\n", player->x, player->y);
    printf("Dino X, Y: %d, %d\n", dino->x, dino->y);
    printf("Dir X, Y: %d, %d\n", dirX, dirY);
    */

    dino->x += dirX;
    dino->y += dirY;
}

