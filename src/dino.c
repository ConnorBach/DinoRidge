#include <stdlib.h>
#include "dino.h"
#include "player.h"

Dino *dinoCreate(size_t x, size_t y, DinoType type) {
    Dino *dino = malloc(sizeof(Dino));
    dino->x = x;
    dino->y = y;
    dino->home_x = x;
    dino->home_y = y;
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
    int dirX = GetRandomValue(-1, 1), dirY = GetRandomValue(-1, 1);

    dino->x += dirX;
    dino->y += dirY;
}

void blueRaptorChase(Dino *dino, Player *player) {
}

/* chases towards player if nearby */
void orangeBrontChase(Dino *dino, Player *player) {
    Vector2 playerPos = { player->x, player->y };
    Vector2 homeLocation = { dino->home_x, dino->home_y };
    if(CheckCollisionPointCircle(playerPos, homeLocation, 300)) {
        dinoMove(dino, playerPos);
    } else {
        dinoMove(dino, homeLocation);
    }
}

/* TRex Chases towards the player */
void purpleRexChase(Dino *dino, Player *player) {
    Vector2 playerPos = { player->x, player->y };
    dinoMove(dino, playerPos);
}

void dinoMove(Dino *dino, Vector2 point) {
    int dirX = 0, dirY = 0;

    //printf("X - X: %d", player->x - dino->x);
    if(point.x > dino->x) {
        dirX = 1;
    } else {
        dirX = -1;
    }

    if(point.y > dino->y) {
        dirY = 1;
    } else {
        dirY = -1;
    }

    dino->x += dirX;
    dino->y += dirY;
}
