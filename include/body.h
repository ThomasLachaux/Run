#ifndef SPACESHOOTER_PLAYER_H
#define SPACESHOOTER_PLAYER_H

#include <SDL2/SDL.h>

struct Body {
    int velocity;
    int size;
    SDL_Surface *surface;
    SDL_Rect position;
    SDL_Rect normalVelocity;
};
typedef struct Body Body;

Body *createBody(int size, int x, int y, int velocity);
void updatePhysics(Body *body);
void calculatePosition(Body *body);
void limitPosition(Body *body);
void moveToward(Body *body, int normalX, int normalY);
void freeBody(Body *body);

#endif