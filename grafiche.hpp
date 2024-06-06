#include "Tetramini.hpp";
#include <ncurses.h>;
using namespace std;

isplaying = true;
int choice;
int countmv;
int AT[2];
int contT=0;
int score = 0;


void UpdateScore(WINDOW *win , int cont);

bool gameOverL(WINDOW *win);

bool gameOverQ(WINDOW *win);

bool checkLine(WINDOW *win , int y);

void replaceLines(WINDOW *win, int y);

int delLines(WINDOW *win);

void gameQ(Quadrato *q , WINDOW *win , WINDOW *gwin);

void gameL(Linea *l , WINDOW *win , WINDOW *gwin);

void UpdateStatTetramini(int A[]);

void DisplayTetramini(int A[], WINDOW *win);


