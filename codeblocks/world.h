#ifndef WORLD_H
#define WORLD_H

#include "game.h"
#include "body.h"

/**
 * Structure de liste chainée contenant des coprs
 */
struct Element {
    Body *body;
    struct Element *previous;
    struct Element *next;
};
typedef struct Element Element;

/**
 * Structure du monde
 */
struct World {
    Element *first;
    Body *player;
    int window;
    bool hardMode;
    int timers[10];
    int score;
    int startTime;
    int determination;
};
typedef struct World World;

World *createWorld();
void addBodyToWorld(World *world, Body *body);
void updateWorldPhysics(World *world);
void drawWorld(SDL_Renderer *screen, World *world);
void destroyWorld(World *world);
void registerCollision(World *world, Layer layerA, Layer layerB, void (*callback)(World *, Body *, Body *));
Uint32 createEnemy(Uint32 interval, void *world);
Uint32 createItem(Uint32 interval, void *world);
Uint32 spawnWave(Uint32 interval, void *world);
void shoot(World *world, float velocityX, float velocityY);
void destroyBodyFromWorld(World *world, Body *body);
void createMenu(World *world);
void startGame(World *world, Body *player, Body *button);

#endif