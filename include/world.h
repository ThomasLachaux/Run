#ifndef SPACESHOOTER_WORLD_H
#define SPACESHOOTER_WORLD_H

#include "body.h"

struct Element {
    Body *body;
    struct Element *next;
};
typedef struct Element Element;

struct World {
    Element *first;
};
typedef struct World World;

World *createWorld();
void addBodyToWorld(World *world, Body *body);
void updateWorldPhysics(World *world);
void drawWorld(World *world);
void destroyWorld(World *world);


#endif