#include <stdio.h>
#include <stdlib.h>

#include "ncursesView.h"
#include "modele/modele.h"

View *createNcursesView()
{
    NcursesView *ncursesView = (NcursesView *)malloc(sizeof(NcursesView));
    if (!ncursesView)
    {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    initscr();

    ncursesView->board = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);
    ncursesView->level = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);
    ncursesView->next = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);
    ncursesView->score = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);
    ncursesView->stats = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);
    box(ncursesView->board, ACS_VLINE, ACS_HLINE);
    box(ncursesView->level, ACS_VLINE, ACS_HLINE);
    box(ncursesView->next, ACS_VLINE, ACS_HLINE);
    box(ncursesView->score, ACS_VLINE, ACS_HLINE);
    box(ncursesView->stats, ACS_VLINE, ACS_HLINE);
}

void updateNcursesView(View *view, GameState *gameState)
{
}

void destroyNcursesView(View *view)
{
    NcursesView *ncursesView = (NcursesView *)view->instanciation;

    wborder(ncursesView->board, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->board);
    delwin(ncursesView->board);

    wborder(ncursesView->level, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->level);
    delwin(ncursesView->level);

    wborder(ncursesView->next, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->next);
    delwin(ncursesView->next);

    wborder(ncursesView->score, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->score);
    delwin(ncursesView->score);

    wborder(ncursesView->stats, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->stats);
    delwin(ncursesView->stats);

    free(ncursesView);
}

void ncursesEvent(GameState *game, int *run)
{
    int ch;
    while ((ch = getch()) != KEY_p)
    {
        switch (ch)
        {
        case KEY_DOWN:
            moveDown(game->map, &(game->p));
            if (!verifCollision(game->map, game->p))
            {
                moveUp(game->map, &(game->p));
                insertPiece(game);
                int cleared = piecePosee(game->map, game->p);
                if (cleared != 0)
                {
                    nbLignes += cleared;
                    updateLevel();
                    ajouteScore(cleared);
                }
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

        case KEY_RIGHT:
            moveRight(game->map, &(game->p));
            if (!verifCollision(game->map, game->p))
                moveLeft(game->map, &(game->p));
            break;

        case KEY_LEFT:
            moveLeft(game->map, &(game->p));
            if (!verifCollision(game->map, game->p))
                moveRight(game->map, &(game->p));
            break;

        case KEY_q:
            rotateLeft(game->map, &(game->p));
            if (!verifCollision(game->map, game->p))
                rotateRight(game->map, &(game->p));
            break;

        case KEY_d:
            rotateRight(game->map, &(game->p));
            if (!verifCollision(game->map, game->p))
                rotateLeft(game->map, &(game->p));
            break;

        case KEY_p:
            *run = 0;
            break;

        default:
            break;
        }
    }
}