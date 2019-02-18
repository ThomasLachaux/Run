#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60

#define PLAYER_SIZE 20

void handleEvents(int *quit);
void physicsCalculations();
void graphicsCalculations();

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Event e;

Uint32 backgroundColor;
Uint32 playerColor;

SDL_Rect playerPosition;

SDL_Surface* player = NULL;

int center(int a, int b) {
    return a / 2 - b / 2;
}

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);

    int quit = 0;

    backgroundColor = SDL_MapRGB(screen->format, 17, 206, 112);
    backgroundColor = SDL_MapRGB(screen->format, 255, 255, 255);


    player = SDL_CreateRGBSurface(0, PLAYER_SIZE, PLAYER_SIZE, 32, 0, 0, 0, 0);
    playerPosition.x = center(SCREEN_WIDTH, PLAYER_SIZE);
    playerPosition.y = SCREEN_HEIGHT * 3 / 4;

    while(!quit) {

        handleEvents(&quit);
        physicsCalculations();
        graphicsCalculations();


        SDL_UpdateWindowSurface(window);
        SDL_Delay(1000 / FPS);
    }

    SDL_FreeSurface(player);

    SDL_Quit();
    return 0;
}


void handleEvents(int *quit) {

    while(SDL_PollEvent(&e) != 0) {

        switch (e.type) {

            case SDL_QUIT:
                *quit = 1;
                break;
        }
    }
}

void physicsCalculations() {



}

void graphicsCalculations() {

    SDL_FillRect(screen, NULL, backgroundColor);


    SDL_FillRect(player, NULL, playerColor);
    SDL_BlitSurface(player, NULL, screen, &playerPosition);

}


