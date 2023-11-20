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
const int PIECE_START_X = 3;
const int PIECE_START_Y = -2;
const int TAILLE_CEL = 8;
const int SCALE = 3;

int level = 0;
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
}

// initialise la liste qui contient les 7 pièces différentes
void initListePiece(GameState *game)
{
    game->listePiece = (Piece *)malloc(sizeof(Piece) * 7);

    Piece p;
    // Block --> les coordonnées des 4 cellules de chaque pièce
    Block b1;
    Block b2;
    Block b3;
    Block b4;

    // T
    b1.x = PIECE_START_X + 1;
    b1.y = PIECE_START_Y + 2;
    b2.x = PIECE_START_X + 2;
    b2.y = PIECE_START_Y + 2;
    b3.x = PIECE_START_X + 3;
    b3.y = PIECE_START_Y + 2;
    b4.x = PIECE_START_X + 2;
    b4.y = PIECE_START_Y + 3;
    p.b[0] = b1;
    p.b[1] = b2;
    p.b[2] = b3;
    p.b[3] = b4;
    p.c = 0;
    p.ind = 0;
    p.type = 0;
    game->listePiece[0] = p;

    // J
    b1.x = PIECE_START_X + 1;
    b1.y = PIECE_START_Y + 2;
    b2.x = PIECE_START_X + 2;
    b2.y = PIECE_START_Y + 2;
    b3.x = PIECE_START_X + 3;
    b3.y = PIECE_START_Y + 2;
    b4.x = PIECE_START_X + 3;
    b4.y = PIECE_START_Y + 3;
    p.b[0] = b1;
    p.b[1] = b2;
    p.b[2] = b3;
    p.b[3] = b4;
    p.c = 2;
    p.ind = 0;
    p.type = 1;
    game->listePiece[1] = p;

    // Z
    b1.x = PIECE_START_X + 3;
    b1.y = PIECE_START_Y + 3;
    b2.x = PIECE_START_X + 2;
    b2.y = PIECE_START_Y + 3;
    b3.x = PIECE_START_X + 2;
    b3.y = PIECE_START_Y + 2;
    b4.x = PIECE_START_X + 1;
    b4.y = PIECE_START_Y + 2;
    p.b[0] = b1;
    p.b[1] = b2;
    p.b[2] = b3;
    p.b[3] = b4;
    p.c = 1;
    p.ind = 0;
    p.type = 2;
    game->listePiece[2] = p;

    // O
    b1.x = PIECE_START_X + 1;
    b1.y = PIECE_START_Y + 2;
    b2.x = PIECE_START_X + 2;
    b2.y = PIECE_START_Y + 2;
    b3.x = PIECE_START_X + 1;
    b3.y = PIECE_START_Y + 3;
    b4.x = PIECE_START_X + 2;
    b4.y = PIECE_START_Y + 3;
    p.b[0] = b1;
    p.b[1] = b2;
    p.b[2] = b3;
    p.b[3] = b4;
    p.c = 0;
    p.ind = 0;
    p.type = 3;
    game->listePiece[3] = p;

    // S
    b1.x = PIECE_START_X + 3;
    b1.y = PIECE_START_Y + 2;
    b2.x = PIECE_START_X + 2;
    b2.y = PIECE_START_Y + 2;
    b3.x = PIECE_START_X + 2;
    b3.y = PIECE_START_Y + 3;
    b4.x = PIECE_START_X + 1;
    b4.y = PIECE_START_Y + 3;
    p.b[0] = b1;
    p.b[1] = b2;
    p.b[2] = b3;
    p.b[3] = b4;
    p.c = 2;
    p.ind = 0;
    p.type = 4;
    game->listePiece[4] = p;

    // L
    b1.x = PIECE_START_X + 3;
    b1.y = PIECE_START_Y + 2;
    b2.x = PIECE_START_X + 2;
    b2.y = PIECE_START_Y + 2;
    b3.x = PIECE_START_X + 1;
    b3.y = PIECE_START_Y + 2;
    b4.x = PIECE_START_X + 1;
    b4.y = PIECE_START_Y + 3;
    p.b[0] = b1;
    p.b[1] = b2;
    p.b[2] = b3;
    p.b[3] = b4;
    p.c = 1;
    p.ind = 0;
    p.type = 5;
    game->listePiece[5] = p;

    // I
    b1.x = PIECE_START_X;
    b1.y = PIECE_START_Y + 2;
    b2.x = PIECE_START_X + 1;
    b2.y = PIECE_START_Y + 2;
    b3.x = PIECE_START_X + 2;
    b3.y = PIECE_START_Y + 2;
    b4.x = PIECE_START_X + 3;
    b4.y = PIECE_START_Y + 2;
    p.b[0] = b1;
    p.b[1] = b2;
    p.b[2] = b3;
    p.b[3] = b4;
    p.c = 0;
    p.ind = 0;
    p.type = 6;
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
        if (0 <= b.x && b.x < WIDTH && 0 <= b.y && b.y < HEIGHT)
        {
            game->map[b.y * WIDTH + b.x].a = 1;
            game->map[b.y * WIDTH + b.x].c = game->p.c;
        }
    }
}

