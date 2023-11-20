#include <stdlib.h>
#include <time.h>

#include "modele/modele.h"

int main(int argc, char **argv)
{
	srand(time(NULL));

	GameState *game = (GameState *)malloc(sizeof(GameState));

	initModele(game);
	gameLoop(game);

	return EXIT_SUCCESS;
} // main