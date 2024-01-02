#ifndef SDLVIEW_H
#define SDLVIEW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "view.h"

typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture **tab_texture;
	Mix_Chunk **tab_sounds;
	int numImages;
	int numSounds;
} SdlView;

SdlView *createSdlView(unsigned w, unsigned h);
void sdlUpdateView(View *view, GameState *gameState);
void destroySdlView(View *view);
void afficherNombre(int n, int nb_chiffre, int x, int y, char *color, SdlView *sdlView);
void play_sound(View *view, int ind);
void sdlEvent(View *view, GameState *game);
#endif