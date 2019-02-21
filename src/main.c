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

    Body *enemy;
    for(i = 0; i < SCREEN_WIDTH; i+= 20) {

        enemy = createBody(i, 20, 10, 10, 1, 0xCC0000, Enemy);
        enemy->normalVelocity.y = 1;
        addBodyToWorld(game.world, enemy);
    }




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

void registerShootInput(Game *game) {

    static int previous;
    int current = 0;

    if(game->keyboardState[SDL_SCANCODE_SPACE])
        current = 1;

    if(current == 1 && previous == 0) {
        Body *ball = createBody(game->player->transform.x + 5, game->player->transform.y + 5, 5, 5, 5, ballColor, Ball);
        ball->normalVelocity.y = -1;
        addBodyToWorld(game->world, ball);
    }

    previous = current;
}

void onKeyPress(Game *game, int scancode, int *previous) {

    int current = 0;

    if(game->keyboardState[scancode])
        current = 1;

    if(current == 1 && previous == 0) {
        Body *ball = createBody(game->player->transform.x + 5, game->player->transform.y + 5, 5, 5, 5, ballColor, Ball);
        ball->normalVelocity.y = -1;
        addBodyToWorld(game->world, ball);
    }

    *previous = current;
}

enum Direction {
    Left, Right, Top, Bottom
};
typedef enum Direction Direction;

void shoot(Game *game, Direction direction) {

    Body *ball = createBody(game->player->transform.x, game->player->transform.y, 5, 5, 5, ballColor, Ball);

    // Passe la vitesse normale à -1 si gauche, 1 si droite, 0 si autre
    ball->normalVelocity.x = direction == Left ? -1 : direction == Right ? 1 : 0;

    // Passe la vitesse normale à -1 si haut, 1 si bas, 0 si autre
    ball->normalVelocity.y = direction == Top ? -1 : direction == Bottom ? 1 : 0;

    addBodyToWorld(game->world, ball);
}

void handleEvents(Game *game) {

    while(SDL_PollEvent(&game->event) != 0) {
        if(game->event.type == SDL_QUIT)
            game->quit = 1;

        else if(game->event.type == SDL_KEYDOWN && game->event.key.repeat == 0) {

            switch (game->event.key.keysym.sym) {

                case SDLK_s:
                    shoot(game, Left);
                    break;

                case SDLK_f:
                    shoot(game, Right);
                    break;

                case SDLK_e:
                    printf("SHHOOOOTT \n");
                    shoot(game, Top);
                    break;

                case SDLK_d:
                    shoot(game, Bottom);
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