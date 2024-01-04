#ifndef VIEW_H
#define VIEW_H

#include "modele/modele.h"

typedef struct GameState GameState;
typedef struct View View;

/**
 * @enum TypeView
 * @brief énumeration du type de vue
 */
typedef enum
{
	SDL_VIEW,	 //!< vue sdl
	NCURSES_VIEW //!< vue ncurses
} TypeView;

/**
 * @struct Functions_View
 * @brief structure des pointeurs de fonction
 */
typedef struct
{
	void (*updateView)(View *view, GameState *); //!< fonction update
	void (*destroyView)(View *view);			 //!< fonction destroy
	void (*play_sound)(View *view, int);		 //!< fonction pour jouer un son
	void (*event)(View *view, GameState *);		 //!< fonction evennement
} Functions_View;

/**
 * @struct View
 * @brief structure de la vue
 */
typedef struct View
{
	TypeView typeView;		   //!< enum du type de vue
	Functions_View *functions; //!< les pointeurs de fonction
	void *instanciation;	   //!< l'espace memoir pour mettre la structure de sdl ou ncurses
} View;

View sdlView_init(unsigned w, unsigned h);
View ncursesView_init();
#endif
