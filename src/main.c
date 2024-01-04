/**
 * @file main.c
 * @author Hurez Matteo and Brissy Axel
 * @brief main du tetris
 * @version 1.0
 * @date 2024−01−04
 *
 * @copyright Copyright(c) 2024
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "modele/modele.h"
#include "view/view.h"

/**
 * @brief main du tetris
 */
int main(int argc, char **argv)
{
	argc--;
	argv++;

	if (argc != 0)
	{
		srand(time(NULL));
		char *type = argv[0];

		argc--;
		argv++;

		char *end;

		if (argc != 0)
		{
			int tmp = (int)strtol(argv[0], &end, 10);
			if (argv[0] != 0 && end[0] == 0)
				if (tmp >= 0 && tmp <= 19)
					level = tmp;
				else
					printf("Pour le 2eme paramètre, choisir entre 0 et 19 pour le niveau de départ. Le jeu se lance au level 0 par défaut.\n");
			else
				printf("Pour le 2eme paramètre, choisir entre 0 et 19 pour le niveau de départ. Le jeu se lance au level 0 par défaut.\n");

			argc--;
			argv++;
			if (argc != 0)
			{
				int tmp = (int)strtol(argv[0], &end, 10);
				if (argv[0] != 0 && end[0] == 0)
					if (tmp >= 0 && tmp <= 10)
						SCALE = tmp;
					else
						printf("Pour le 3eme paramètre, choisir entre 0 et 10 pour la taille de la fenêtre sdl. Le jeu se lance à une taille de 3 par défaut.\n");
				else
					printf("Pour le 3eme paramètre, choisir entre 0 et 10 pour la taille de la fenêtre sdl. Le jeu se lance à une taille de 3 par défaut.\n");
			}
		}

		GameState *game = (GameState *)malloc(sizeof(GameState));
		View view;
		if (strcmp(type, "sdl") == 0)
			view = sdlView_init(256 * SCALE, 240 * SCALE);
		else if (strcmp(type, "ncurses") == 0)
			view = ncursesView_init();
		else
		{
			printf("Il faut choisir entre sdl et ncurses.\n");
			return EXIT_FAILURE;
		}

		initModele(game);

		gameLoop(&view, game);

		return EXIT_SUCCESS;
	}
	printf("Il faut choisir entre sdl et ncurses.\n");
	return EXIT_SUCCESS;

} // main