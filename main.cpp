#include "Tetramini.hpp"
#include <ncurses.h>
using namespace std; 

//const int dimw_y=45;  //Tetramini.hpp
//const int dimw_x=31;
//const int y_start_w=5;
//const int x_start_w=20;

bool isplaying = true;

void gameQ(Quadrato *q , WINDOW *win){   //passati per riferimento perchè inizializzati dopo nel main
 do{		
		q->display();
		box(win, 0, 0);
		wrefresh(win);
		refresh();
      if(q->isbottom()==true){
			q->saveTetramino();
			wmove(win , 3 , dimw_x/2 - 2);
			isplaying=false;
		}
 }while(q->getmv() != 'x' || isplaying == true);

}
 
int main(){
 srand(time(0));
 initscr(); 
 noecho();
 WINDOW *win = newwin( dimw_y ,dimw_x , y_start_w , x_start_w); 
		 //Linea *q = new Linea(win , 3 , dimw_x/2 - 2);
 do{	
 if((rand()%5)<=5){   //Per ora condizione sempre vera, test sul quadrato
   Quadrato *q = new Quadrato(win, 3, dimw_x/2 - 2);	
	gameQ(q, win);
 }
 }while(!isplaying);
 endwin();
 return 0; 
}	



	








