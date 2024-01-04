#ifndef MODELE_H
#define MODELE_H

#include <time.h>

#include "view/view.h"

extern const int WIDTH;
extern const int HEIGHT;
extern const int PIECE_START_X;
extern const int PIECE_START_Y;
extern const int TAILLE_CEL;

extern int SCALE;
extern int nbLignes;
extern int level;
extern char changeTransition;
extern int diff;
extern int lim;
extern int score;
extern int highScore;
extern int stats[];

typedef struct View View;

/**
 * @struct Block
 * @brief structure qui contient les coordonnées x, y d'un block
 */
typedef struct Block
{
    int x; //!< coordonnée x
    int y; //!< coordonnée y
} Block;

/**
 * @struct Piece
 * @brief structure de la pièce qui tombe
 */
typedef struct Piece
{
    Block b[4]; //!< liste de la pos des 4 blocks
    int c;      //!< couleur --> ind de la liste des couleurs
    int type;   //!< dans la liste [T, J, Z, O, S, L, I]
    int h, w;   //!< taille de la matrice
    int x, y;   //!< coordonnées du coin supérieur gauche de la matrice
} Piece;

/**
 * @struct Cel
 * @brief Cellule de la matrice
 */
typedef struct Cel
{
    int a; //!< 1 si il contient un block et 0 si vide
    int c; //!< couleur du block si a non vide
} Cel;

/**
 * @struct GameState
 * @brief gamestate du jeu
 */
typedef struct GameState
{
    Cel *map;          //!< matrice du tetris
    Piece p;           //!< structure Piece qui contient la pièce qui tombe
    Piece nextBox;     //!< structure Pièce qui contient la prochaine pièce
    Piece *listePiece; //!< liste de tous les types de pièce
    int run;           //!< variable run pour la boucle du jeu
} GameState;

void initModele(GameState *game);
void initListePiece(GameState *game);
void initMap(GameState *game);
void insertPiece(GameState *game);
void removePiece(GameState *game);
int moveDown(GameState *game);
void moveUp(Cel *map, Piece *p);
void moveRight(Cel *map, Piece *p);
void moveLeft(Cel *map, Piece *p);
void rotateRight(Cel *map, Piece *p);
void rotateLeft(Cel *map, Piece *p);
void deleteLine(Cel *map, int y);
int verifCollision(Cel *map, Piece p);
int verifDeleteLine(Cel *map, int y);
void mapDown(Cel *map, int y);
int getHighScore(char *file);
void updateHighScore(char *file, int high);
void ajouteScore(int nb);
void updateLevel();
int piecePosee(Cel *map, Piece p);
void changePiece(GameState *game);
unsigned int getSpeed();
unsigned int timespecDiff(const struct timespec *time1, const struct timespec *time0);
void gameLoop(View *view, GameState *game);
#endif