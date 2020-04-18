#include "player.h"

Player *playerCreate(int x, int y, int hp, int max_hp) {
    Player *p = malloc(sizeof(Player)); 
    p->x =  x;
    p->y =  y;
    p->hp = hp;
    p->max_hp = max_hp;
    return p;
}

void playerMove(Player *p, size_t x, size_t y) {
    p->x += x;
    p->y += y;
}

void playerUpdateHP(Player *p, int change) {
    int new_hp = p->hp + change;
    if(new_hp >= 0 && new_hp <= p->max_hp) {
        p->hp = new_hp;
    } else if(new_hp > p->max_hp) {
        p->hp = p->max_hp;
    } else {
        p->hp = 0;
    }
}

void playerUpdatePercentHP(Player *p) {
    p->percent_hp = (float)p->hp / p->max_hp;
    printf("p->percent_hp: %f\n", p->percent_hp);
}

/* returns a bounding rectangle */
Rectangle *playerGetRectangle(Player *p) {
    Rectangle *r = malloc(sizeof(Rectangle));
    r->x = p->x;
    r->y = p->y;
    switch(p->type) {
        case Cowboy:
            r->width = 50;
            r->height = 50;
            break;
        case Ninja:
            r->width = 40;
            r->height = 40;
            break;
        case Grace:
            r->width = 40;
            r->height = 40;
            break;
        case Michael:
            r->width = 30;
            r->height = 30;
            break;
    }

    return r;
}
