#include <math.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"

Game initGame() {

    Game game;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();

    game.window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // todo: à supprimer
    game.screen = SDL_GetWindowSurface(game.window);

    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);

    game.keyboardState = SDL_GetKeyboardState(NULL);

    game.quit = false;

    return game;
}

int minInt(int x, int y) {
    return x < y ? x : y;
}

int maxInt(int x, int y) {
    return x > y ? x : y;
}

int clamp(int lower, int x, int upper) {
    return minInt(upper, maxInt(x, lower));
}

void normalizeVector(Vector *vector) {
    double magnitude = sqrt(pow(vector->x, 2) + pow(vector->y, 2));

    if(magnitude != 0) {
        vector->x /= magnitude;
        vector->y /= magnitude;
    }
}

int ranInt(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

int setRenderColor(SDL_Renderer *renderer, Uint32 color) {

    Uint8 r, g, b, a;

    r = color / (256 * 256);
    g = color / 256 % 256;
    b = color % 256;
    a = 0xFF;

    return SDL_SetRenderDrawColor(renderer, r, g, b, a);
}