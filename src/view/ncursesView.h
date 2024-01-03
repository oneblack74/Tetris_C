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

NcursesView *createNcursesView();
void updateNcursesView(View *view, GameState *game);
void destroyNcursesView(View *view);
void ncursesEvent(View *view, GameState *game);

#endif