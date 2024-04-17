#include "Tetramini.hpp"
#include <ncurses.h>
using namespace std; 

//const int dimw_y=45;  //Tetramini.hpp
//const int dimw_x=31;
//const int y_start_w=5;
//const int x_start_w=20;


void setcuror(WINDOW *p){
	wmove(p,y_start_w+2,x_start_w+dimw_x/2-1);
}

int main(){ 
 bool gameOver=false;
 char ch;
 initscr();
 WINDOW *win = newwin(dimw_y, dimw_x, y_start_w, x_start_w);
 box(win, 0, 0);
 wrefresh(win);
 refresh();
 setcuror(win);   //funzione che muove il cursore in posizione origine tetramini
 Quadrato P = Quadrato(win, y_start_w+2 , x_start_w + dimw_x/2 - 1 );
 keypad(P.curwin, true);
 while(wgetch(P.curwin)!='x'){
 
 }
 
 endwin();

 return 0; 
}






	








