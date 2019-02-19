#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "body.h"

Body *player = NULL;
Body *ball = NULL;

void handleEvents(int *quit, const Uint8 *keyboardState);
void physicsCalculations();
void graphicsCalculations();

int main(int argc, char *argv[]) {

    initGame();
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    int quit = 0;

    player = createBody(20, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, 4);

    ball = createBody(5, player->position.x + 5, player->position.y + 5, 5);
    ball->normalVelocity.y = -1;

    while(!quit) {
        handleEvents(&quit, keyboardState);
        physicsCalculations();
        graphicsCalculations();

        SDL_UpdateWindowSurface(window);
        SDL_Delay(DELTA_TIME);
    }

    freeBody(player);
    freeBody(ball);

    SDL_Quit();
    return 0;
}


void handleEvents(int *quit, const Uint8 *keyboardState) {

    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT)
            *quit = 1;
    }

    SDL_PumpEvents();

    if(keyboardState[SDL_SCANCODE_UP])
        moveUp(player);

    else if(keyboardState[SDL_SCANCODE_DOWN])
        moveDown(player);

    else
        player->normalVelocity.y = 0;

    if(keyboardState[SDL_SCANCODE_LEFT])
        moveLeft(player);

    else if(keyboardState[SDL_SCANCODE_RIGHT])
        moveRight(player);

    else
        player->normalVelocity.x = 0;

    if(keyboardState[SDL_SCANCODE_SPACE]) {
        ball->position.x = player->position.x + center(player->size, ball->size);
        ball->position.y = player->position.y;
    }
}

void physicsCalculations() {
    updatePhysics(ball);
    updatePhysics(player);
}

void graphicsCalculations() {

    SDL_FillRect(screen, NULL, backgroundColor);

    SDL_FillRect(player->surface, NULL, playerColor);
    SDL_BlitSurface(player->surface, NULL, screen, &player->position);

    SDL_FillRect(ball->surface, NULL, ballColor);
    SDL_BlitSurface(ball->surface, NULL, screen, &ball->position);

}


