#include "game.h"

Game initGame() {

    Game game;

    SDL_Init(SDL_INIT_VIDEO);

    game.window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    game.screen = SDL_GetWindowSurface(game.window);

    game.keyboardState = SDL_GetKeyboardState(NULL);

    game.quit = false;

    return game;
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