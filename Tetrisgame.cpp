#include "Tetrisgame.hpp"
using namespace std;

TetrisGame :: TetrisGame(){
        initscr();    //queste sono le funzioni che inizializzano tutto ncurses
        noecho();
        cbreak();
        curs_set(0);
        getmaxyx(stdscr, ymax, xmax);
     
        int sce;
        int highlight=0;
        create_menu(ymax, xmax, highlight, sce);
      
        
            while (1)  //ciclo infinito che si interrompe solo con control c poi decidete voi
            {
                 if (highlight==0 && sce == 10) // crea la griglia quando si seleziona il tasto NUOVA PARTITA
            {
                create_griglia();
                /*if (sce== 'w') // serve a rimettere menu una volta finito il game
                {
                    create_menu(ymax, xmax, highlight, sce);
                }*/
                
                
            }
            if (highlight==1 && sce == 10) // crea la classifica quando si seleziona il tasto Classifica
            {
                create_ranking(ymax, xmax, sce);
                if (sce == 'q')
                {
                    create_menu(ymax, xmax, highlight, sce); //ricrea il menu (riparte il ciclo while)
                }
                
            }
            }
        endwin();
    }