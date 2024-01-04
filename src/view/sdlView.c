/**
 * @file sdlView.c
 * @author Hurez Matteo and Brissy Axel
 * @brief vue sdl
 * @version 1.0
 * @date 2024−01−04
 *
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>

#include "sdlView.h"
#include "modele/modele.h"

/**
 * @brief permet de créer la structure sdlView et initialiser sdl
 *
 * @param w largeur de la fenetre
 * @param h hauteur de la fenetre
 * @return struct sdlView
 */
SdlView *createSdlView(unsigned w, unsigned h)
{
	SdlView *sdlView = (SdlView *)malloc(sizeof(SdlView));
	if (!sdlView)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	/* Initialise SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Erreur lors de l'initialisation de la SDL : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		printf("SDL_mixer initialisation failed: %s\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_CreateWindowAndRenderer(w, h, SDL_INIT_VIDEO, &sdlView->window, &sdlView->renderer);
	if (!sdlView->window || !sdlView->renderer)
	{
		fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	sdlView->numSounds = 9;
	sdlView->numImages = 3;

	// Allouer de l'espace pour le tableau des sons
	sdlView->tab_sounds = (Mix_Chunk **)malloc(sizeof(Mix_Chunk *) * sdlView->numSounds);
	if (!sdlView->tab_sounds)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	sdlView->tab_sounds[0] = Mix_LoadWAV("src/sound/Clear_1_to_3_Lines.wav");
	sdlView->tab_sounds[1] = Mix_LoadWAV("src/sound/Clear_Tetris.wav");
	sdlView->tab_sounds[2] = Mix_LoadWAV("src/sound/Move_Piece.wav");
	sdlView->tab_sounds[3] = Mix_LoadWAV("src/sound/MoveMenu.wav");
	sdlView->tab_sounds[4] = Mix_LoadWAV("src/sound/Piece_Pose.wav");
	sdlView->tab_sounds[5] = Mix_LoadWAV("src/sound/Rotate_Piece.wav");
	sdlView->tab_sounds[6] = Mix_LoadWAV("src/sound/Top_Out_End.wav");
	sdlView->tab_sounds[7] = Mix_LoadWAV("src/sound/Transition_Level.wav");
	sdlView->tab_sounds[8] = Mix_LoadWAV("src/sound/Valide_In_Menu.wav");

	for (int i = 0; i < sdlView->numSounds; i++)
	{
		if (sdlView->tab_sounds[i] == NULL)
		{
			printf("Failed to load sound number %d: %s\n", i, Mix_GetError());
			exit(EXIT_FAILURE);
		}
	}

	// Allouer de l'espace pour le tableau de textures
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

	return sdlView;
}

/**
 * @brief permet d'afficher un nombre sur la fenêtre avec les images
 *
 * @param n le nombre à afficher
 * @param nb_chiffre le nombre de chiffre max à afficher
 * @param x coordonnée x de la où on place le nombre
 * @param y coordonnée y de la où on place le nombre
 * @param color la couleur du nombre (rouge ou blanc)
 * @param sdlView la structure sdlView
 */
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

/**
 * @brief permet de mettre à jour la fenêtre et le rendu
 *
 * @param view la structure view
 * @param game la gamestate du jeu
 */
void sdlUpdateView(View *view, GameState *game)
{
	SdlView *sdlView = (SdlView *)view->instanciation;
	// Effacer le rendu précédent
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

	// Mettre à jour l'affichage
	SDL_RenderPresent(sdlView->renderer);
}

/**
 * @brief permet de clear et quitter sdl
 *
 * @param view la structure view
 */
void destroySdlView(View *view)
{
	SdlView *sdlView = (SdlView *)view->instanciation;
	for (int i = 0; i < sdlView->numImages; ++i)
	{
		SDL_DestroyTexture(sdlView->tab_texture[i]);
	}
	for (int i = 0; i < sdlView->numSounds; ++i)
	{
		Mix_FreeChunk(sdlView->tab_sounds[i]);
	}

	Mix_CloseAudio();
	SDL_DestroyRenderer(sdlView->renderer);
	SDL_DestroyWindow(sdlView->window);

	free(sdlView->tab_texture);
	free(sdlView->tab_sounds);

	free(sdlView);
	free(view);

	SDL_Quit();
}

/**
 * @brief permet de jouer un son
 *
 * @param view la structure view
 * @param ind indice du son dans le tableau à jouer
 */
void play_sound(View *view, int ind)
{
	SdlView *sdlView = (SdlView *)view->instanciation;

	Mix_PlayChannel(-1, sdlView->tab_sounds[ind], 0);
}

/**
 * @brief permet de gérer les évènements de sdl
 *
 * @param view la structure view
 * @param game la gamestate du jeu
 */
void sdlEvent(View *view, GameState *game)
{
	SdlView *sdlView = (SdlView *)view->instanciation;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			game->run = 0;
		}
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_DOWN:
			{
				int ret = moveDown(game);
				if (view->functions->play_sound != NULL && ret >= 0)
				{
					if (ret == 4)
						view->functions->play_sound(view, 1);
					else if (ret > 0)
						view->functions->play_sound(view, 0);
				}
				break;
			}

			case SDLK_RIGHT:
				moveRight(game->map, &(game->p));
				if (!verifCollision(game->map, game->p))
					moveLeft(game->map, &(game->p));
				else if (view->functions->play_sound != NULL)
					view->functions->play_sound(view, 2);
				break;

			case SDLK_LEFT:
				moveLeft(game->map, &(game->p));
				if (!verifCollision(game->map, game->p))
					moveRight(game->map, &(game->p));
				else if (view->functions->play_sound != NULL)
					view->functions->play_sound(view, 2);
				break;

			case SDLK_q:
				rotateLeft(game->map, &(game->p));
				if (!verifCollision(game->map, game->p))
					rotateRight(game->map, &(game->p));
				else if (view->functions->play_sound != NULL)
					view->functions->play_sound(view, 5);
				break;

			case SDLK_d:
				rotateRight(game->map, &(game->p));
				if (!verifCollision(game->map, game->p))
					rotateLeft(game->map, &(game->p));
				else if (view->functions->play_sound != NULL)
					view->functions->play_sound(view, 5);
				break;

			case SDLK_p:
				game->run = 0;
				break;

			default:
				break;
			}
		}
	}
}