#include <stdlib.h>
#include "dino.h"
#include "player.h"

extern int screenWidth;
extern int screenHeight;

Dino *dinoCreate(size_t x, size_t y, DinoType type) {
    Dino *dino = malloc(sizeof(Dino));
    dino->x = x;
    dino->y = y;
    dino->home_x = x;
    dino->home_y = y;
    dino->type = type;

    Vector2 dst = { GetRandomValue(0, screenWidth), GetRandomValue(0, screenHeight) };
    dino->greenRaptorDest = dst;
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

/* moves around to random locations */
void greenRaptorChase(Dino *dino, Player *player) {
    if(dino->x != dino->greenRaptorDest.x || dino->y != dino->greenRaptorDest.y) {
    } else {
        Vector2 dest = { GetRandomValue(0, screenWidth), GetRandomValue(0, screenHeight) };
        dino->greenRaptorDest = dest;
    }

    dinoMove(dino, dino->greenRaptorDest);
}

/* chases player if you are in it's territory */
void blueRaptorChase(Dino *dino, Player *player) {
    Vector2 playerPos = { player->x, player->y };
    Vector2 homeLocation = { dino->home_x, dino->home_y };
    if(CheckCollisionPointCircle(playerPos, homeLocation, 500)) {
        dinoMove(dino, playerPos);
    } else {
        dinoMove(dino, homeLocation);
    }
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
