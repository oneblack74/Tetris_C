/**
 * @file view.c
 * @author Hurez Matteo and Brissy Axel
 * @brief vue du tetris
 * @version 1.0
 * @date 2024−01−04
 *
 * @copyright Copyright(c) 2024
 */
#include "view.h"
#include "sdlView.h"
#include "ncursesView.h"

/**
 * @brief permet d'initialiser la vue avec sdl
 *
 * @param w la largeur de la fenetre sdl
 * @param h la hauteur de la fenetre sdl
 */
View sdlView_init(unsigned w, unsigned h)
{
	View view;
	view.typeView = SDL_VIEW;
	view.instanciation = createSdlView(w, h);
	Functions_View *f = (Functions_View *)malloc(sizeof(Functions_View));
	if (!f)
	{
		perror("malloc()\n");
		exit(EXIT_FAILURE);
	}
	view.functions = f;
	view.functions->updateView = sdlUpdateView;
	view.functions->destroyView = destroySdlView;
	view.functions->play_sound = play_sound;
	view.functions->event = sdlEvent;
	return view;
}

/**
 * @brief permet d'initialiser la vue avec ncurses
 */
View ncursesView_init()
{
	View view;
	view.typeView = NCURSES_VIEW;
	view.instanciation = createNcursesView();
	Functions_View *f = (Functions_View *)malloc(sizeof(Functions_View));
	if (!f)
	{
		perror("malloc()\n");
		exit(EXIT_FAILURE);
	}
	view.functions = f;
	view.functions->updateView = updateNcursesView;
	view.functions->destroyView = destroyNcursesView;
	view.functions->play_sound = NULL;
	view.functions->event = ncursesEvent;
	return view;
}