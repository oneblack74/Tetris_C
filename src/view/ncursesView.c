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

    ncursesView->board = newwin(22, 22, 0, 0);
    // ncursesView->level = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);
    // ncursesView->next = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);
    // ncursesView->score = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);
    // ncursesView->stats = subwin(stdscr, LINES - h / 2, COLS - w / 2, 0, 0);
    box(ncursesView->board, ACS_VLINE, ACS_HLINE);
    // box(ncursesView->level, ACS_VLINE, ACS_HLINE);
    // box(ncursesView->next, ACS_VLINE, ACS_HLINE);
    // box(ncursesView->score, ACS_VLINE, ACS_HLINE);
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