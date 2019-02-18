#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "body.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60

#define PLAYER_SIZE 20
#define PLAYER_SPEED 3

#define BALL_SIZE 2
#define BALL_SPEED 5



void handleEvents(int *quit, const Uint8 *keyboardState);
void physicsCalculations();
void graphicsCalculations();

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Event e;

Uint32 backgroundColor;
Uint32 playerColor;

int center(int a, int b) {
    return a / 2 - b / 2;
}

Body player;
Body ball;

int main(int argc, char *argv[]) {

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);

    int quit = 0;

    backgroundColor = 0x11CE70;
    playerColor = 0x000000;


    player = createBody(PLAYER_SIZE, center(SCREEN_WIDTH, PLAYER_SIZE), SCREEN_HEIGHT * 3 / 4);
    ball = createBody(BALL_SIZE, player.position.x + 5, player.position.y + 5);

    while(!quit) {
        handleEvents(&quit, keyboardState);
        physicsCalculations();
        graphicsCalculations();



        SDL_UpdateWindowSurface(window);
        SDL_Delay(1000 / FPS);
    }

    freeBody(player);
    freeBody(ball);

    SDL_Quit();
    return 0;
}


void handleEvents(int *quit, const Uint8 *keyboardState) {

    while(SDL_PollEvent(&e) != 0) {

        switch (e.type) {

            case SDL_QUIT:
                *quit = 1;
                break;
        }
    }

    SDL_PumpEvents();

    if(keyboardState[SDL_SCANCODE_UP])
        player.position.y -= PLAYER_SPEED;

    else if(keyboardState[SDL_SCANCODE_DOWN])
        player.position.y += PLAYER_SPEED;

    if(keyboardState[SDL_SCANCODE_LEFT])
        player.position.x -= PLAYER_SPEED;

    else if(keyboardState[SDL_SCANCODE_RIGHT])
        player.position.x += PLAYER_SPEED;


}

void physicsCalculations() {



}

void graphicsCalculations() {

    SDL_FillRect(screen, NULL, backgroundColor);

    SDL_FillRect(player.surface, NULL, playerColor);
    SDL_BlitSurface(player.surface, NULL, screen, &player.position);

}


