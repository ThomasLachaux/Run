#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
    game.world->player = createBody(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, BIG, BIG, PLAYER_VELOCITY, PLAYER_COLOR, Player);

    addBodyToWorld(game.world, game.world->player);


    SDL_Surface *background = IMG_Load("background.png");
    SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(game.renderer, background);
    SDL_Surface *rules = IMG_Load("rules.png");
    SDL_Texture *bg_rules = SDL_CreateTextureFromSurface(game.renderer, rules);
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    pos.w = background->w;
    pos.h = background->h;

    createMenu(game.world);

    while(!game.quit) {
        handleEvents(&game);
        updateWorldPhysics(game.world);

        SDL_RenderCopy(game.renderer, game.world->isPlaying ? bg_texture : bg_rules, NULL, &pos);

        drawWorld(game.renderer, game.world);

        if(game.world->isPlaying) {
            increaseAndDrawScore(&game);
            displayWaveTime(&game);
        }

        else {
            drawButtonsText(&game);
        }

        SDL_RenderPresent(game.renderer);

        SDL_Delay(DELTA_TIME);
    }

    destroyGame(&game);
    return 0;
}

void handleEvents(Game *game) {

    while(SDL_PollEvent(&game->event) != 0) {
        if(game->event.type == SDL_QUIT)
            game->quit = 1;

        else if(game->event.type == SDL_KEYDOWN && game->event.key.repeat == 0) {

            switch (game->event.key.keysym.sym) {

                // Left
                case LEFT_AZERTY:
                case LEFT_QWERTY:
                    shoot(game->world, -1, 0);
                    break;

                // Right
                case RIGHT:
                    shoot(game->world, 1, 0);
                    break;

                // Top
                case TOP_AZERTY:
                case TOP_QWERTY:
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
    setRenderColor(renderer, BACKGROUND_COLOR);
    SDL_RenderClear(renderer);
}