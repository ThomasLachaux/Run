#include "body.h"

Body createBody(int size, int x, int y) {

    Body body;

    body.surface = SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0);
    body.position.x = x;
    body.position.y = y;

    return body;
}

void freeBody(Body body) {
    SDL_FreeSurface(body.surface);
}