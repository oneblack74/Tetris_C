#include <stdio.h>
#include <stdlib.h>

#include "ncursesView.h"
#include "modele/modele.h"

NcursesView *createNcursesView()
{
    NcursesView *ncursesView = (NcursesView *)malloc(sizeof(NcursesView));
    if (!ncursesView)
    {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    initscr();
    cbreak();
    noecho();
    timeout(0);
    keypad(stdscr, TRUE);
    curs_set(0);

    // board
    ncursesView->board = subwin(stdscr, 22, 22, 0, 15);

    // lines and level
    ncursesView->level = subwin(stdscr, 7, 7, 13, 38);
    mvwaddch(ncursesView->level, 1, 1, 'L');
    mvwaddch(ncursesView->level, 1, 2, 'I');
    mvwaddch(ncursesView->level, 1, 3, 'N');
    mvwaddch(ncursesView->level, 1, 4, 'E');
    mvwaddch(ncursesView->level, 1, 5, 'S');

    mvwaddch(ncursesView->level, 4, 1, 'L');
    mvwaddch(ncursesView->level, 4, 2, 'E');
    mvwaddch(ncursesView->level, 4, 3, 'V');
    mvwaddch(ncursesView->level, 4, 4, 'E');
    mvwaddch(ncursesView->level, 4, 5, 'L');

    // next box
    ncursesView->next = subwin(stdscr, 5, 10, 8, 38);
    mvwaddch(ncursesView->next, 1, 3, 'N');
    mvwaddch(ncursesView->next, 1, 4, 'E');
    mvwaddch(ncursesView->next, 1, 5, 'X');
    mvwaddch(ncursesView->next, 1, 6, 'T');

    // highscore and score
    ncursesView->score = subwin(stdscr, 7, 8, 0, 38);
    mvwaddch(ncursesView->score, 1, 1, 'T');
    mvwaddch(ncursesView->score, 1, 2, 'O');
    mvwaddch(ncursesView->score, 1, 3, 'P');

    mvwaddch(ncursesView->score, 4, 1, 'S');
    mvwaddch(ncursesView->score, 4, 2, 'C');
    mvwaddch(ncursesView->score, 4, 3, 'O');
    mvwaddch(ncursesView->score, 4, 4, 'R');
    mvwaddch(ncursesView->score, 4, 5, 'E');

    // piece distribution
    ncursesView->stats = subwin(stdscr, 23, 14, 0, 0);
    mvwaddch(ncursesView->stats, 1, 2, 'S');
    mvwaddch(ncursesView->stats, 1, 3, 'T');
    mvwaddch(ncursesView->stats, 1, 4, 'A');
    mvwaddch(ncursesView->stats, 1, 5, 'T');
    mvwaddch(ncursesView->stats, 1, 6, 'I');
    mvwaddch(ncursesView->stats, 1, 7, 'S');
    mvwaddch(ncursesView->stats, 1, 8, 'T');
    mvwaddch(ncursesView->stats, 1, 9, 'I');
    mvwaddch(ncursesView->stats, 1, 10, 'C');
    mvwaddch(ncursesView->stats, 1, 11, 'S');

    // T
    mvwaddch(ncursesView->stats, 3, 2, '[');
    mvwaddch(ncursesView->stats, 3, 3, ']');
    mvwaddch(ncursesView->stats, 3, 4, '[');
    mvwaddch(ncursesView->stats, 3, 5, ']');
    mvwaddch(ncursesView->stats, 3, 6, '[');
    mvwaddch(ncursesView->stats, 3, 7, ']');
    mvwaddch(ncursesView->stats, 4, 4, '[');
    mvwaddch(ncursesView->stats, 4, 5, ']');

    // J
    mvwaddch(ncursesView->stats, 6, 2, '[');
    mvwaddch(ncursesView->stats, 6, 3, ']');
    mvwaddch(ncursesView->stats, 6, 4, '[');
    mvwaddch(ncursesView->stats, 6, 5, ']');
    mvwaddch(ncursesView->stats, 6, 6, '[');
    mvwaddch(ncursesView->stats, 6, 7, ']');
    mvwaddch(ncursesView->stats, 7, 6, '[');
    mvwaddch(ncursesView->stats, 7, 7, ']');

    // Z
    mvwaddch(ncursesView->stats, 9, 2, '[');
    mvwaddch(ncursesView->stats, 9, 3, ']');
    mvwaddch(ncursesView->stats, 9, 4, '[');
    mvwaddch(ncursesView->stats, 9, 5, ']');
    mvwaddch(ncursesView->stats, 10, 4, '[');
    mvwaddch(ncursesView->stats, 10, 5, ']');
    mvwaddch(ncursesView->stats, 10, 6, '[');
    mvwaddch(ncursesView->stats, 10, 7, ']');

    // O
    mvwaddch(ncursesView->stats, 12, 3, '[');
    mvwaddch(ncursesView->stats, 12, 4, ']');
    mvwaddch(ncursesView->stats, 12, 5, '[');
    mvwaddch(ncursesView->stats, 12, 6, ']');
    mvwaddch(ncursesView->stats, 13, 3, '[');
    mvwaddch(ncursesView->stats, 13, 4, ']');
    mvwaddch(ncursesView->stats, 13, 5, '[');
    mvwaddch(ncursesView->stats, 13, 6, ']');

    // S
    mvwaddch(ncursesView->stats, 15, 4, '[');
    mvwaddch(ncursesView->stats, 15, 5, ']');
    mvwaddch(ncursesView->stats, 15, 6, '[');
    mvwaddch(ncursesView->stats, 15, 7, ']');
    mvwaddch(ncursesView->stats, 16, 2, '[');
    mvwaddch(ncursesView->stats, 16, 3, ']');
    mvwaddch(ncursesView->stats, 16, 4, '[');
    mvwaddch(ncursesView->stats, 16, 5, ']');

    // L
    mvwaddch(ncursesView->stats, 18, 2, '[');
    mvwaddch(ncursesView->stats, 18, 3, ']');
    mvwaddch(ncursesView->stats, 18, 4, '[');
    mvwaddch(ncursesView->stats, 18, 5, ']');
    mvwaddch(ncursesView->stats, 18, 6, '[');
    mvwaddch(ncursesView->stats, 18, 7, ']');
    mvwaddch(ncursesView->stats, 19, 2, '[');
    mvwaddch(ncursesView->stats, 19, 3, ']');

    // I
    mvwaddch(ncursesView->stats, 21, 1, '[');
    mvwaddch(ncursesView->stats, 21, 2, ']');
    mvwaddch(ncursesView->stats, 21, 3, '[');
    mvwaddch(ncursesView->stats, 21, 4, ']');
    mvwaddch(ncursesView->stats, 21, 5, '[');
    mvwaddch(ncursesView->stats, 21, 6, ']');
    mvwaddch(ncursesView->stats, 21, 7, '[');
    mvwaddch(ncursesView->stats, 21, 8, ']');

    box(ncursesView->board, ACS_VLINE, ACS_HLINE);
    box(ncursesView->level, ACS_VLINE, ACS_HLINE);
    box(ncursesView->next, ACS_VLINE, ACS_HLINE);
    box(ncursesView->score, ACS_VLINE, ACS_HLINE);
    box(ncursesView->stats, ACS_VLINE, ACS_HLINE);

    return ncursesView;
}

void updateNcursesView(View *view, GameState *game)
{
    NcursesView *ncursesView = (NcursesView *)view->instanciation;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (game->map[i * WIDTH + j].a)
            {
                mvwaddch(ncursesView->board, i + 1, (j * 2) + 1, '[');
                mvwaddch(ncursesView->board, i + 1, (j * 2) + 2, ']');
            }
            else
            {
                mvwaddch(ncursesView->board, i + 1, (j * 2) + 1, ' ');
                mvwaddch(ncursesView->board, i + 1, (j * 2) + 2, ' ');
            }
        }
    }

    int div = 1000;
    for (int i = 1; i < 4; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->level, 2, i, ((nbLignes / div) % 10) + '0');
    }

    div = 100;
    for (int i = 1; i < 3; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->level, 5, i, ((level / div) % 10) + '0');
    }

    div = 1000000;
    for (int i = 1; i < 7; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->score, 2, i, ((highScore / div) % 10) + '0');
    }

    div = 1000000;
    for (int i = 1; i < 7; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->score, 5, i, ((score / div) % 10) + '0');
    }

    div = 1000;
    for (int i = 10; i < 13; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->stats, 3, i, ((stats[0] / div) % 10) + '0');
    }

    div = 1000;
    for (int i = 10; i < 13; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->stats, 6, i, ((stats[1] / div) % 10) + '0');
    }

    div = 1000;
    for (int i = 10; i < 13; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->stats, 9, i, ((stats[2] / div) % 10) + '0');
    }

    div = 1000;
    for (int i = 10; i < 13; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->stats, 12, i, ((stats[3] / div) % 10) + '0');
    }

    div = 1000;
    for (int i = 10; i < 13; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->stats, 15, i, ((stats[4] / div) % 10) + '0');
    }

    div = 1000;
    for (int i = 10; i < 13; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->stats, 18, i, ((stats[5] / div) % 10) + '0');
    }

    div = 1000;
    for (int i = 10; i < 13; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->stats, 21, i, ((stats[6] / div) % 10) + '0');
    }

    refresh();
    wrefresh(ncursesView->board);
    wrefresh(ncursesView->level);
    wrefresh(ncursesView->next);
    wrefresh(ncursesView->score);
    wrefresh(ncursesView->stats);
}

