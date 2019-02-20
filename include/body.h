#ifndef SPACESHOOTER_PLAYER_H
#define SPACESHOOTER_PLAYER_H

#include <SDL2/SDL.h>

struct Body {
    int velocity;
    int size;
    Uint32 color;
    SDL_Surface *surface;
    SDL_Rect position;
    SDL_Rect normalVelocity;
};
typedef struct Body Body;


Body *createBody(int size, int x, int y, int velocity, Uint32 color);
void updatePhysicsBody(Body *body);
void drawBody(Body *body);
void calculatePosition(Body *body);
void limitPosition(Body *body);
void moveToward(Body *body, int normalX, int normalY);
void moveUp(Body *body);
void moveDown(Body *body);
void moveLeft(Body *body);
void moveRight(Body *body);
void destroyBody(Body *body);

#endif