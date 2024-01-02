#ifndef NCURSESVIEW_H
#define NCURSESVIEW_H

#include <ncurses.h>
#include "view.h"

typedef struct
{
    WINDOW *board;
    WINDOW *stats;
    WINDOW *score;
    WINDOW *next;
    WINDOW *level;
} NcursesView;

View *createNcursesView();
void updateNcursesView(View *view, GameState *gameState);
void destroyNcursesView(View *view);
void ncursesEvent(GameState *game, int *run);

#endif