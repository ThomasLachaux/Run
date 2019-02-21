#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "body.h"
#include "world.h"

Body *player = NULL;
Body *ball = NULL;
Body *enemy = NULL;

int i;

void handleEvents(int *quit, const Uint8 *keyboardState);

void drawBackground(SDL_Surface *screen);

int main(int argc, char *argv[]) {

    Game game = initGame();

    player = createBody(20, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, 4, playerColor, Player);

    ball = createBody(5, player->position.x + 5, player->position.y + 5, 5, ballColor, Ball);
    ball->normalVelocity.y = -1;

    game.world = createWorld();

    addBodyToWorld(game.world, player);
    addBodyToWorld(game.world, ball);

    for(i = 0; i < SCREEN_WIDTH; i+= 20) {

        enemy = createBody(10, i, 20, 1, 0xCC0000, Enemy);
        enemy->normalVelocity.y = 1;
        addBodyToWorld(game.world, enemy);
    }

    while(!game.quit) {
        handleEvents(&game.quit, game.keyboardState);
        updateWorldPhysics(game.world);

        drawBackground(game.screen);
        drawWorld(game.screen, game.world);

        SDL_UpdateWindowSurface(game.window);
        SDL_Delay(DELTA_TIME);
    }

    destroyWorld(game.world);
    SDL_DestroyWindow(game.window);

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

void drawBackground(SDL_Surface *screen) {
    SDL_FillRect(screen, NULL, backgroundColor);
}