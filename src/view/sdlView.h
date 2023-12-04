#ifndef SDLVIEW_H
#define SDLVIEW_H

#include <SDL2/SDL.h>
#include "view.h"

typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture **tab_texture;
	int numImages;
} SdlView;

View *createSdlView(unsigned w, unsigned h);
void sdlUpdateView(View *view, GameState *gameState);
void destroySdlView(View *view);
void afficherNombre(int n, int nb_chiffre, int x, int y, char *color, SdlView *sdlView);

#endif