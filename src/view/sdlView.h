#ifndef SDLVIEW_H
#define SDLVIEW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "view.h"

/**
 * @struct SdlView
 * @brief structure de sdl
 */
typedef struct
{
	SDL_Window *window;		   //!< window
	SDL_Renderer *renderer;	   //!< le rendu
	SDL_Texture **tab_texture; //!< la tableau contenant les textures
	Mix_Chunk **tab_sounds;	   //!< le tableau contenant les sons
	int numImages;			   //!< le nombre de texture
	int numSounds;			   //!< le nombre de sons
} SdlView;

SdlView *createSdlView(unsigned w, unsigned h);
void sdlUpdateView(View *view, GameState *gameState);
void destroySdlView(View *view);
void afficherNombre(int n, int nb_chiffre, int x, int y, char *color, SdlView *sdlView);
void play_sound(View *view, int ind);
void sdlEvent(View *view, GameState *game);
#endif