void destroyNcursesView(View *view)
{
    NcursesView *ncursesView = (NcursesView *)view->instanciation;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            mvwaddch(ncursesView->board, i + 1, (j * 2) + 1, ' ');
            mvwaddch(ncursesView->board, i + 1, (j * 2) + 2, ' ');
        }
    }
    wborder(ncursesView->board, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->board);
    delwin(ncursesView->board);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            mvwaddch(ncursesView->level, i + 1, j + 1, ' ');
        }
    }
    wborder(ncursesView->level, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->level);
    delwin(ncursesView->level);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            mvwaddch(ncursesView->next, i + 1, j + 1, ' ');
        }
    }
    wborder(ncursesView->next, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->next);
    delwin(ncursesView->next);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            mvwaddch(ncursesView->score, i + 1, j + 1, ' ');
        }
    }
    wborder(ncursesView->score, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->score);
    delwin(ncursesView->score);

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            mvwaddch(ncursesView->stats, i + 1, j + 1, ' ');
        }
    }
    wborder(ncursesView->stats, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->stats);
    delwin(ncursesView->stats);

    free(ncursesView);
    echo();
    curs_set(1);
}

void ncursesEvent(View *view, GameState *game)
{
    int ch;
    while ((ch = getch()) != ERR)
    {
        switch (ch)
        {
        case KEY_DOWN:
            moveDown(game);
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

        case 'q':
            rotateLeft(game->map, &(game->p));
            if (!verifCollision(game->map, game->p))
                rotateRight(game->map, &(game->p));
            break;

        case 'd':
            rotateRight(game->map, &(game->p));
            if (!verifCollision(game->map, game->p))
                rotateLeft(game->map, &(game->p));
            break;

        case 'p':
            game->run = 0;
            break;

        default:
            break;
        }
    }
}