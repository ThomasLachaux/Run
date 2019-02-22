#ifndef SPACESHOOTER_GAME_H
#define SPACESHOOTER_GAME_H

#include <SDL2/SDL.h>
#include "world.h"

#define FPS 60

static const int DELTA_TIME = 1000 / FPS;

static const int SCREEN_WIDTH = 720;
static const int SCREEN_HEIGHT = 480;

static const int VELOCITY_NORMALIZE = 12;

// todo: Passer en define

static const int playerSize = 20;
static const int ballSize = 5;

static const Uint32 backgroundColor = 0x11CE70;
static const Uint32 playerColor = 0x000000;
static const Uint32 ballColor = 0xFFFFFF;

//SDL_Window *window;
//SDL_Surface *screen;
//SDL_Event e;

struct Game {
    SDL_Window *window;
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
int center(int a, int b);
void normalizeVector(Vector *vector);
#endif
