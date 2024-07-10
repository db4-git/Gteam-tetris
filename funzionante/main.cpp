//#include "Tetramini.hpp"
//#include "menu.hpp"
#include "griglia.hpp"
//#include "ranking.hpp"
//#include "grafiche.hpp"
//#include "Tetrisgame.hpp"
#include <ncurses.h> 

using namespace std; 
	int main(){
        initscr();    //queste sono le funzioni che inizializzano tutto ncurses
        noecho();
        cbreak();
        curs_set(0);
		  int xmax, ymax;
        getmaxyx(stdscr, ymax, xmax);
        int sce;
        int highlight=0;
		  bool close;
        close=create_menu(ymax, xmax, highlight, sce);
     	 

    while(!close){
         if (highlight==0 && sce == 10){
             	create_griglia(highlight, sce);
               close=create_menu(ymax, xmax, highlight, sce);
         }
         if (highlight==1 && sce == 10){
             	create_ranking(ymax, xmax, sce);
               if (sce == 'q'){
                	close=create_menu(ymax, xmax, highlight, sce); //ricrea il menu (riparte il ciclo while)
					}
         }
			
   }
 endwin();
 return 0; 
}	



	
