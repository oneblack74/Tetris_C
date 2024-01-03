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
    ncursesView->board = subwin(stdscr, 22, 22, 0, 0);

    // lines and level
    ncursesView->level = subwin(stdscr, 7, 7, 8, 23);
    mvwaddch(ncursesView->level, 1, 1, 'L');
    mvwaddch(ncursesView->level, 1, 2, 'I');
    mvwaddch(ncursesView->level, 1, 3, 'N');
    mvwaddch(ncursesView->level, 1, 4, 'E');
    mvwaddch(ncursesView->level, 1, 5, 'S');

    int div = 1000;
    for (int i = 1; i < 4; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->level, 2, i, ((nbLignes / div) % 10) + '0');
    }

    mvwaddch(ncursesView->level, 4, 1, 'L');
    mvwaddch(ncursesView->level, 4, 2, 'E');
    mvwaddch(ncursesView->level, 4, 3, 'V');
    mvwaddch(ncursesView->level, 4, 4, 'E');
    mvwaddch(ncursesView->level, 4, 5, 'L');

    div = 100;
    for (int i = 1; i < 3; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->level, 5, i, ((level / div) % 10) + '0');
    }

    // next box
    // ncursesView->next = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);

    // highscore and score
    ncursesView->score = subwin(stdscr, 7, 8, 0, 23);
    mvwaddch(ncursesView->score, 1, 1, 'T');
    mvwaddch(ncursesView->score, 1, 2, 'O');
    mvwaddch(ncursesView->score, 1, 3, 'P');

    div = 1000000;
    for (int i = 1; i < 7; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->score, 2, i, ((highScore / div) % 10) + '0');
    }

    mvwaddch(ncursesView->score, 4, 1, 'S');
    mvwaddch(ncursesView->score, 4, 2, 'C');
    mvwaddch(ncursesView->score, 4, 3, 'O');
    mvwaddch(ncursesView->score, 4, 4, 'R');
    mvwaddch(ncursesView->score, 4, 5, 'E');

    div = 1000000;
    for (int i = 1; i < 7; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->score, 5, i, ((score / div) % 10) + '0');
    }

    // piece distribution
    // ncursesView->stats = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);

    box(ncursesView->board, ACS_VLINE, ACS_HLINE);
    box(ncursesView->level, ACS_VLINE, ACS_HLINE);
    // box(ncursesView->next, ACS_VLINE, ACS_HLINE);
    box(ncursesView->score, ACS_VLINE, ACS_HLINE);
    // box(ncursesView->stats, ACS_VLINE, ACS_HLINE);

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
    refresh();
    wrefresh(ncursesView->board);

    int div = 1000000;
    for (int i = 1; i < 7; i++)
    {
        div /= 10;
        mvwaddch(ncursesView->score, 5, i, ((score / div) % 10) + '0');
    }
    refresh();
    wrefresh(ncursesView->score);
}

void destroyWindow(WINDOW *window)
{
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
        for (int j = 0; j < 6; j++)
        {
            mvwaddch(ncursesView->board, i + 1, j + 1, ' ');
        }
    }
    wborder(ncursesView->level, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->level);
    delwin(ncursesView->level);

    /* wborder(ncursesView->next, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->next);
    delwin(ncursesView->next);

    wborder(ncursesView->score, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->score);
    delwin(ncursesView->score);

    wborder(ncursesView->stats, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(ncursesView->stats);
    delwin(ncursesView->stats); */

    free(ncursesView);
}

void ncursesEvent(View *view, GameState *game)
{
    int ch;
    while ((ch = getch()) != ERR)
    {
        switch (ch)
        {
        case KEY_DOWN:
            int ret = moveDown(game);
            if (ret >= 0)
            {
                if (ret == 4)
                    view->functions->play_sound(view, 1);
                else if (ret > 0)
                    view->functions->play_sound(view, 0);
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