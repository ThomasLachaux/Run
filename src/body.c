#include <stdlib.h>

#include "game.h"
#include "body.h"

Body *createBody(int size, int x, int y, int velocity, Uint32 color) {

    Body *body = malloc(sizeof(Body));

    body->surface = SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0);

    body->position.x = x;
    body->position.y = y;
    body->size = size;

    body->normalVelocity.x = 0;
    body->normalVelocity.y = 0;

    body->velocity = velocity * DELTA_TIME / VELOCITY_NORMALIZE;
    body->color = color;

    return body;
}

void moveToward(Body *body, int normalX, int normalY) {
    body->position.x += normalX * body->velocity;
    body->position.y += normalY * body->velocity;
}

void moveUp(Body *body) {
    body->normalVelocity.y = -1;
}

void moveDown(Body *body) {
    body->normalVelocity.y = 1;
}

void moveRight(Body *body) {
    body->normalVelocity.x = 1;
}

void moveLeft(Body *body) {
    body->normalVelocity.x = -1;
}

void updatePhysicsBody(Body *body) {
    calculatePosition(body);

    limitPosition(body);
}

void drawBody(Body *body) {
    SDL_FillRect(body->surface, NULL, body->color);
    SDL_BlitSurface(body->surface, NULL, screen, &body->position);
}

void calculatePosition(Body *body) {
    body->position.x += body->normalVelocity.x * body->velocity;
    body->position.y += body->normalVelocity.y * body->velocity;
}

void limitPosition(Body *body) {
    body->position.x = clamp(0, body->position.x, SCREEN_WIDTH - body->size);
    body->position.y = clamp(0, body->position.y, SCREEN_HEIGHT - body->size);
}

void destroyBody(Body *body) {
    SDL_FreeSurface(body->surface);
    free(body);
}