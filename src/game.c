#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

/**
 * Initialise la SDL et la fenetre
 */
Game initGame() {

    Game game;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    TTF_Init();

    game.font = TTF_OpenFont(ASSETS("LemonMilk.ttf"), 20);
    game.bigFont = TTF_OpenFont(ASSETS("LemonMilk.ttf"), 50);


    game.window = SDL_CreateWindow("Run !", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);

    game.keyboardState = SDL_GetKeyboardState(NULL);

    game.quit = false;

    return game;
}

/**
 * Détruie proprement la SDL
 */
void destroyGame(Game *game) {
    destroyWorld(game->world);
    SDL_DestroyWindow(game->window);

    TTF_CloseFont(game->font);

    TTF_Quit();
    SDL_Quit();
}

/**
 * Retourne le minimum des 2 entiers en argument
 */
int minInt(int x, int y) {
    return x < y ? x : y;
}

/**
 * Retourne le maximum des 2 entiers en argument
 */
int maxInt(int x, int y) {
    return x > y ? x : y;
}

/**
 * Retourne la valeur si elle est comprise entre le min et le max, sinon l'une des 2 bornes
 */
int clamp(int lower, int x, int upper) {
    return minInt(upper, maxInt(x, lower));
}

/**
 * Retourne un vecteur normal
 */
void normalizeVector(Vector *vector) {
    double magnitude = sqrt(pow(vector->x, 2) + pow(vector->y, 2));

    if(magnitude != 0) {
        vector->x /= magnitude;
        vector->y /= magnitude;
    }
}

/**
 * Retourne un entier aléatoire entre les 2 bornes
 */
int ranInt(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

/** Override la fonction SDL_SetRenderDrawColor pour pouvoir utiliser les couleurs en hexadécimal
 *
 */
int setRenderColor(SDL_Renderer *renderer, Uint32 color) {

    Uint8 r, g, b, a;

    r = color / (256 * 256);
    g = color / 256 % 256;
    b = color % 256;
    a = 0xFF;

    return SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

/**
 * Transform une couleur hexadécimale en SDL_Color
 */
SDL_Color hexToSDLColor(Uint32 hex) {
    Uint8 r, g, b;

    r = hex / (256 * 256);
    g = hex / 256 % 256;
    b = hex % 256;

    SDL_Color color = {r, g, b};

    return color;
}

/**
 * Augmente le score au fur et à mesure du temps et le dessine
 */
void increaseAndDrawScore(Game *game) {
    char displayScore[6];

    sprintf(displayScore, "%06d", game->world->score);

    SDL_Surface *text = TTF_RenderText_Blended(game->font, displayScore, hexToSDLColor(0x000000));

    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, text);

    SDL_Rect pos;
    pos.x = SCREEN_WIDTH - 100;
    pos.y = 10;
    pos.w = text->w;
    pos.h = text->h;

    SDL_RenderCopy(game->renderer, texture, NULL, &pos);

    game->world->score += DELTA_TIME / 10;

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(text);
}

void drawWaveTime(Game *game) {
    int time = WAVE_TIME - (SDL_GetTicks() - game->world->startTime) % WAVE_TIME;
    time /= 1000;
    time += 1;
    char timeDisplay[16];
    sprintf(timeDisplay, "Vague: %02d s", time);

    // Affiche rouge si le temps est inférieur à 10 et qu'il est pair
    Uint32 color = time <= 10 && time % 2 == 0 ? 0xCC0000 : 0x000000;

    SDL_Surface *text = TTF_RenderText_Blended(game->font, timeDisplay, hexToSDLColor(color));

    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, text);

    SDL_Rect pos;
    pos.x = 10;
    pos.y = 10;
    pos.w = text->w;
    pos.h = text->h;

    SDL_RenderCopy(game->renderer, texture, NULL, &pos);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(text);
}

/**
 * Dessine les textes des boutons du menu
 */
void drawMenuText(Game *game) {

    SDL_Color color = hexToSDLColor(0xFFFFFF);
    SDL_Surface *text = TTF_RenderText_Blended(game->font, "Mode facile", color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, text);


    SDL_Rect pos;
    pos.w = text->w;
    pos.h = text->h;
    pos.x = SCREEN_WIDTH / 4 - pos.w / 2;
    pos.y = SCREEN_HEIGHT / 6 * 5 - pos.h / 2;

    SDL_RenderCopy(game->renderer, texture, NULL, &pos);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(texture);

    text = TTF_RenderText_Blended(game->font, "Mode vraiment dur", color);
    texture = SDL_CreateTextureFromSurface(game->renderer, text);
    pos.w = text->w;
    pos.h = text->h;
    pos.x = SCREEN_WIDTH / 4 * 3 - pos.w / 2;
    SDL_RenderCopy(game->renderer, texture, NULL, &pos);

    SDL_FreeSurface(text);
    SDL_DestroyTexture(texture);
}

/**
 * Dessine les textes du menu du gameOver
 */
void drawGameoverText(Game *game) {
    SDL_Color white = hexToSDLColor(0xFFFFFF);
    SDL_Color black = hexToSDLColor(0x000000);
    SDL_Surface *text = TTF_RenderText_Blended(game->font, "Recommencer", white);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, text);

    SDL_Rect pos;
    pos.w = text->w;
    pos.h = text->h;
    pos.x = SCREEN_WIDTH / 2 - pos.w / 2;
    pos.y = SCREEN_HEIGHT / 2 - pos.h / 2 + 100;

    SDL_RenderCopy(game->renderer, texture, NULL, &pos);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(texture);

    char displayScore[6];

    sprintf(displayScore, "%06d - %06d", game->world->score, game->world->highScores[game->world->hardMode]);

    text = TTF_RenderText_Blended(game->bigFont, displayScore, black);

    texture = SDL_CreateTextureFromSurface(game->renderer, text);

    pos.w = text->w;
    pos.h = text->h;
    pos.x = SCREEN_WIDTH / 2 - pos.w / 2;
    pos.y = 200;

    SDL_RenderCopy(game->renderer, texture, NULL, &pos);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(text);


    // source: Undertale
    char *determination[6];
    determination[0] = "Tu ne peux pas abandonner comme ça, reste déterminé !";
    determination[1] = "Ce n'est pas terminé, reste déterminé !";
    determination[2] = "Ne perds pas espoir, reste déterminé !";
    determination[3] = "Cela ne peut pas se terminer ainsi, reste déterminé !";
    determination[4] = "Tu dois continuer, reste déterminé !";
    determination[5] = "S'il te plaît, n'abandonne pas, reste déterminé !";

    text = TTF_RenderUTF8_Blended(game->font, determination[game->world->determination], black);
    texture = SDL_CreateTextureFromSurface(game->renderer, text);

    pos.w = text->w;
    pos.h = text->h;
    pos.x = SCREEN_WIDTH / 2 - pos.w / 2;
    pos.y = 300;

    SDL_RenderCopy(game->renderer, texture, NULL, &pos);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(text);

}