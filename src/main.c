/**
 * @brief Projet effectué dans le cadre de l'UE Microprocesseur en P19
 * @author Thomas de Lachaux
 * @ref https://github.com/ThomasLachaux/SpaceShooter
 * @copyright This project is released under the GNU Public License.
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#include "game.h"
#include "body.h"
#include "world.h"


void handleEvents(Game *game);


int main(int argc, char *argv[]) {

    // Seed modifiée
    srand(time(NULL));


    Game game = initGame();

    // Création du joueur
    game.world = createWorld();
    game.world->player = createBody(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, BIG, BIG, PLAYER_VELOCITY, PLAYER_COLOR, Player);

    addBodyToWorld(game.world, game.world->player);

    // Initialisation du logo
    SDL_Surface *logo = IMG_Load(ASSETS("logo.png"));
    SDL_SetWindowIcon(game.window, logo);

    // Initialisation des images de fond ainsi que les textures
    SDL_Surface *background = IMG_Load(ASSETS("background.png"));
    SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(game.renderer, background);

    SDL_Surface *rules = IMG_Load(ASSETS("rules.png"));
    SDL_Texture *bg_rules = SDL_CreateTextureFromSurface(game.renderer, rules);

    SDL_Surface *gameover = IMG_Load(ASSETS("gameover.png"));
    SDL_Texture *bg_gameover = SDL_CreateTextureFromSurface(game.renderer, gameover);

    // Initialisation des coordonées du fond. Comme la taille des images est la même, on se base sur la première
    SDL_Rect bg_pos;
    bg_pos.x = 0;
    bg_pos.y = 0;
    bg_pos.w = background->w;
    bg_pos.h = background->h;


    createMenu(game.world);

    while(!game.quit) {
        handleEvents(&game);
        updateWorldPhysics(game.world);

        // Dessine le fond adapté
        SDL_RenderCopy(game.renderer, game.world->window == MENU ? bg_rules : game.world->window == GAME_OVER ? bg_gameover : bg_texture, NULL, &bg_pos);

        // Dessine tous les corps du jeu
        drawWorld(game.renderer, game.world);

        // Dessine le texte
        switch (game.world->window) {
            case MENU:
                drawMenuText(&game);
                break;

            case GAME:
                increaseAndDrawScore(&game);
                drawWaveTime(&game);
                break;

            case GAME_OVER:
                drawGameoverText(&game);
                break;
        }

        // Met à jour la fenêtre
        SDL_RenderPresent(game.renderer);
        SDL_Delay(DELTA_TIME);
    }


    // Liberation de la mémoire

    SDL_FreeSurface(logo);

    SDL_DestroyTexture(bg_texture);
    SDL_FreeSurface(background);

    SDL_DestroyTexture(bg_rules);
    SDL_FreeSurface(rules);

    SDL_DestroyTexture(bg_gameover);
    SDL_FreeSurface(gameover);

    destroyGame(&game);
    return 0;
}

/**
 * Gère tous entrées de l'utilisateur (clavier et souris)
 */
void handleEvents(Game *game) {

    // Tant qu'il y a des evenements à gerer
    while(SDL_PollEvent(&game->event) != 0) {
        // Si l'utilisateur quitte (Alt+F4 ou croix)
        if(game->event.type == SDL_QUIT)
            game->quit = 1;

        // Lors d'une entrée clavier (seulement en evenement -> permet de limiter les tirs/seconde facilement)
        else if(game->event.type == SDL_KEYDOWN && game->event.key.repeat == 0) {

            // Gère les tirs du joueur
            switch (game->event.key.keysym.sym) {

                // Gauche
                case LEFT_AZERTY:
                case LEFT_QWERTY:
                    shoot(game->world, -1, 0);
                    break;

                // Droite
                case RIGHT:
                    shoot(game->world, 1, 0);
                    break;

                // Haut
                case TOP_AZERTY:
                case TOP_QWERTY:
                    shoot(game->world, 0, -1);
                    break;

                // Bas
                case BOTTOM:
                    shoot(game->world, 0, 1);
            }

        }
    }

    // Rafraichissement des evenements clavier (keyboardStateà
    SDL_PumpEvents();

    // Gere le mouvement du joueur
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