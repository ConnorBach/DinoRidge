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

    dino->bounds = dinoGetRectangles(dino);
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
    //Vector2 playerPos = { player->x, player->y };
    Vector2 *playerPos = dinoGetAdjustedPlayerPos(player);
    Vector2 homeLocation = { dino->home_x, dino->home_y };
    if(CheckCollisionPointCircle(*playerPos, homeLocation, 500)) {
        dinoMove(dino, *playerPos);
    } else {
        dinoMove(dino, homeLocation);
    }
    free(playerPos);
}

/* chases towards player if nearby */
void orangeBrontChase(Dino *dino, Player *player) {
    //Vector2 playerPos = { player->x, player->y };
    Vector2 *playerPos = dinoGetAdjustedPlayerPos(player);
    Vector2 homeLocation = { dino->home_x, dino->home_y };
    if(CheckCollisionPointCircle(*playerPos, homeLocation, 300)) {
        dinoMove(dino, *playerPos);
    } else {
        dinoMove(dino, homeLocation);
    }
    free(playerPos);
}

/* TRex Chases towards the player */
void purpleRexChase(Dino *dino, Player *player) {
    //Vector2 playerPos = { player->x, player->y };
    Vector2 *playerPos = dinoGetAdjustedPlayerPos(player);
    dinoMove(dino, *playerPos);
    free(playerPos);
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

Rectangle **dinoGetRectangles(Dino *d) {
    Rectangle **bounds = malloc(sizeof(Rectangle*)*3);
    Rectangle *body = malloc(sizeof(Rectangle));
    Rectangle *head = malloc(sizeof(Rectangle));
    Rectangle *tail = malloc(sizeof(Rectangle));

    switch(d->type) {
        case GreenRaptor:
            head->x = d->x + 50;
            head->y = d->y + 20;
            head->width = 100;
            head->height = 60;

            body->x = d->x + 50;
            body->y = d->y + 20;
            body->width = 50;
            body->height = 120;

            tail->x = d->x + 10;
            tail->y = d->y + 80;
            tail->width = 50;
            tail->height = 50;
            break;
        case BlueRaptor:
            head->x = d->x + 50;
            head->y = d->y + 20;
            head->width = 100;
            head->height = 60;

            body->x = d->x + 50;
            body->y = d->y + 20;
            body->width = 50;
            body->height = 120;

            tail->x = d->x + 10;
            tail->y = d->y + 80;
            tail->width = 50;
            tail->height = 50;
            break;
        case OrangeBront:
            head->x = d->x + 130;
            head->y = d->y + 10;
            head->width = 110;
            head->height = 60;

            body->x = d->x + 130;
            body->y = d->y + 60;
            body->width = 50;
            body->height = 180;

            tail->x = d->x + 20;
            tail->y = d->y + 140;
            tail->width = 150;
            tail->height = 80;
            break;
        case PurpleRex:
            head->x = d->x + 130;
            head->y = d->y + 10;
            head->width = 110;
            head->height = 60;

            body->x = d->x + 100;
            body->y = d->y + 60;
            body->width = 80;
            body->height = 180;

            tail->x = d->x + 20;
            tail->y = d->y + 150;
            tail->width = 130;
            tail->height = 40;
            break;
    }

    bounds[0] = head;
    bounds[1] = body;
    bounds[2] = tail;
    return bounds;
}

void dinoFree(Dino *d) {
    for(int i = 0; i < 3; i++) {
        free(d->bounds[i]);
    }
    free(d);
}

Vector2 *dinoGetAdjustedPlayerPos(Player *p) {
    Vector2 *pos = malloc(sizeof(Vector2));
    pos->x = p->x - 100;
    pos->y = p->y - 100;
    return pos;
}
