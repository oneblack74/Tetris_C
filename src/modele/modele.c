#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "modele.h"
#include "view/view.h"
#include "controller/controller.h"

const int WIDTH = 10;
const int HEIGHT = 20;
const int TAILLE_CEL = 8;
const int SCALE = 3;

int level = 19;
int score = 0;
int highScore = 0;
int nbLignes = 0;
int stats[7] = {0, 0, 0, 0, 0, 0, 0};

void initModele(GameState *game)
{
    initListePiece(game);
    initMap(game);

    game->p = game->listePiece[rand() % 7];
    game->nextBox = game->listePiece[rand() % 7];
    stats[game->p.type]++;
}

// initialise la liste qui contient les 7 pièces différentes
void initListePiece(GameState *game)
{
    game->listePiece = (Piece *)malloc(sizeof(Piece) * 7);

    Piece p;

    // T
    p.b[0] = (Block){0, 1};
    p.b[1] = (Block){1, 1};
    p.b[2] = (Block){2, 1};
    p.b[3] = (Block){1, 2};
    p.c = 0;
    p.type = 0;
    p.w = 3;
    p.h = 3;
    p.x = 4;
    p.y = -1;
    game->listePiece[0] = p;

    // J
    p.b[0] = (Block){0, 1};
    p.b[1] = (Block){1, 1};
    p.b[2] = (Block){2, 1};
    p.b[3] = (Block){2, 2};
    p.c = 2;
    p.type = 1;
    p.w = 3;
    p.h = 3;
    p.x = 4;
    p.y = -1;
    game->listePiece[1] = p;

    // Z
    p.b[0] = (Block){0, 0};
    p.b[1] = (Block){1, 0};
    p.b[2] = (Block){1, 1};
    p.b[3] = (Block){2, 1};
    p.c = 1;
    p.type = 2;
    p.w = 3;
    p.h = 2;
    p.x = 4;
    p.y = 0;
    game->listePiece[2] = p;

    // O
    p.b[0] = (Block){0, 0};
    p.b[1] = (Block){1, 0};
    p.b[2] = (Block){0, 1};
    p.b[3] = (Block){1, 1};
    p.c = 0;
    p.type = 3;
    p.w = 2;
    p.h = 2;
    p.x = 4;
    p.y = 0;
    game->listePiece[3] = p;

    // S
    p.b[0] = (Block){1, 0};
    p.b[1] = (Block){2, 0};
    p.b[2] = (Block){0, 1};
    p.b[3] = (Block){1, 1};
    p.c = 2;
    p.type = 4;
    p.w = 3;
    p.h = 2;
    p.x = 4;
    p.y = 0;
    game->listePiece[4] = p;

    // L
    p.b[0] = (Block){0, 1};
    p.b[1] = (Block){1, 1};
    p.b[2] = (Block){2, 1};
    p.b[3] = (Block){0, 2};
    p.c = 1;
    p.type = 5;
    p.w = 3;
    p.h = 3;
    p.x = 4;
    p.y = -1;
    game->listePiece[5] = p;

    // I
    p.b[0] = (Block){0, 1};
    p.b[1] = (Block){1, 1};
    p.b[2] = (Block){2, 1};
    p.b[3] = (Block){3, 1};
    p.c = 0;
    p.type = 6;
    p.w = 4;
    p.h = 3;
    p.x = 3;
    p.y = -1;
    game->listePiece[6] = p;
}

// initialise la map vide
void initMap(GameState *game)
{
    game->map = (Cel *)malloc(sizeof(Cel) * WIDTH * HEIGHT);
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            game->map[i * WIDTH + j].a = 0;
            game->map[i * WIDTH + j].c = 0;
        }
    }
}

// insère la pièce qui descend dans le tableau pour l'afficher (en texte)
void insertPiece(GameState *game)
{
    for (int i = 0; i < 4; i++)
    {
        Block b = game->p.b[i];
        int new_x = game->p.x + b.x;
        int new_y = game->p.y + b.y;
        if (0 <= new_x && new_x < WIDTH && 0 <= new_y && new_y < HEIGHT)
        {
            game->map[new_y * WIDTH + new_x].a = 1;
            game->map[new_y * WIDTH + new_x].c = game->p.c;
        }
    }
}

