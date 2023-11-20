#include <stdio.h>
#include <stdlib.h>

#include "sldView.h"
#include "modele/modele.h"
#include <SDL2/SDL_image.h>

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

	sdlView->numImages = 51;

	// Allouez de l'espace pour le tableau de textures
	sdlView->imageTexture = (SDL_Texture **)malloc(sdlView->numImages * sizeof(SDL_Texture *));
	if (!sdlView->imageTexture)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 3; j++)
		{
			char imagePath[30];
			sprintf(imagePath, "src/img/color_%d%d.png", i, j);

			SDL_Surface *imageSurface = IMG_Load(imagePath);
			if (!imageSurface)
			{
				fprintf(stderr, "Erreur chargement de l'image : %s", SDL_GetError());
				return NULL;
			}

			sdlView->imageTexture[i * 3 + j] = SDL_CreateTextureFromSurface(sdlView->renderer, imageSurface);
			SDL_FreeSurface(imageSurface);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		char imagePath[30];
		sprintf(imagePath, "src/img/red_%d.png", i);

		SDL_Surface *imageSurface = IMG_Load(imagePath);
		if (!imageSurface)
		{
			fprintf(stderr, "Erreur chargement de l'image : %s", SDL_GetError());
			return NULL;
		}

		sdlView->imageTexture[30 + i] = SDL_CreateTextureFromSurface(sdlView->renderer, imageSurface);
		SDL_FreeSurface(imageSurface);

		sprintf(imagePath, "src/img/white_%d.png", i);

		imageSurface = IMG_Load(imagePath);
		if (!imageSurface)
		{
			fprintf(stderr, "Erreur chargement de l'image : %s", SDL_GetError());
			return NULL;
		}

		sdlView->imageTexture[40 + i] = SDL_CreateTextureFromSurface(sdlView->renderer, imageSurface);
		SDL_FreeSurface(imageSurface);
	}

	SDL_Surface *imageSurface = IMG_Load("src/img/background.png");
	if (!imageSurface)
	{
		fprintf(stderr, "Erreur chargement de l'image : %s", SDL_GetError());
		return NULL;
	}

	sdlView->imageTexture[50] = SDL_CreateTextureFromSurface(sdlView->renderer, imageSurface);
	SDL_FreeSurface(imageSurface);

	for (int i = 0; i < sdlView->numImages; i++)
	{
		if (!sdlView->imageTexture[i])
		{
			fprintf(stderr, "Erreur création de la texture : %s", SDL_GetError());
			return NULL;
		}
	}

	ret->instanciation = sdlView;
	ret->functions.updateGrid = sdlUpdateView;
	return ret;
} // createSdlView

void afficherNombre(int n, int nb_chiffre, int x, int y, char *color, SdlView *sdlView)
{
	int ind, cpt = 0;
	if (strcmp(color, "red") == 0)
		ind = 30;
	else
		ind = 40;

	while (n > 0 && cpt < nb_chiffre)
	{
		int chiffre = n % 10;
		SDL_Rect rect = {x + (nb_chiffre - 1 - cpt) * TAILLE_CEL * SCALE, y, TAILLE_CEL * SCALE, TAILLE_CEL * SCALE};
		SDL_RenderCopy(sdlView->renderer, sdlView->imageTexture[ind + chiffre], NULL, &rect);
		n /= 10;
		cpt++;
	}

	for (cpt; cpt < nb_chiffre; cpt++)
	{
		SDL_Rect rect = {x + (nb_chiffre - 1 - cpt) * TAILLE_CEL * SCALE, y, TAILLE_CEL * SCALE, TAILLE_CEL * SCALE};
		SDL_RenderCopy(sdlView->renderer, sdlView->imageTexture[ind], NULL, &rect);
	}
}

void sdlUpdateView(View *view, GameState *game)
{
	SdlView *sdlView = (SdlView *)(view->instanciation);

	// Effacez le rendu précédent
	SDL_RenderClear(sdlView->renderer);

	// afficher le background
	SDL_Rect rect = {0, 0, 256 * SCALE, 240 * SCALE};
	SDL_RenderCopy(sdlView->renderer, sdlView->imageTexture[50], NULL, &rect);

	// afficher le plateau de jeu
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (game->map[i * WIDTH + j].a)
			{
				SDL_Rect rect = {j * TAILLE_CEL * SCALE + (96 * SCALE), i * TAILLE_CEL * SCALE + (48 * SCALE), (TAILLE_CEL - 1) * SCALE, (TAILLE_CEL - 1) * SCALE};
				SDL_RenderCopy(sdlView->renderer, sdlView->imageTexture[game->map[i * WIDTH + j].c], NULL, &rect);
			}
		}
	}

	// afficher la nextBox
	for (int i = 0; i < 4; i++)
	{
		switch (game->nextBox.type)
		{
		case 6:
			rect.x = game->nextBox.b[i].x * TAILLE_CEL * SCALE + (168 * SCALE);
			rect.y = game->nextBox.b[i].y * TAILLE_CEL * SCALE + (124 * SCALE);
			rect.w = (TAILLE_CEL - 1) * SCALE;
			rect.h = (TAILLE_CEL - 1) * SCALE;
			break;
		case 3:
			rect.x = game->nextBox.b[i].x * TAILLE_CEL * SCALE + (168 * SCALE);
			rect.y = game->nextBox.b[i].y * TAILLE_CEL * SCALE + (120 * SCALE);
			rect.w = (TAILLE_CEL - 1) * SCALE;
			rect.h = (TAILLE_CEL - 1) * SCALE;
			break;

		default:
			rect.x = game->nextBox.b[i].x * TAILLE_CEL * SCALE + (164 * SCALE);
			rect.y = game->nextBox.b[i].y * TAILLE_CEL * SCALE + (120 * SCALE);
			rect.w = (TAILLE_CEL - 1) * SCALE;
			rect.h = (TAILLE_CEL - 1) * SCALE;
			break;
		}

		SDL_RenderCopy(sdlView->renderer, sdlView->imageTexture[level % 10 + game->nextBox.c], NULL, &rect);
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
		SDL_DestroyTexture(sdlView->imageTexture[i]);
	}
	SDL_DestroyRenderer(sdlView->renderer);
	SDL_DestroyWindow(sdlView->window);

	free(sdlView->imageTexture);

	free(sdlView);
	free(view);

	SDL_Quit();
}