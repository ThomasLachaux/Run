#ifndef SPACESHOOTER_GAME_H
#define SPACESHOOTER_GAME_H

#include <SDL2/SDL.h>
#include "world.h"

#define FPS 60
#define DELTA_TIME 1000 / FPS

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480

#define VELOCITY_COEFF 12

#define BIG 20
#define MEDIUM 10
#define SMALL 5

#define GREEN 0x11CE70
#define BLACK 0x000000
#define WHITE 0xFFFFFF

#define LEFT SDLK_s
#define RIGHT SDLK_f
#define TOP SDLK_e
#define BOTTOM SDLK_d

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    // todo: à supprimer
    SDL_Surface *screen;
    SDL_Event event;
    World *world;
    const Uint8 *keyboardState;
    bool quit;
};
typedef struct Game Game;

Game initGame();
int minInt(int x, int y);
int maxInt(int x, int y);
int clamp(int lower, int x, int upper);
void normalizeVector(Vector *vector);
int ranInt(int min, int max);
int setRenderColor(SDL_Renderer *renderer, Uint32 color);
#endif
