#include "Tetramini.hpp"
#include <ncurses.h>

using namespace std;

extern bool isplaying;
extern int choice;
extern int countmv;
extern int AT[2];   //array che contiene i tetramini successivi
extern int contT;  //conta i tetramini che vengono generati per capire a che profondita' riempire l' AT
extern int score;



void UpdateScore(WINDOW *win, int cont);

bool gameOverL(WINDOW *win);

bool gameOverQ(WINDOW *win);

bool checkLine(WINDOW *win, int y);

void replaceLines(WINDOW *win, int y);

int delLines(WINDOW *win);

void gameQ(Quadrato *q , WINDOW *win, WINDOW *gwin);

void gameL(Linea *l, WINDOW *win, WINDOW *gwin);

void UpdateStatTetramini(int A[]);

void DisplayTetramini(int A[], WINDOW *win);
