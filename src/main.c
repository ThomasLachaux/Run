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

    game.player = createBody(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, 20, 20, 4, playerColor, Player);

    game.world = createWorld();

    addBodyToWorld(game.world, game.player);

    /*Body *enemy;
    for(i = 0; i < SCREEN_WIDTH; i+= 20) {

        enemy = createBody(i, 20, 10, 10, 1, 0xCC0000, Enemy);
        enemy->normalVelocity.y = 1;
        addBodyToWorld(game.world, enemy);
    }*/

    Body *enemy = createBody(SCREEN_WIDTH / 2, 20, 10, 10, 1, 0xCC0000, Enemy);
    addBodyToWorld(game.world, enemy);




    while(!game.quit) {
        handleEvents(&game);
        updateWorldPhysics(game.world);


        Element *current = game.world->first;

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

enum Direction {
    Left, Right, Top, Bottom
};
typedef enum Direction Direction;

void shoot(Game *game, float velocityX, float velocityY) {

    Body *ball = createBody(game->player->transform.x, game->player->transform.y, 5, 5, 5, ballColor, Ball);

    ball->normalVelocity.x = velocityX;
    ball->normalVelocity.y = velocityY;

    addBodyToWorld(game->world, ball);
}

void handleEvents(Game *game) {

    while(SDL_PollEvent(&game->event) != 0) {
        if(game->event.type == SDL_QUIT)
            game->quit = 1;

        else if(game->event.type == SDL_KEYDOWN && game->event.key.repeat == 0) {

            switch (game->event.key.keysym.sym) {

                // Left
                case SDLK_s:
                    shoot(game, -1, 0);
                    break;

                // Right
                case SDLK_f:
                    shoot(game, 1, 0);
                    break;

                // Top
                case SDLK_e:
                    shoot(game, 0, -1);
                    break;

                // Bottom
                case SDLK_d:
                    shoot(game, 0, 1);
            }

        }
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

    //registerShootInput(game);
}

void drawBackground(SDL_Surface *screen) {
    SDL_FillRect(screen, NULL, backgroundColor);
}