#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "world.h"

/**
 * Crée un monde. Un monde contient entre autre une liste chainées de corps. (On utilise la structure Element pour gérer cette liste chainée)
 */
World *createWorld() {
    World *world = malloc(sizeof(World));
    world->first = NULL;

    // Si les scores existent, les reprend, sinon il les met à 0
    FILE *file = fopen(SAVEFILE, "rb");

    if(file != NULL)
        fread(world->highScores, sizeof(int), 2, file);

    else {
        world->highScores[EASY] = 0;
        world->highScores[HARD] = 0;
    }

    return world;
}

/**
 * Crée le menu: le fond des 2 boutons du menu
 */
void createMenu(World *world) {
    world->window = MENU;
    world->score = 0;
    Body *easyButton = createBody(SCREEN_WIDTH / 4 - 300 / 2, SCREEN_HEIGHT / 6 * 5 - 50 / 2, 300, 50, 0, 0x222222, Easy);
    addBodyToWorld(world, easyButton);

    Body *hardButton = createBody(SCREEN_WIDTH / 4 * 3 - 300 / 2, SCREEN_HEIGHT / 6 * 5 - 50 / 2, 300, 50, 0, 0x222222, Hard);
    addBodyToWorld(world, hardButton);
}

/**
 * Crée le fond du bouton retry, et change la phrase de détermination
 */
void createGameOver(World *world) {
    world->window = GAME_OVER;
    world->determination = ranInt(0, 5);

    Body *retryButton = createBody(SCREEN_WIDTH / 2 - 300 / 2, SCREEN_HEIGHT / 2 - 50 / 2 + 100, 300, 50, 0, 0x222222, Retry);
    addBodyToWorld(world, retryButton);

    world->player->transform.x = SCREEN_WIDTH / 2;
    world->player->transform.y = SCREEN_HEIGHT * 3 / 4;

    // Remplace le highscore par le score actuel si le score actuel est plus elevé que le highscore
    // world->highScores[world->hardMode] permet d'acceder au highscore approprié. (Mode facile ou hard)
    world->highScores[world->hardMode] = world->score > world->highScores[world->hardMode] ? world->score : world->highScores[world->hardMode];

}

/**
 * Ajoute un corps au monde.
 */
void addBodyToWorld(World *world, Body *body) {

    Element *element = malloc(sizeof(Element));
    element->body = body;
    element->previous = NULL;
    element->next = NULL;

    if (world->first == NULL)
        world->first = element;

    else {
        Element *current = world->first;

        while (current->next != NULL)
            current = current->next;

        current->next = element;
        element->previous = current;
    }
}

/**
 * Fonction appelée lors d'une collision entre un ennemi et une balle.
 * Détruit l'ennemi et la balle et augment le score
 */
void onEnemyBallCollision(World *world, Body *enemy, Body *ball) {
    destroyBodyFromWorld(world, enemy);
    destroyBodyFromWorld(world, ball);
    world->score += 100;
}

/**
 * Fonction appelée lors d'une collsion entre un joueur et un ennemi.
 * Lance le game over
 */
void onPlayerEnemyCollision(World *world, Body *player, Body *enemy) {
    world->window = GAME_OVER;
    int i;
    for(i = 0; i <= 2; i++)
        SDL_RemoveTimer(world->timers[i]);


    // Supprime tous les ennemis et les items
    Element *current = world->first;
    while (current != NULL) {
        if(current->body->layer == Enemy || current->body->layer == Item) {
            Element *toDelete = current;

            destroyBodyFromWorld(world, toDelete->body);


        }

        current = current->next;
    }

    createGameOver(world);

}

/**
 * Fonction appelée lors d'une collision entre un joueur et un item.
 * Fait exploser l'item
 */
void onPlayerItemCollision(World *world, Body *player, Body *item) {
    int x,y;

    int steps = 10;

    for(x = -steps; x <= steps; x++) {
        for(y = -steps; y <= steps; y ++) {
            if(x != 0 || y != 0)
                shoot(world, (float) x / steps, (float) y / steps);
        }
    }

    destroyBodyFromWorld(world, item);
}

