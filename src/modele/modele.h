#ifndef MODELE_H
#define MODELE_H

#include "view/view.h"

extern const int WIDTH;
extern const int HEIGHT;
extern const int PIECE_START_X;
extern const int PIECE_START_Y;
extern const int TAILLE_CEL;

extern int SCALE;
extern int nbLignes;
extern int level;
extern int score;
extern int highScore;
extern int stats[];

typedef struct View View;

// structure qui contient les coordonnées x, y d'un block
typedef struct Block
{
    int x;
    int y;
} Block;

// structure de la pièce qui tombe
// contient la position des 4 blocks qui la composent, sa couleur, son type et l'indice de sa rotation
typedef struct Piece
{
    Block b[4]; // liste de la pos des 4 blocks
    int c;      // couleur --> ind de la liste des couleurs
    int type;   // dans la liste [T, J, Z, O, S, L, I]
    int h, w;   // taille la matrice
    int x, y;   // coordonnees du coins supérieur gauche de la matrice
} Piece;

// structure de cellule qui compose la map
typedef struct Cel
{
    int a; // 1 si il contient un block et 0 si vide
    int c; // couleur du block si a non vide
} Cel;

typedef struct GameState
{
    Cel *map;
    Piece p;
    Piece nextBox;
    Piece *listePiece;
    int run;
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
void affiche(Cel *map, Piece nextBox);
int verifCollision(Cel *map, Piece p);
int verifDeleteLine(Cel *map, int y);
void mapDown(Cel *map, int y);
int getHighScore(char *file);
void updateHighScore(char *file, int high);
void updateLevel();
int piecePosee(Cel *map, Piece p);
void gameLoop(View *view, GameState *game);
void changePiece(GameState *game);
void ajouteScore(int nb);

#endif