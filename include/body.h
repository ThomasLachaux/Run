#ifndef SPACESHOOTER_PLAYER_H
#define SPACESHOOTER_PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "world.h"

enum Layer {
    Player, Enemy, Ball
};
typedef enum Layer Layer;

struct Body {
    float velocity;
    Uint32 color;
    SDL_Surface *surface;
    SDL_Rect transform;
    SDL_Rect normalVelocity;
    Layer layer;
};
typedef struct Body Body;


Body *createBody(int x, int y, int w, int h, float velocity, Uint32 color, Layer layer);
void updateBodyPhysics(Body *body);
void drawBody(SDL_Surface *screen, Body *body);
void calculatePosition(Body *body);
void limitPosition(Body *body);

void moveUp(Body *body);
void moveDown(Body *body);
void moveLeft(Body *body);
void moveRight(Body *body);
void destroyBody(Body *body);
bool isOffScreen(Body *body);

#endif