/**
 * Fonction appelée lors d'une collsion entre le joueur et le bouton facile
 */
void onPlayerEasyCollision(World *world, Body *player, Body *button) {
    world->hardMode = false;
    startGame(world, player, button);
}

/**
 * Fonction appelée lors d'une collsion entre le joueur et le bouton difficile
 */
void onPlayerHardCollision(World *world, Body *player, Body *button) {
    world->hardMode = true;
    startGame(world, player, button);
}

/**
 * Fonction appelée lors d'une collsion entre le joueur et le bouton recommencer
 */
void onPlayerRetryCollision(World *world, Body *player, Body *button) {
    destroyBodyFromWorld(world, button);
    createMenu(world);
}

/**
 * Démarre le jeu, supprime le bouton easy et hard
 */
void startGame(World *world, Body *player, Body *button) {
    world->window = GAME;
    world->startTime = SDL_GetTicks();
    WAVE_TIME = world->hardMode ? WAVE_TIME_HARD : WAVE_TIME_EASY;

    spawnWave(0, world);

    world->timers[0] = SDL_AddTimer(SPAWN_TIME, createEnemy, world);
    world->timers[1] = SDL_AddTimer(WAVE_TIME, spawnWave, world);
    world->timers[2] = SDL_AddTimer(5000, createItem, world);

    onPlayerItemCollision(world, player, button);

    Element *current = world->first;
    while (current != NULL) {
        if(current->body->layer == Easy || current->body->layer == Hard) {
            Element *toDelete = current;
            destroyBodyFromWorld(world, toDelete->body);
        }
        current = current->next;
    }
}

/**
 * Met à jour la position de tous les corps du monde
 */
void updateWorldPhysics(World *world) {
    Element *current = world->first;

    while (current != NULL) {
        updateBodyPhysics(current->body);

        if(current->body->layer == Player)
            limitPosition(current->body);

        else if(current->body->layer == Ball && isOffScreen(current->body))
            destroyBodyFromWorld(world, current->body);

        else if(current->body->layer == Enemy)
            follow(current->body, world->player);

        current = current->next;
    }

    registerCollision(world, Enemy, Ball, onEnemyBallCollision);
    registerCollision(world, Player, Enemy, onPlayerEnemyCollision);
    registerCollision(world, Player, Item, onPlayerItemCollision);
    registerCollision(world, Player, Easy, onPlayerEasyCollision);
    registerCollision(world, Player, Hard, onPlayerHardCollision);
    registerCollision(world, Player, Retry, onPlayerRetryCollision);
}

/**
 * Dessine tous les corps du monde
 */
void drawWorld(SDL_Renderer *screen, World *world) {
    Element *current = world->first;

    while (current != NULL) {
        drawBody(screen, current->body);
        current = current->next;
    }
}

/**
 * Détruit tous les corps du monde et enregistre les score
 */
void destroyWorld(World *world) {
    // Destruction des elements
    Element *current = world->first;
    Element *toDestroy;

    while (current != NULL) {
        toDestroy = current;
        current = current->next;

        destroyBody(toDestroy->body);
        free(toDestroy);
    }

    // Ecriture des scores
    FILE *file = fopen(SAVEFILE, "wb");
    fwrite(world->highScores, sizeof(int), 2, file);

    free(world);
}

/**
 * Détruit un coprs et le supprime du monde
 */
void destroyBodyFromWorld(World *world, Body *body) {
    Element *to_delete = world->first;
    Element *previous, *next;

    while (to_delete != NULL && to_delete->body != body) {
        to_delete = to_delete->next;
    }

    if(to_delete != NULL) {

        previous = to_delete->previous;
        next = to_delete->next;

        // If first element
        if (previous == NULL) {

            world->first = next;

            if (next != NULL)
                next->previous = NULL;
        }

            // If not first element
        else {
            previous->next = next;

            if (next != NULL)
                next->previous = previous;
        }

        destroyBody(to_delete->body);

        /*
         * Il faudrait décommenter la ligne si dessous pour que la mémoire soit libérée.
         * Cependant, cela provoque des erreurs alétoire dans l'application qui entrainent un crash.
         * Je n'ai pas trouvé la vrai source du problème, et comme la fuite de mémoire est extrement faible;
         * J'ai préféré commenter cette ligne
         */
        //free(to_delete);
    }
}

