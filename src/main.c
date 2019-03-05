#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "game.h"
#include "body.h"
#include "world.h"

int i;

void handleEvents(Game *game);
void drawBackground(SDL_Renderer *renderer);

// todo: reorganiser code



int main(int argc, char *argv[]) {

    srand(time(NULL));

    Game game = initGame();


    game.world = createWorld();
    game.world->player = createBody(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, BIG, BIG, 4, BLACK, Player);

    addBodyToWorld(game.world, game.world->player);

    for(i = 0; i < 6; i++)
        createEnemy(0, game.world);

    SDL_AddTimer(2000, createEnemy, game.world);

    while(!game.quit) {
        handleEvents(&game);
        updateWorldPhysics(game.world);

        drawBackground(game.renderer);
        drawWorld(game.renderer, game.world);

        SDL_RenderPresent(game.renderer);
        SDL_Delay(DELTA_TIME);
    }

    destroyWorld(game.world);
    SDL_DestroyWindow(game.window);

    SDL_Quit();
    return 0;
}

void handleEvents(Game *game) {

    while(SDL_PollEvent(&game->event) != 0) {
        if(game->event.type == SDL_QUIT)
            game->quit = 1;

        else if(game->event.type == SDL_KEYDOWN && game->event.key.repeat == 0) {

            switch (game->event.key.keysym.sym) {

                // Left
                case LEFT:
                    shoot(game->world, -1, 0);
                    break;

                // Right
                case RIGHT:
                    shoot(game->world, 1, 0);
                    break;

                // Top
                case TOP:
                    shoot(game->world, 0, -1);
                    break;

                // Bottom
                case BOTTOM:
                    shoot(game->world, 0, 1);
            }

        }
    }

    SDL_PumpEvents();

    if(game->keyboardState[SDL_SCANCODE_UP])
        moveUp(game->world->player);

    else if(game->keyboardState[SDL_SCANCODE_DOWN])
        moveDown(game->world->player);

    else
        game->world->player->direction.y = 0;

    if(game->keyboardState[SDL_SCANCODE_LEFT])
        moveLeft(game->world->player);

    else if(game->keyboardState[SDL_SCANCODE_RIGHT])
        moveRight(game->world->player);

    else
        game->world->player->direction.x = 0;
}

void drawBackground(SDL_Renderer *renderer) {
    setRenderColor(renderer, GREEN);
    SDL_RenderClear(renderer);
}