#ifndef VIEW_H
#define VIEW_H

#include "modele/modele.h"

typedef struct GameState GameState;
typedef struct View View;

typedef enum
{
	SDL_VIEW,
	NCURSES_VIEW
} TypeView;

typedef struct
{
	void (*updateView)(View *view, GameState *);
	void (*destroyView)(View *view);
	void (*play_sound)(View *view, int);

} Functions_View;

struct View
{
	TypeView typeView;
	Functions_View *functions;
	void *instanciation;
};

View sdlView_init(unsigned w, unsigned h);
View ncursesView_init();
#endif
