#include <math.h>
#include <stdio.h>

#include "game.h"

Game initGame() {

    Game game;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    game.window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    game.screen = SDL_GetWindowSurface(game.window);

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

int center(int a, int b) {
    return a / 2 - b / 2;
}

void normalizeVector(Vector *vector) {
    double magnitude = sqrt(pow(vector->x, 2) + pow(vector->y, 2));

    if(magnitude != 0) {
        vector->x /= magnitude;
        vector->y /= magnitude;
    }
}