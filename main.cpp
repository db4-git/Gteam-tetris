#include "Tetramini.hpp"
#include <ncurses.h>
using namespace std; 

//const int dimw_y=45;  //Tetramini.hpp
//const int dimw_x=31;
//const int y_start_w=5;
//const int x_start_w=20;

bool isplaying = true;
int choice;

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
		choice = wgetch(win);
		if(choice == ERR ) q->mvdown();
		else q->getmv(choice);
 }while(isplaying == true);


}
void gameL(Linea *l, WINDOW *win){
 do{		
		l->display();
		box(win, 0, 0);
		wrefresh(win);
		refresh();
      if(l->isbottom()==true){
			l->saveTetramino();
			wmove(win , 3 , dimw_x/2 - 2);
			isplaying=false;
		}
		choice = wgetch(win);
		if(choice == ERR) l->mvdown();
		else l->getmv(choice);
  }while(isplaying == true);
}

 
int main(){
 srand(time(0));
 initscr();
 noecho();
 WINDOW *win = newwin( dimw_y ,dimw_x , y_start_w , x_start_w); 
 wtimeout(win, 300);		 

 do{	
 	isplaying=true; 		//se lo metto alla fine del while, non rientra più nel ciclo 
 	if((rand()%5)<3){   //Per ora condizione sempre vera, test sul quadrato
   	Quadrato *q = new Quadrato(win, 3, dimw_x/2 - 2);	
   	gameQ(q, win);
 	}
 	else{
 		Linea *l = new Linea(win , 3 , dimw_x/2 - 2);	
		gameL(l, win);
 	} 
 }while(!isplaying);
 endwin();
 return 0; 
}	



	








