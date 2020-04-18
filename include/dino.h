#ifndef _DINOH_
#define _DINOH_

#include <stdlib.h>
#include "player.h"

typedef enum DinoType {
    GreenRaptor,
    BlueRaptor,
    OrangeBront,
    PurpleRex
} DinoType;

typedef struct Dino {
    size_t x;
    size_t y;
    size_t home_x;
    size_t home_y;
    Vector2 greenRaptorDest;
    DinoType type;
    Rectangle **bounds;
} Dino;

Dino *dinoCreate(size_t x, size_t y, DinoType type);

void dinoChase(Dino *dino, Player *player);
void greenRaptorChase(Dino *dino, Player *player);
void blueRaptorChase(Dino *dino, Player *player);
void orangeBrontChase(Dino *dino, Player *player);
void purpleRexChase(Dino *dino, Player *player);
void dinoMove(Dino *dino, Vector2 point);
Rectangle **dinoGetRectangles(Dino *d);

#endif
