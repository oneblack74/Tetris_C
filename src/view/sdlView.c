#include <stdio.h>
#include <stdlib.h>

#include "sdlView.h"
#include "modele/modele.h"
#include <SDL2/SDL_image.h>

// 24 - 93

/**
 * @brief createSdlView implementation.
 */
View *createSdlView(unsigned w, unsigned h)
{
	View *ret = (View *)malloc(sizeof(View));
	if (!ret)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	SdlView *sdlView = (SdlView *)malloc(sizeof(SdlView));
	if (!sdlView)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	/* Initialise SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Erreur lors de l'initialisation de la SDL : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_CreateWindowAndRenderer(w, h, SDL_INIT_VIDEO, &sdlView->window, &sdlView->renderer);
	if (!sdlView->window || !sdlView->renderer)
	{
		fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
		return NULL;
	}

	sdlView->numImages = 3;

	// Allouez de l'espace pour le tableau de textures
	sdlView->tab_texture = (SDL_Texture **)malloc(sdlView->numImages * sizeof(SDL_Texture *));
	if (!sdlView->tab_texture)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	SDL_Surface *imageSurface;

	imageSurface = IMG_Load("src/img/background.png");
	if (!imageSurface)
	{
		fprintf(stderr, "Erreur chargement de l'image : %s", SDL_GetError());
		return NULL;
	}
	sdlView->tab_texture[0] = SDL_CreateTextureFromSurface(sdlView->renderer, imageSurface);
	SDL_FreeSurface(imageSurface);
	imageSurface = IMG_Load("src/img/stats_tilesheet.png");
	if (!imageSurface)
	{
		fprintf(stderr, "Erreur chargement de l'image : %s", SDL_GetError());
		return NULL;
	}
	sdlView->tab_texture[1] = SDL_CreateTextureFromSurface(sdlView->renderer, imageSurface);
	SDL_FreeSurface(imageSurface);
	imageSurface = IMG_Load("src/img/tilesheet.png");
	if (!imageSurface)
	{
		fprintf(stderr, "Erreur chargement de l'image : %s", SDL_GetError());
		return NULL;
	}
	sdlView->tab_texture[2] = SDL_CreateTextureFromSurface(sdlView->renderer, imageSurface);
	SDL_FreeSurface(imageSurface);

	ret->instanciation = sdlView;
	ret->functions.updateGrid = sdlUpdateView;
	return ret;
} // createSdlView

void afficherNombre(int n, int nb_chiffre, int x, int y, char *color, SdlView *sdlView)
{
	int ind, cpt = 0;
	if (strcmp(color, "red") == 0)
		ind = 3;
	else
		ind = 4;

	while (n > 0 && cpt < nb_chiffre)
	{
		int chiffre = n % 10;
		SDL_Rect rect = {x + (nb_chiffre - 1 - cpt) * TAILLE_CEL * SCALE, y, TAILLE_CEL * SCALE, TAILLE_CEL * SCALE};
		SDL_Rect rect_src = {chiffre * TAILLE_CEL, ind * TAILLE_CEL, TAILLE_CEL, TAILLE_CEL};
		SDL_RenderCopy(sdlView->renderer, sdlView->tab_texture[2], &rect_src, &rect);
		n /= 10;
		cpt++;
	}

	for (cpt; cpt < nb_chiffre; cpt++)
	{
		SDL_Rect rect = {x + (nb_chiffre - 1 - cpt) * TAILLE_CEL * SCALE, y, TAILLE_CEL * SCALE, TAILLE_CEL * SCALE};
		SDL_Rect rect_src = {0, ind * TAILLE_CEL, TAILLE_CEL, TAILLE_CEL};
		SDL_RenderCopy(sdlView->renderer, sdlView->tab_texture[2], &rect_src, &rect);
	}
}

void sdlUpdateView(View *view, GameState *game)
{
	SdlView *sdlView = (SdlView *)(view->instanciation);

	// Effacez le rendu précédent
	SDL_RenderClear(sdlView->renderer);

	// afficher le background
	SDL_Rect rect = {0, 0, 256 * SCALE, 240 * SCALE};
	SDL_RenderCopy(sdlView->renderer, sdlView->tab_texture[0], NULL, &rect);

	// afficher les stats
	SDL_Rect rect_src = {(level % 10) * 24, 0, 24, 104};
	SDL_Rect rect_dst = {24 * SCALE, 93 * SCALE, 24 * SCALE, 104 * SCALE};
	SDL_RenderCopy(sdlView->renderer, sdlView->tab_texture[1], &rect_src, &rect_dst);

	// afficher le plateau de jeu
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (game->map[i * WIDTH + j].a)
			{
				SDL_Rect rect_src = {TAILLE_CEL * (level % 10), game->map[i * WIDTH + j].c * TAILLE_CEL, TAILLE_CEL, TAILLE_CEL};
				SDL_Rect rect_dst = {j * TAILLE_CEL * SCALE + (96 * SCALE), i * TAILLE_CEL * SCALE + (48 * SCALE), TAILLE_CEL * SCALE, TAILLE_CEL * SCALE};
				SDL_RenderCopy(sdlView->renderer, sdlView->tab_texture[2], &rect_src, &rect_dst);
			}
		}
	}

	// afficher la nextBox
	for (int i = 0; i < 4; i++)
	{
		switch (game->nextBox.type)
		{
		case 6:
			rect.x = game->nextBox.b[i].x * TAILLE_CEL * SCALE + (192 * SCALE);
			rect.y = game->nextBox.b[i].y * TAILLE_CEL * SCALE + (116 * SCALE);
			break;
		case 3:
			rect.x = game->nextBox.b[i].x * TAILLE_CEL * SCALE + (200 * SCALE);
			rect.y = game->nextBox.b[i].y * TAILLE_CEL * SCALE + (120 * SCALE);
			break;

		case 2:
		case 4:
			rect.x = game->nextBox.b[i].x * TAILLE_CEL * SCALE + (196 * SCALE);
			rect.y = game->nextBox.b[i].y * TAILLE_CEL * SCALE + (120 * SCALE);
			break;

		default:
			rect.x = game->nextBox.b[i].x * TAILLE_CEL * SCALE + (196 * SCALE);
			rect.y = game->nextBox.b[i].y * TAILLE_CEL * SCALE + (112 * SCALE);
			break;
		}
		rect.w = TAILLE_CEL * SCALE;
		rect.h = TAILLE_CEL * SCALE;

		SDL_Rect rect_src = {(level % 10) * TAILLE_CEL, game->nextBox.c * TAILLE_CEL, TAILLE_CEL, TAILLE_CEL};
		SDL_RenderCopy(sdlView->renderer, sdlView->tab_texture[2], &rect_src, &rect);
	}

	// afficher top
	afficherNombre(highScore, 6, 192 * SCALE, 40 * SCALE, "white", sdlView);

	// afficher score
	afficherNombre(score, 6, 192 * SCALE, 64 * SCALE, "white", sdlView);

	// afficher lines
	afficherNombre(nbLignes, 3, 152 * SCALE, 24 * SCALE, "white", sdlView);

	// afficher lines
	afficherNombre(level, 2, 208 * SCALE, 168 * SCALE, "white", sdlView);

	// afficher stats nb
	for (int i = 0; i < 7; i++)
	{
		afficherNombre(stats[i], 3, 48 * SCALE, (96 + i * 16) * SCALE, "red", sdlView);
	}

	// Mettez à jour l'affichage
	SDL_RenderPresent(sdlView->renderer);
}

void destroySdlView(View *view)
{
	SdlView *sdlView = (SdlView *)(view->instanciation);

	for (int i = 0; i < sdlView->numImages; ++i)
	{
		SDL_DestroyTexture(sdlView->tab_texture[i]);
	}
	SDL_DestroyRenderer(sdlView->renderer);
	SDL_DestroyWindow(sdlView->window);

	free(sdlView->tab_texture);

	free(sdlView);
	free(view);

	SDL_Quit();
}