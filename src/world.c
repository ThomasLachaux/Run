#include <stdlib.h>
#include <stdio.h>
#include <game.h>
#include <math.h>

#include "world.h"

World *createWorld() {
    World *world = malloc(sizeof(World));
    world->first = NULL;
    world->isPlaying = false;

    return world;
}

void addBodyToWorld(World *world, Body *body) {

    Element *element = malloc(sizeof(Element));
    element->body = body;
    element->previous = NULL;
    element->next = NULL;

    if (world->first == NULL)
        world->first = element;

    else {
        Element *current = world->first;

        while (current->next != NULL)
            current = current->next;

        current->next = element;
        element->previous = current;
    }
}

/**
 * Parcours chaque body.
 * Prends en paramètre le world et une fonction ayant pour prototype void callback(Body *body)
 */
void forEachBody(World *world, void (*callback)(Body *)) {
    Element *current = world->first;

    while (current != NULL) {
        (*callback)(current->body);
        current = current->next;
    }
}

void onEnemyBallCollision(World *world, Body *enemy, Body *ball) {
    destroyBodyFromWorld(world, enemy);
    destroyBodyFromWorld(world, ball);
}

void onPlayerEnemyCollision(World *world, Body *player, Body *enemy) {
    destroyBodyFromWorld(world, player);
}

void onPlayerItemCollision(World *world, Body *player, Body *item) {
    int x,y;

    int steps = 10;

    for(x = -steps; x <= steps; x++) {
        for(y = -steps; y <= steps; y ++) {
            if(x != 0 || y != 0)
                shoot(world, (float) x / steps, (float) y / steps);
        }
    }

    destroyBodyFromWorld(world, item);
}

void onPlayerStartCollision(World *world, Body *player, Body *start) {
    world->isPlaying = true;

    spawnWave(0, world);

    SDL_AddTimer(SPAWN_TIME, createEnemy, world);
    SDL_AddTimer(WAVE_TIME, spawnWave, world);
    SDL_AddTimer(5000, createItem, world);

    onPlayerItemCollision(world, player, start);
}

void updateWorldPhysics(World *world) {
    Element *current = world->first;

    while (current != NULL) {
        updateBodyPhysics(current->body);

        if(current->body->layer == Player)
            limitPosition(current->body);

        else if(current->body->layer == Ball && isOffScreen(current->body))
            destroyBodyFromWorld(world, current->body);

        else if(current->body->layer == Enemy)
            follow(current->body, world->player);

        current = current->next;
    }

    registerCollision(world, Enemy, Ball, onEnemyBallCollision);
    //registerCollision(world, Player, Enemy, onPlayerEnemyCollision);
    registerCollision(world, Player, Item, onPlayerItemCollision);
    registerCollision(world, Player, Start, onPlayerStartCollision);
}

void drawWorld(SDL_Renderer *screen, World *world) {
    Element *current = world->first;

    while (current != NULL) {
        drawBody(screen, current->body);
        current = current->next;
    }
}

void destroyWorld(World *world) {
    Element *current = world->first;
    Element *toDestroy;

    while (current != NULL) {
        toDestroy = current;
        current = current->next;

        destroyBody(toDestroy->body);
        free(toDestroy);
    }

    free(world);
}

void destroyBodyFromWorld(World *world, Body *body) {
    Element *to_delete = world->first;
    Element *previous, *next;

    while (to_delete != NULL && to_delete->body != body) {
        to_delete = to_delete->next;
    }

    if(to_delete != NULL) {

        previous = to_delete->previous;
        next = to_delete->next;

        // If first element
        if (previous == NULL) {

            world->first = next;

            if (next != NULL)
                next->previous = NULL;
        }

            // If not first element
        else {
            previous->next = next;

            if (next != NULL)
                next->previous = previous;
        }

        destroyBody(to_delete->body);
        // todo: trouver une solution à ça
        //free(to_delete);
    }
}

Uint32 createItem(Uint32 interval, void *world) {
    int x = ranInt(MEDIUM, SCREEN_WIDTH - MEDIUM);
    int y = ranInt(MEDIUM, SCREEN_HEIGHT - MEDIUM);

    Body *item = createBody(x, y, MEDIUM, MEDIUM, 0, 0x0000CC, Item);
    addBodyToWorld(world, item);

    return interval;
}

Uint32 createEnemy(Uint32 interval, void *world) {

    int x = ranInt(0, 1) ? 0: SCREEN_WIDTH;
    int y = ranInt(0, SCREEN_HEIGHT);

    Body *enemy = createBody(x, y, MEDIUM, MEDIUM, 3, ENEMY_COLOR, Enemy);
    addBodyToWorld(world, enemy);

    return (Uint32) maxInt(SPAWN_MIN, interval - DELTA_TIME);
}

Uint32 spawnWave(Uint32 interval, void *world) {
    int i;

    for(i = 0; i < WAVE_LENGTH; i++)
        createEnemy(0, world);

    return interval;
}

void shoot(World *world, float velocityX, float velocityY) {

    int x = world->player->transform.x + BIG / 2 - SMALL / 2;
    int y = world->player->transform.y + BIG / 2 - SMALL / 2;

    Body *ball = createBody(x, y, SMALL, SMALL, 5, BALL_COLOR, Ball);

    ball->direction.x = velocityX;
    ball->direction.y = velocityY;

    addBodyToWorld(world, ball);
}

void registerCollision(World *world, Layer layerA, Layer layerB, void (*callback)(World *, Body *, Body *)) {

    Element *elementA, *elementB, *nextElementA, *nextElementB;
    Body *bodyA, *bodyB;

    elementA = world->first;

    
    
    // Premier parcours
    while (elementA != NULL) {
        
        nextElementA = elementA->next;
        
        // Recherche dans le layerA
        if (elementA->body->layer == layerA) {

            elementB = world->first;
            
            while (elementB != NULL) {

                nextElementB = elementB->next;
                
                // Recherche dans le layerB
                if (elementB->body->layer == layerB) {

                    bodyA = elementA->body;
                    bodyB = elementB->body;

                    // Si collision, alors appel du callback
                    if (
                            bodyA->transform.x < bodyB->transform.x + bodyB->transform.w &&
                            bodyA->transform.x + bodyA->transform.w > bodyB->transform.x &&
                            bodyA->transform.y < bodyB->transform.y + bodyB->transform.h &&
                            bodyA->transform.h + bodyA->transform.y > bodyB->transform.y) {

                            (*callback)(world, bodyA, bodyB);
                    }
                }

                elementB = nextElementB;
            }
        }
        elementA = nextElementA;
    }
}