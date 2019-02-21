#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "body.h"
#include "world.h"

int i;

void handleEvents(Game *game);

void drawBackground(SDL_Surface *screen);

int main(int argc, char *argv[]) {

    Game game = initGame();

    game.player = createBody(20, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, 4, playerColor, Player);

    game.world = createWorld();

    addBodyToWorld(game.world, game.player);


    Body *enemy;
    for(i = 0; i < SCREEN_WIDTH; i+= 20) {

        enemy = createBody(10, i, 20, 1, 0xCC0000, Enemy);
        enemy->normalVelocity.y = 1;
        addBodyToWorld(game.world, enemy);
    }

    while(!game.quit) {
        handleEvents(&game);
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

void registerShootInput(Game *game) {

    static int previous;
    int current = 0;

    if(game->keyboardState[SDL_SCANCODE_SPACE])
        current = 1;

    if(current == 1 && previous == 0) {
        Body *ball = createBody(5, game->player->position.x + 5, game->player->position.y + 5, 5, ballColor, Ball);
        ball->normalVelocity.y = -1;
        addBodyToWorld(game->world, ball);
    }

    previous = current;
}


void handleEvents(Game *game) {

    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT)
            game->quit = 1;
    }

    SDL_PumpEvents();

    if(game->keyboardState[SDL_SCANCODE_UP])
        moveUp(game->player);

    else if(game->keyboardState[SDL_SCANCODE_DOWN])
        moveDown(game->player);

    else
        game->player->normalVelocity.y = 0;

    if(game->keyboardState[SDL_SCANCODE_LEFT])
        moveLeft(game->player);

    else if(game->keyboardState[SDL_SCANCODE_RIGHT])
        moveRight(game->player);

    else
        game->player->normalVelocity.x = 0;

    registerShootInput(game);
}

void drawBackground(SDL_Surface *screen) {
    SDL_FillRect(screen, NULL, backgroundColor);
}