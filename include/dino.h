#ifndef _DINOH_
#define _DINOH_

#include <stdlib.h>

typedef enum DinoType {
    GreenRaptor,
    BlueRaptor,
    OrangeBront,
    PurpleRex
} DinoType;

typedef struct Dino {
    size_t x;
    size_t y;
    enum DinoType type;
} Dino;

Dino *dinoCreate(size_t x, size_t y, DinoType type);

#endif
