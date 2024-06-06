#include <ncurses.h>
//#include "Griglia.hpp"
#include <iostream>
#include "menu.hpp"
//#include "file.hpp"

class TetrisGame{
    protected:
    //Griglia griglia;
    int xmax, ymax;
    bool game_over;
    Game_Menu *menu;
    Ranking *classifica;
    public:
    TetrisGame(){
        initscr();
        noecho();
        cbreak();
        curs_set(0);
        int sce;
        getmaxyx(stdscr, ymax, xmax);
        int highlight=0;
        //create_menu(ymax, xmax);
        menu = new Game_Menu(ymax, xmax, highlight);
        getch();
        endwin();
    }

    void processInput(){
        //char input= griglia.getInput();
    }

    bool isOver(){
        return game_over;
    }
};