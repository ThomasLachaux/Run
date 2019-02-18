#ifndef SPACESHOOTER_PLAYER_H
#define SPACESHOOTER_PLAYER_H

#include <SDL2/SDL.h>

struct Body {
    SDL_Surface *surface;
    SDL_Rect position;
    SDL_Rect velocity;
};
typedef struct Body Body;

Body createBody(int size, int x, int y);
void freeBody(Body body);

#endif