// retire la pièce du tableau pour la déplacer
void removePiece(GameState *game)
{
    for (int i = 0; i < 4; i++)
    {
        Block b = game->p.b[i];
        int new_x = game->p.x + b.x;
        int new_y = game->p.y + b.y;
        if (0 <= new_x && new_x < WIDTH && 0 <= new_y && new_y < HEIGHT)
        {
            game->map[new_y * WIDTH + new_x].a = 0;
        }
    }
}

// déplace la pièce vers le bas
void moveDown(Cel *map, Piece *p)
{
    p->y++;
}

// déplace la pièce vers le haut (pour gérer les collisions)
void moveUp(Cel *map, Piece *p)
{
    p->y--;
}

// déplace la pièce vers la droite
void moveRight(Cel *map, Piece *p)
{
    p->x++;
}

// déplace la pièce vers la gauche
void moveLeft(Cel *map, Piece *p)
{
    p->x--;
}

// fait tourner la pièce vers la droite
void rotateLeft(Cel *map, Piece *p)
{
    for (int i = 0; i < 4; i++)
    {
        int new_x = p->b[i].y % p->h;
        int new_y = (p->w - p->b[i].x - 1) + (p->b[i].y / p->h);
        p->b[i].x = new_x;
        p->b[i].y = new_y;
    }

    int tmp = p->h;
    p->h = p->w;
    p->w = tmp;

    p->x -= (p->w - p->h);
    p->y += (p->w - p->h);
}

// fait tourner la pièce vers la gauche
void rotateRight(Cel *map, Piece *p)
{
    for (int i = 0; i < 4; i++)
    {
        int new_x = (p->h - p->b[i].y - 1) % p->h;
        int new_y = p->b[i].x + (p->h - p->b[i].y - 1) / p->h;
        p->b[i].x = new_x;
        p->b[i].y = new_y;
    }

    int tmp = p->h;
    p->h = p->w;
    p->w = tmp;

    p->x -= (p->w - p->h);
    p->y += (p->w - p->h);
}

// supprime la ligne de coordonnée y
void deleteLine(Cel *map, int y)
{
    if (0 <= y && y < HEIGHT)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            map[y * WIDTH + i].a = 0;
        }
    }
}

void affiche(Cel *map, Piece nextBox)
{
    printf("+--------------------+\n");
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("|");
        for (int j = 0; j < WIDTH; j++)
        {
            if (map[i * WIDTH + j].a)
            {
                printf("[]");
            }
            else
            {
                printf("  ");
            }
        }
        printf("|\n");
    }
    printf("+--------------------+\n");
    printf("Score: %d - Lines: %d - Level: %d\n", score, nbLignes, level);
    printf("High score: %d\n", highScore);
    printf("NextBox: ");
    switch (nextBox.type)
    {
    case 0:
        printf("T");
        break;

    case 1:
        printf("J");
        break;

    case 2:
        printf("Z");
        break;

    case 3:
        printf("O");
        break;

    case 4:
        printf("S");
        break;

    case 5:
        printf("L");
        break;

    case 6:
        printf("I");
        break;

    default:
        break;
    }
    printf("\n");
}

// vérifie si la pièce est entrée en collision avec les bords de la map ainsi que les pièces déjà posées
int verifCollision(Cel *map, Piece p)
{
    for (int i = 0; i < 4; i++)
    {
        int x = p.x + p.b[i].x;
        int y = p.y + p.b[i].y;

        if (0 > x || x >= WIDTH)
            return 0;
        if (y >= HEIGHT)
            return 0;
        if (y >= 0 && map[y * WIDTH + x].a)
            return 0;
    }
    return 1;
}

int verifDeleteLine(Cel *map, int y)
{
    for (int i = 0; i < WIDTH; i++)
    {
        if (!map[y * WIDTH + i].a)
            return 0;
    }
    return 1;
}

void mapDown(Cel *map, int y, int cpt)
{
    for (int i = y; i >= cpt; i--)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            map[i * WIDTH + j] = map[(i - cpt) * WIDTH + j];
        }
    }
    for (int i = 0; i < cpt; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            map[i * WIDTH + j].a = 0;
        }
    }
}

