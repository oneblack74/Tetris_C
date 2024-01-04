#ifndef NCURSESVIEW_H
#define NCURSESVIEW_H

#include <ncurses.h>
#include "view.h"

/**
 * @struct NcursesView
 * @brief structure qui contient les différentes fenêtres de la vue ncurses
 */
typedef struct
{
    WINDOW *title; //!< fenêtre de l'affichage du nom du jeu
    WINDOW *board; //!< fenêtre de la matrice du tetris
    WINDOW *stats; //!< fenêtre de la distibution des pièces
    WINDOW *score; //!< fenêtre de l'affichage du score et du record
    WINDOW *next;  //!< fenêtre de l'affichage de la pièce suivante
    WINDOW *level; //!< fenêtre de l'affichage des lignes et du niveau
} NcursesView;

NcursesView *createNcursesView();
void updateNcursesView(View *view, GameState *game);
void destroyNcursesView(View *view);
void ncursesEvent(View *view, GameState *game);

#endif