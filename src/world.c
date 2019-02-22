#include <stdlib.h>
#include <stdio.h>
#include <game.h>

#include "world.h"

World *createWorld() {
    World *world = malloc(sizeof(World));
    world->first = NULL;

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

void updateWorldPhysics(World *world) {
    Element *current = world->first;

    while (current != NULL) {
        updateBodyPhysics(current->body);

        if(current->body->layer == Player)
            limitPosition(current->body);

        else if(current->body->layer == Ball && isOffScreen(current->body))
            destroyBodyFromWorld(world, current->body);

        current = current->next;
    }

    registerCollision(world, Enemy, Ball, onEnemyBallCollision);
    registerCollision(world, Player, Enemy, onPlayerEnemyCollision);
}

void drawWorld(SDL_Surface *screen, World *world) {
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
    free(to_delete);
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