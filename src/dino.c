#include <stdlib.h>
#include "dino.h"

Dino *dinoCreate(size_t x, size_t y, DinoType type) {
    Dino *dino = malloc(sizeof(Dino));
    dino->x = x;
    dino->y = y;
    dino->type = type;
    return dino;
}
