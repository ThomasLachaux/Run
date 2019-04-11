#ifndef SPACESHOOTER_GAME_H
#define SPACESHOOTER_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "world.h"

// General
#define FPS 60
#define DELTA_TIME 1000 / FPS

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

// Game design
#define VELOCITY_COEFF 12
#define SPAWN_TIME 2000
#define SPAWN_MIN 500
#define WAVE_LENGTH 10
#define WAVE_TIME 30000

// Styles
#define BIG 20
#define MEDIUM 13
#define SMALL 8

//#define GREEN 0x11CE70
#define BACKGROUND_COLOR 0xFFFFFF
#define BACKGROUND_SECONDARY_COLOR 0xDDDDDD
#define PLAYER_COLOR 0x222222
#define BALL_COLOR 0x222222
#define ENEMY_COLOR 0xCC0000

// Contrôles
#define LEFT_AZERTY SDLK_q
#define LEFT_QWERTY SDLK_a
#define RIGHT SDLK_d
#define TOP_AZERTY SDLK_z
#define TOP_QWERTY SDLK_w
#define BOTTOM SDLK_s

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    // todo: à supprimer
    SDL_Surface *screen;
    SDL_Event event;
    World *world;
    TTF_Font *font;
    const Uint8 *keyboardState;
    bool quit;
    int score;
    bool isPlaying;
};
typedef struct Game Game;

Game initGame();
void destroyGame(Game *game);
int minInt(int x, int y);
int maxInt(int x, int y);
int clamp(int lower, int x, int upper);
void normalizeVector(Vector *vector);
int ranInt(int min, int max);
int setRenderColor(SDL_Renderer *renderer, Uint32 color);
void increaseAndDrawScore(Game *game);
void displayWaveTime(Game *game);
void displayRules(Game *game);
#endif
