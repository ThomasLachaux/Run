#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "body.h"

Body *createBody(int x, int y, int w, int h, float velocity, Uint32 color, Layer layer) {

    Body *body = malloc(sizeof(Body));

    body->surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

    body->transform.x = x;
    body->transform.y = y;
    body->transform.w = w;
    body->transform.h = h;

    body->direction.x = 0;
    body->direction.y = 0;

    body->velocity = velocity * DELTA_TIME / VELOCITY_COEFF;
    body->color = color;

    body->layer = layer;

    return body;
}

void moveUp(Body *body) {
    body->direction.y = -1;
}

void moveDown(Body *body) {
    body->direction.y = 1;
}

void moveRight(Body *body) {
    body->direction.x = 1;
}

void moveLeft(Body *body) {
    body->direction.x = -1;
}

void updateBodyPhysics(Body *body) {
    calculatePosition(body);
}

void drawBody(SDL_Renderer *renderer, Body *body) {
    setRenderColor(renderer, body->color);
    SDL_RenderFillRect(renderer, &body->transform);
}

void calculatePosition(Body *body) {
    normalizeVector(&body->direction);

    body->transform.x = (int) roundf(body->transform.x + body->direction.x * body->velocity);
    body->transform.y = (int) roundf(body->transform.y + body->direction.y * body->velocity);
}

void follow(Body *follower, Body *followed) {
    follower->direction.x = followed->transform.x - follower->transform.x;
    follower->direction.y = followed->transform.y - follower->transform.y;
}

void limitPosition(Body *body) {
    body->transform.x = clamp(0, body->transform.x, SCREEN_WIDTH - body->transform.w);
    body->transform.y = clamp(0, body->transform.y, SCREEN_HEIGHT - body->transform.h);
}

bool isOffScreen(Body *body) {
    return (
            body->transform.x < 0 || body->transform.x > SCREEN_WIDTH - body->transform.w ||
            body->transform.y < 0 || body->transform.y > SCREEN_HEIGHT - body->transform.h);
}

void destroyBody(Body *body) {
    SDL_FreeSurface(body->surface);
    free(body);
}