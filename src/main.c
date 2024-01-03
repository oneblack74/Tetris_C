#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "modele/modele.h"
#include "view/view.h"

int main(int argc, char **argv)
{
	argc--;
	argv++;

	if (argc == 1)
	{
		srand(time(NULL));
		View view;
		if (strcmp(argv[0], "sdl") == 0)
			view = sdlView_init(256 * SCALE, 240 * SCALE);
		else if (strcmp(argv[0], "ncurses") == 0)
			view = ncursesView_init();
		else
		{
			printf("Il faut choisir entre sdl et ncurses.\n");
			return EXIT_FAILURE;
		}
		GameState *game = (GameState *)malloc(sizeof(GameState));

		initModele(game);

		gameLoop(&view, game);

		return EXIT_SUCCESS;
	}
	printf("Il faut choisir entre sdl et ncurses.\n");
	return EXIT_SUCCESS;

} // main