// retire la pièce du tableau pour la déplacer
void removePiece(GameState *game)
{
    for (int i = 0; i < 4; i++)
    {
        Block b = game->p.b[i];
        if (0 <= b.x && b.x < WIDTH && 0 <= b.y && b.y < HEIGHT)
        {
            game->map[b.y * WIDTH + b.x].a = 0;
        }
    }
}

// déplace la pièce vers le bas
void moveDown(Cel *map, Piece *p)
{
    for (int i = 0; i < 4; i++)
    {
        (*p).b[i].y++;
    }
}

// déplace la pièce vers le haut (pour gérer les collisions)
void moveUp(Cel *map, Piece *p)
{
    for (int i = 0; i < 4; i++)
    {
        (*p).b[i].y--;
    }
}

// déplace la pièce vers la droite
void moveRight(Cel *map, Piece *p)
{
    for (int i = 0; i < 4; i++)
    {
        (*p).b[i].x++;
    }
}

// déplace la pièce vers la gauche
void moveLeft(Cel *map, Piece *p)
{
    for (int i = 0; i < 4; i++)
    {
        (*p).b[i].x--;
    }
}

// fait tourner la pièce vers la droite
void rotateRight(Cel *map, Piece *p)
{
    switch ((*p).type)
    {
    // rotation droite pour le T
    case 0:
        switch ((*p).ind)
        {
        case 0:
            (*p).b[0].x++;
            (*p).b[0].y--;

            (*p).b[2].x--;
            (*p).b[2].y++;

            (*p).b[3].x--;
            (*p).b[3].y--;
            break;

        case 1:
            (*p).b[0].x++;
            (*p).b[0].y++;

            (*p).b[2].x--;
            (*p).b[2].y--;

            (*p).b[3].x++;
            (*p).b[3].y--;
            break;

        case 2:
            (*p).b[0].x--;
            (*p).b[0].y++;

            (*p).b[2].x++;
            (*p).b[2].y--;

            (*p).b[3].x++;
            (*p).b[3].y++;
            break;

        case 3:
            (*p).b[0].x--;
            (*p).b[0].y--;

            (*p).b[2].x++;
            (*p).b[2].y++;

            (*p).b[3].x--;
            (*p).b[3].y++;
            break;

        default:
            break;
        }
        break;

    // rotation droite pour le J
    case 1:
        switch ((*p).ind)
        {
        case 0:
            (*p).b[0].x++;
            (*p).b[0].y--;

            (*p).b[2].x--;
            (*p).b[2].y++;

            (*p).b[3].x -= 2;
            break;

        case 1:
            (*p).b[0].x++;
            (*p).b[0].y++;

            (*p).b[2].x--;
            (*p).b[2].y--;

            (*p).b[3].y -= 2;
            break;

        case 2:
            (*p).b[0].x--;
            (*p).b[0].y++;

            (*p).b[2].x++;
            (*p).b[2].y--;

            (*p).b[3].x += 2;
            break;

        case 3:
            (*p).b[0].x--;
            (*p).b[0].y--;

            (*p).b[2].x++;
            (*p).b[2].y++;

            (*p).b[3].y += 2;
            break;

        default:
            break;
        }
        break;

    // rotation droite pour le Z
    case 2:
        if ((*p).ind == 0 || (*p).ind == 2)
        {
            (*p).b[0].y -= 2;

            (*p).b[1].x++;
            (*p).b[1].y--;

            (*p).b[3].x++;
            (*p).b[3].y++;
        }
        else if ((*p).ind == 1 || (*p).ind == 3)
        {
            (*p).b[0].y += 2;

            (*p).b[1].x--;
            (*p).b[1].y++;

            (*p).b[3].x--;
            (*p).b[3].y--;
        }
        break;

    // rotation droite pour le S
    case 4:
        if ((*p).ind == 0 || (*p).ind == 2)
        {
            (*p).b[0].x--;
            (*p).b[0].y--;

            (*p).b[2].x++;
            (*p).b[2].y--;

            (*p).b[3].x += 2;
        }
        else if ((*p).ind == 1 || (*p).ind == 3)
        {
            (*p).b[0].x++;
            (*p).b[0].y++;

            (*p).b[2].x--;
            (*p).b[2].y++;

            (*p).b[3].x -= 2;
        }
        break;

    // rotation droite pour le L
    case 5:
        switch ((*p).ind)
        {
        case 0:
            (*p).b[0].x--;
            (*p).b[0].y++;

            (*p).b[2].x++;
            (*p).b[2].y--;

            (*p).b[3].y -= 2;
            break;

        case 1:
            (*p).b[0].x--;
            (*p).b[0].y--;

            (*p).b[2].x++;
            (*p).b[2].y++;

            (*p).b[3].x += 2;
            break;

        case 2:
            (*p).b[0].x++;
            (*p).b[0].y--;

            (*p).b[2].x--;
            (*p).b[2].y++;

            (*p).b[3].y += 2;
            break;

        case 3:
            (*p).b[0].x++;
            (*p).b[0].y++;

            (*p).b[2].x--;
            (*p).b[2].y--;

            (*p).b[3].x -= 2;
            break;

        default:
            break;
        }
        break;

    // rotation droite pour le I
    case 6:
        if ((*p).ind == 0 || (*p).ind == 2)
        {
            (*p).b[0].x += 2;
            (*p).b[0].y -= 2;

            (*p).b[1].x++;
            (*p).b[1].y--;

            (*p).b[3].x--;
            (*p).b[3].y++;
        }
        else if ((*p).ind == 1 || (*p).ind == 3)
        {
            (*p).b[0].x -= 2;
            (*p).b[0].y += 2;

            (*p).b[1].x--;
            (*p).b[1].y++;

            (*p).b[3].x++;
            (*p).b[3].y--;
        }
        break;

    default:
        break;
    }
    if ((*p).ind == 3)
    {
        (*p).ind = 0;
    }
    else
    {
        (*p).ind++;
    }
}

