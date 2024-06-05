#include <ncurses.h>
//#include "Griglia.hpp"
#include <iostream>
#include "menu.hpp"

class TetrisGame{
    protected:
    //Griglia griglia;
    int xmax, ymax;
    bool game_over;
    Game_Menu *menu;
    public:
    TetrisGame(){
        getmaxyx(stdscr, ymax, xmax);
        menu= new Game_Menu(ymax, xmax);
        
    }

    void processInput(){
        //char input= griglia.getInput();
    }

    bool isOver(){
        return game_over;
    }
};