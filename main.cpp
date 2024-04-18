#include "Tetramini.hpp"
#include <ncurses.h>
using namespace std; 

//const int dimw_y=45;  //Tetramini.hpp
//const int dimw_x=31;
//const int y_start_w=5;
//const int x_start_w=20;


int main(){
 srand(time(0));
 bool gameOver=false;
 initscr();
 WINDOW *win = newwin( dimw_y ,dimw_x , y_start_w , x_start_w); 
 box(win, 0, 0);
 wrefresh(win);
 refresh();
 
  
 Quadrato *q = new Quadrato(win, 3 , dimw_x/2 -2);
 //Linea *q = new Linea(win, 0, 0);

 do{ 	
 	q->display();
	box(win, 0, 0);
	wrefresh(win);
	refresh();
 }while(q->getmv()!='x'); 

 endwin();
 return 0; 
}




	








