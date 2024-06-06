#include <ncurses.h>
//#include "Griglia.hpp"
#include <iostream>
#include "menu.hpp"
#include "griglia.hpp"
//#include "file.hpp"

class TetrisGame{
    protected:
    //Griglia griglia;
    int xmax, ymax;
    bool game_over;
    //Game_Menu *menu;
    //Ranking *classifica;
    public:
    TetrisGame(){
        initscr();
        noecho();
        cbreak();
        curs_set(0);
        int sce;
        getmaxyx(stdscr, ymax, xmax);
     
        
        int highlight=0;
        //menu = new Game_Menu(ymax, xmax, highlight, sce);
        //create_griglia();
        create_menu(ymax, xmax, highlight, sce);
      
        
            while (1)
            {
                 if (highlight==0 && sce == 10)
            {
                create_griglia();
                
            }
            if (highlight==1 && sce == 10)
            {
                create_ranking(ymax, xmax, sce);
                if (sce == 'q')
                {
                    create_menu(ymax, xmax, highlight, sce);
                }
                
            }
            }
            //create_menu(ymax, xmax, highlight, sce);
            //sce=getch();
            //create_menu(ymax, xmax, highlight, sce);
            /*if (highlight==0 && sce == 10)
            {
                create_griglia();
            }
            if (highlight==1 && sce == 10)
            {
                create_ranking(ymax, xmax);
                refresh();
            }
            */

        //create_griglia();
        
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