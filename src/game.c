#include "game.h"

void initGame() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
}

int min(int x, int y) {
    return x < y ? x : y;
}

int max(int x, int y) {
    return x > y ? x : y;
}

int clamp(int lower, int x, int upper) {
    return min(upper, max(x, lower));
}

int center(int a, int b) {
    return a / 2 - b / 2;
}