int getHighScore(char *file)
{
    FILE *f;
    f = fopen(file, "r");

    if (f == NULL) // pour être sûr mais à priori ça n'arrivera pas
    {
        printf("Impossible de lire le fichier.");
        exit(EXIT_FAILURE);
    }

    int high = 0;
    char c;

    while ((c = fgetc(f)) != EOF)
    {
        if ((c < '0') || (c > '9'))
        {
            continue;
        }
        else
        {
            high *= 10;
            high += c - '0';
        }
    }

    printf("\n");

    fclose(f);
    return high;
}

void updateHighScore(char *file, int high)
{
    FILE *f;
    f = fopen(file, "w");

    if (f == NULL) // une fois de plus, pour être sûr mais à priori ça n'arrivera pas
    {
        printf("Impossible de lire le fichier.");
        exit(EXIT_FAILURE);
    }

    int tmp = high;
    int nb = 0;
    while (tmp != 0)
    {
        tmp /= 10;
        nb++;
    }

    int j = nb;
    char *ch = (char *)malloc(sizeof(char) * nb + 1);
    ch[nb] = '\0';
    while (nb >= 0 && high > 0)
    {
        ch[--nb] = high % 10 + '0';
        high /= 10;
    }
    fwrite(ch, sizeof(char) * j, 1, f);
    free(ch);

    fclose(f);
}

void ajouteScore(int nb)
{
    switch (nb)
    {
    case 1:
        score += 40 * (level + 1);
        break;

    case 2:
        score += 100 * (level + 1);
        break;

    case 3:
        score += 300 * (level + 1);
        break;

    case 4:
        score += 1200 * (level + 1);
        break;

    default:
        break;
    }
}

// à modif selon le level start ultérieurement
void updateLevel()
{
    level = nbLignes / 10;
}

int piecePosee(Cel *map, Piece p)
{
    int cpt = 0, yMax = -1;
    for (int i = 0; i < 4; i++)
    {
        int y = p.y + p.b[i].y;
        if (verifDeleteLine(map, y))
        {
            cpt++;
            deleteLine(map, y);

            if (y > yMax)
                yMax = y;
        }
    }
    if (cpt)
        mapDown(map, yMax, cpt);
    return cpt;
}

void changePiece(GameState *game)
{
    game->p = game->nextBox;
    game->nextBox = game->listePiece[rand() % 7];

    stats[game->p.type]++;
}

unsigned long getSpeed()
{
    switch (level)
    {
    case 0:
        return 2400;
        break;
    case 1:
        return 2150;
        break;
    case 2:
        return 1900;
        break;
    case 3:
        return 1650;
        break;
    case 4:
        return 1400;
        break;
    case 5:
        return 1150;
        break;
    case 6:
        return 900;
        break;
    case 7:
        return 650;
        break;
    case 8:
        return 400;
        break;
    case 9:
        return 300;
        break;
    case 10:
    case 11:
    case 12:
        return 250;
        break;
    case 13:
    case 14:
    case 15:
        return 200;
        break;
    case 16:
    case 17:
    case 18:
        return 150;
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
        return 100;
        break;

    default:
        break;
    }
    return 50;
}

void gameLoop(GameState *game)
{
    View *view = createView(SDL_VIEW);

    highScore = getHighScore("highscore.txt");
    int cleared;
    int run = 1;
    int ch;
    unsigned long speed = getSpeed(); // en milliseconde

    clock_t clock_end = clock();
    clock_t clock_begin = clock_end;

    insertPiece(game);
    updateView(SDL_VIEW, view, game);
    removePiece(game);

    while (run)
    {
        removePiece(game);
        if (((clock_end - clock_begin) * 1000 / CLOCKS_PER_SEC) >= speed)
        {
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
                    speed = getSpeed();
                }
                changePiece(game);
                if (!verifCollision(game->map, game->p))
                {
                    run = 0;
                    if (score > highScore)
                        updateHighScore("highscore.txt", score);
                    printf("Aww man you topped out rip D: Good game!\n");
                }
            }
            else
                clock_begin = clock_end;
        }
        else
        {
            clock_end = clock();
        }

        event(SDL_CONTROLLER, game, &run);

        insertPiece(game);
        updateView(SDL_VIEW, view, game);
    }

    destroyView(SDL_VIEW, view);

    free(game->map);
    free(game->listePiece);
    free(game);
}