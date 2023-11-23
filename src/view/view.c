#include "view.h"
#include "sdlView.h"

/**
 * @brief createView implementation. */
View *createView(TypeView typeView)
{
	if (typeView == SDL_VIEW)
		return createSdlView(256 * SCALE, 240 * SCALE);
} // createView

void updateView(TypeView typeView, View *view, GameState *game)
{
	if (typeView == SDL_VIEW)
		sdlUpdateView(view, game);
}

void destroyView(TypeView typeView, View *view)
{
	if (typeView == SDL_VIEW)
		destroySdlView(view);
}