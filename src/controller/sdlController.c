#include "controller.h"
#include "sdlController.h"

#include "view/sldView.h"

void sdlEvent(GameState *game, int *run)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            *run = 0;
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_DOWN:
                moveDown(game->map, &(game->p));
                if (!verifCollision(game->map, game->p))
                {
                    moveUp(game->map, &(game->p));
                    insertPiece(game);
                    int cleared = piecePosee(game->map, game->p);
                    nbLignes += cleared;
                    updateLevel();
                    ajouteScore(cleared);
                    changePiece(game);
                    if (!verifCollision(game->map, game->p))
                    {
                        *run = 0;
                        if (score > highScore)
                            updateHighScore("highscore.txt", score);
                        printf("Aww man you topped out rip D: Good game!\n");
                    }
                }
                break;

            case SDLK_RIGHT:
                moveRight(game->map, &(game->p));
                if (!verifCollision(game->map, game->p))
                    moveLeft(game->map, &(game->p));
                break;

            case SDLK_LEFT:
                moveLeft(game->map, &(game->p));
                if (!verifCollision(game->map, game->p))
                    moveRight(game->map, &(game->p));
                break;

            case SDLK_q:
                rotateLeft(game->map, &(game->p));
                if (!verifCollision(game->map, game->p))
                    rotateRight(game->map, &(game->p));
                break;

            case SDLK_d:
                rotateRight(game->map, &(game->p));
                if (!verifCollision(game->map, game->p))
                    rotateLeft(game->map, &(game->p));
                break;

            case SDLK_p:
                *run = 0;
                break;

            default:
                break;
            }
        }
    }
}