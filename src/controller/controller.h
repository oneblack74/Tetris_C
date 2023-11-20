#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "modele/modele.h"
#include "view/view.h"

typedef enum
{
    SDL_CONTROLLER,
    NCURSES_CONTROLLER
} TypeController;

typedef struct Functions_Controller
{
    void (*event)(GameState *);
} Functions_Controller;

void event(TypeController typeController, GameState *game, int *run);

#endif