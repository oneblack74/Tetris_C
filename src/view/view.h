#ifndef VIEW_H
#define VIEW_H

#include "modele/modele.h"

typedef struct View View;

typedef enum
{
	SDL_VIEW,
	NCURSES_VIEW
} TypeView;

typedef struct
{
	void (*updateGrid)(struct View *, GameState *);
} Functions_View;

struct View
{
	Functions_View functions;
	void *instanciation;
};

View *createView(TypeView typeView);
void updateView(TypeView typeView, View *view, GameState *game);
void destroyView(TypeView typeView, View *view);

#endif
