#include <math.h>
#include <stdio.h>


#include "game.h"

Game initGame() {

    Game game;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    TTF_Init();

    game.font = TTF_OpenFont("../src/LemonMilk.ttf", 20);

    game.window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // todo: à supprimer
    game.screen = SDL_GetWindowSurface(game.window);

    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);

    game.keyboardState = SDL_GetKeyboardState(NULL);

    game.quit = false;

    game.score = 0;

    return game;
}

void destroyGame(Game *game) {
    destroyWorld(game->world);
    SDL_DestroyWindow(game->window);

    TTF_CloseFont(game->font);

    TTF_Quit();
    SDL_Quit();
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

void increaseAndDrawScore(Game *game) {
    char displayScore[6];

    sprintf(displayScore, "%06d", game->score);

    SDL_Color color = {255, 255, 255};
    // Ligne en dessous pose probleme
    SDL_Surface *text = TTF_RenderText_Blended(game->font, displayScore, color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, text);

    SDL_Rect pos;
    pos.x = SCREEN_WIDTH - 100;
    pos.y = 10;
    pos.w = text->w;
    pos.h = text->h;

    SDL_RenderCopy(game->renderer, texture, NULL, &pos);

    game->score += DELTA_TIME / 10;
}

void displayWaveTime(Game *game) {
    int time = WAVE_TIME - SDL_GetTicks() % WAVE_TIME;
    time /= 1000;
    time += 1;
    char timeDisplay[16];
    sprintf(timeDisplay, "Vague: %02d s", time);

    SDL_Color color = {255, 255, 255};
    SDL_Surface *text = TTF_RenderText_Blended(game->font, timeDisplay, color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, text);

    SDL_Rect pos;
    pos.x = 10;
    pos.y = 10;
    pos.w = text->w;
    pos.h = text->h;

    SDL_RenderCopy(game->renderer, texture, NULL, &pos);
}