/**
 * Ajoute un item au monde
 */
Uint32 createItem(Uint32 interval, void *world) {
    int x = ranInt(MEDIUM, SCREEN_WIDTH - MEDIUM);
    int y = ranInt(MEDIUM, SCREEN_HEIGHT - MEDIUM);

    Body *item = createBody(x, y, MEDIUM, MEDIUM, 0, ITEM_COLOR, Item);
    addBodyToWorld(world, item);

    return interval;
}

/**
 * Ajoute un ennemi au monde qui suit le joueur
 * Retourne un interval plus petit jusq'a une limite pour faire une acceleration
 */
Uint32 createEnemy(Uint32 interval, void *world) {

    int x = ranInt(0, 1) ? 0: SCREEN_WIDTH;
    int y = ranInt(0, SCREEN_HEIGHT);

    int velocity = !((World*) world)->hardMode ? ENEMY_VELOCITY_EASY : ENEMY_VELOCITY_HARD;

    Body *enemy = createBody(x, y, MEDIUM, MEDIUM, velocity, ENEMY_COLOR, Enemy);
    addBodyToWorld(world, enemy);

    return (Uint32) maxInt(SPAWN_MIN, interval - DELTA_TIME);
}

/**
 * Crée une vague d'ennemis
 */
Uint32 spawnWave(Uint32 interval, void *world) {
    int i;

    for(i = 0; i < WAVE_LENGTH; i++)
        createEnemy(0, world);

    return interval;
}

/**
 * Permet au joueur de tirer
 */
void shoot(World *world, float velocityX, float velocityY) {

    int x = world->player->transform.x + BIG / 2 - SMALL / 2;
    int y = world->player->transform.y + BIG / 2 - SMALL / 2;

    int velocity = !world->hardMode ? BALL_VELOCITY_EASY : BALL_VELOCITY_HARD;

    Body *ball = createBody(x, y, SMALL, SMALL, velocity, BALL_COLOR, Ball);

    ball->direction.x = velocityX;
    ball->direction.y = velocityY;

    addBodyToWorld(world, ball);
}

/**
 * Enregistre la collision entre 2 couches. Si il y a collision, appelle la fonction passée en paramètre.
 * Par convention, le nom du callback s'appelle on[LayerA][LayerB]Collision
 */
void registerCollision(World *world, Layer layerA, Layer layerB, void (*callback)(World *, Body *, Body *)) {

    Element *elementA, *elementB, *nextElementA, *nextElementB;
    Body *bodyA, *bodyB;

    elementA = world->first;

    // Premier parcours
    while (elementA != NULL) {
        
        nextElementA = elementA->next;
        
        // Recherche dans le layerA
        if (elementA->body->layer == layerA) {

            elementB = world->first;
            
            while (elementB != NULL) {

                nextElementB = elementB->next;
                
                // Recherche dans le layerB
                if (elementB->body->layer == layerB) {

                    bodyA = elementA->body;
                    bodyB = elementB->body;

                    // Si collision, alors appel du callback
                    if (
                            bodyA->transform.x < bodyB->transform.x + bodyB->transform.w &&
                            bodyA->transform.x + bodyA->transform.w > bodyB->transform.x &&
                            bodyA->transform.y < bodyB->transform.y + bodyB->transform.h &&
                            bodyA->transform.h + bodyA->transform.y > bodyB->transform.y) {

                            (*callback)(world, bodyA, bodyB);
                    }
                }

                elementB = nextElementB;
            }
        }
        elementA = nextElementA;
    }
}