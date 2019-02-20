#include <stdlib.h>

#include "world.h"


World *createWorld() {
    World *world = malloc(sizeof(World));
    world->first = NULL;

    return world;
}

void addBodyToWorld(World *world, Body *body) {

    Element *element = malloc(sizeof(Element));
    element->body = body;
    element->next = NULL;

    if(world->first == NULL)
        world->first = element;

    else {
        Element *current = world->first;

        while (current->next != NULL)
            current = current->next;

        current->next = element;
    }
}

/**
 * Parcours chaque body.
 * Prends en paramètre le world et une fonction ayant pour prototype void callback(Body *body)
 */
void forEachBody(World *world, void (*callback)(Body *body)) {
    Element *current = world->first;

    while (current != NULL) {
        (*callback)(current->body);
        current = current->next;
    }
}

void updateWorldPhysics(World *world) {
    forEachBody(world, updateBodyPhysics);
}

void drawWorld(World *world) {
    forEachBody(world, drawBody);
}

void destroyWorld(World *world) {
    forEachBody(world, destroyBody);
}