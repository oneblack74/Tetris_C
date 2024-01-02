#include <stdlib.h>
#include <time.h>

#include "modele/modele.h"
#include "view/view.h"

int main(int argc, char **argv)
{
	srand(time(NULL));

	GameState *game = (GameState *)malloc(sizeof(GameState));

	initModele(game);

	View SDL = sdlView_init(256 * SCALE, 240 * SCALE);

	gameLoop(SDL, game);

	return EXIT_SUCCESS;
} // main