// fait tourner la pièce vers la gauche
void rotateLeft(Cel *map, Piece *p)
{
    switch ((*p).type)
    {
    // rotation gauche pour le T
    case 0:
        switch ((*p).ind)
        {
        case 0:
            (*p).b[0].x++;
            (*p).b[0].y++;

            (*p).b[2].x--;
            (*p).b[2].y--;

            (*p).b[3].x++;
            (*p).b[3].y--;
            break;

        case 1:
            (*p).b[0].x--;
            (*p).b[0].y++;

            (*p).b[2].x++;
            (*p).b[2].y--;

            (*p).b[3].x++;
            (*p).b[3].y++;
            break;

        case 2:
            (*p).b[0].x--;
            (*p).b[0].y--;

            (*p).b[2].x++;
            (*p).b[2].y++;

            (*p).b[3].x--;
            (*p).b[3].y++;
            break;

        case 3:
            (*p).b[0].x++;
            (*p).b[0].y--;

            (*p).b[2].x--;
            (*p).b[2].y++;

            (*p).b[3].x--;
            (*p).b[3].y--;
            break;

        default:
            break;
        }
        break;

    // rotation gauche pour le J
    case 1:
        switch ((*p).ind)
        {
        case 0:
            (*p).b[0].x++;
            (*p).b[0].y++;

            (*p).b[2].x--;
            (*p).b[2].y--;

            (*p).b[3].y -= 2;
            break;

        case 1:
            (*p).b[0].x--;
            (*p).b[0].y++;

            (*p).b[2].x++;
            (*p).b[2].y--;

            (*p).b[3].x += 2;
            break;

        case 2:
            (*p).b[0].x--;
            (*p).b[0].y--;

            (*p).b[2].x++;
            (*p).b[2].y++;

            (*p).b[3].y += 2;
            break;

        case 3:
            (*p).b[0].x++;
            (*p).b[0].y--;

            (*p).b[2].x--;
            (*p).b[2].y++;

            (*p).b[3].x -= 2;
            break;

        default:
            break;
        }
        break;

    // rotation gauche pour le Z
    case 2:
        if ((*p).ind == 0 || (*p).ind == 2)
        {
            (*p).b[0].y -= 2;

            (*p).b[1].x++;
            (*p).b[1].y--;

            (*p).b[3].x++;
            (*p).b[3].y++;
        }
        else if ((*p).ind == 1 || (*p).ind == 3)
        {
            (*p).b[0].y += 2;

            (*p).b[1].x--;
            (*p).b[1].y++;

            (*p).b[3].x--;
            (*p).b[3].y--;
        }
        break;

    // rotation gauche pour le S
    case 4:
        if ((*p).ind == 0 || (*p).ind == 2)
        {
            (*p).b[0].x--;
            (*p).b[0].y--;

            (*p).b[2].x++;
            (*p).b[2].y--;

            (*p).b[3].x += 2;
        }
        else if ((*p).ind == 1 || (*p).ind == 3)
        {
            (*p).b[0].x++;
            (*p).b[0].y++;

            (*p).b[2].x--;
            (*p).b[2].y++;

            (*p).b[3].x -= 2;
        }
        break;

    // rotation gauche pour le L
    case 5:
        switch ((*p).ind)
        {
        case 0:
            (*p).b[0].x--;
            (*p).b[0].y--;

            (*p).b[2].x++;
            (*p).b[2].y++;

            (*p).b[3].x += 2;
            break;

        case 1:
            (*p).b[0].x++;
            (*p).b[0].y--;

            (*p).b[2].x--;
            (*p).b[2].y++;

            (*p).b[3].y += 2;
            break;

        case 2:
            (*p).b[0].x++;
            (*p).b[0].y++;

            (*p).b[2].x--;
            (*p).b[2].y--;

            (*p).b[3].x -= 2;
            break;

        case 3:
            (*p).b[0].x--;
            (*p).b[0].y++;

            (*p).b[2].x++;
            (*p).b[2].y--;

            (*p).b[3].y -= 2;
            break;

        default:
            break;
        }
        break;

    // rotation gauche pour le I
    case 6:
        if ((*p).ind == 0 || (*p).ind == 2)
        {
            (*p).b[0].x += 2;
            (*p).b[0].y -= 2;

            (*p).b[1].x++;
            (*p).b[1].y--;

            (*p).b[3].x--;
            (*p).b[3].y++;
        }
        else if ((*p).ind == 1 || (*p).ind == 3)
        {
            (*p).b[0].x -= 2;
            (*p).b[0].y += 2;

            (*p).b[1].x--;
            (*p).b[1].y++;

            (*p).b[3].x++;
            (*p).b[3].y--;
        }
        break;

    default:
        break;
    }
    if ((*p).ind == 0)
    {
        (*p).ind = 3;
    }
    else
    {
        (*p).ind--;
    }
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
        int x = p.b[i].x;
        int y = p.b[i].y;

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
        int y = p.b[i].y;
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
}

void gameLoop(GameState *game)
{
    View *view = createView(SDL_VIEW);

    highScore = getHighScore("highscore.txt");
    int cleared;
    int run = 1;
    int ch;

    insertPiece(game);
    updateView(SDL_VIEW, view, game);
    removePiece(game);

    while (run)
    {
        removePiece(game);
        event(SDL_CONTROLLER, game, &run);

        insertPiece(game);
        updateView(SDL_VIEW, view, game);
    }

    destroyView(SDL_VIEW, view);

    free(game->map);
    free(game->listePiece);
    free(game);
}