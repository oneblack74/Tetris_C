#include <ncurses.h>
#include <stdlib.h>

#include "controller.h"
#include "sdlController.h"

void event(TypeController typeController, GameState *game, int *run)
{
    if (typeController == SDL_CONTROLLER)
    {
        sdlEvent(game, run);
    }
}