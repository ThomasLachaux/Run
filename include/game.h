#ifndef SPACESHOOTER_GAME_H
#define SPACESHOOTER_GAME_H

#include <SDL2/SDL.h>

#define FPS 60

static const int DELTA_TIME = 1000 / FPS;

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

static const int VELOCITY_NORMALIZE = 12;

static const Uint32 backgroundColor = 0x11CE70;
static const Uint32 playerColor = 0x000000;
static const Uint32 ballColor = 0xFFFFFF;

SDL_Window *window;
SDL_Surface *screen;
SDL_Event e;

void initGame();
int min(int x, int y);
int max(int x, int y);
int clamp(int lower, int x, int upper);
int center(int a, int b);

#endif
