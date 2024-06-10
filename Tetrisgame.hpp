#include <ncurses.h>
#include <iostream>
#include "menu.hpp"
#include "griglia.hpp"
#include "ranking.hpp"

class TetrisGame{
    protected:
    int xmax, ymax;
    bool game_over;
    public:
    TetrisGame();

};