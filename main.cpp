#include "Tetramini.hpp"
#include <ncurses.h>
using namespace std; 

//Griglia creata in Tetramini.hpp
bool isplaying = true;
int choice;
int countmv;

void gameQ(Quadrato *q , WINDOW *win){   //passati per riferimento perchè inizializzati dopo nel main
 do{  
	  
   	choice = wgetch(win);
		if(countmv == 8) keypad(win, false);
		if(choice == ERR || countmv >= 8 ){
	 		q->mvdown();
			countmv=0;
		}
		q->getmv(choice);
		keypad(win , true);
		q->display();
		box(win, 0, 0);
		wrefresh(win);
		refresh();
		if(q->isbottom()==true){
			q->saveTetramino();
			wmove(win , 3 , dimw_x/2 - 2);
			isplaying=false;
		}
   	countmv++;
 }while(isplaying == true);

}
void gameL(Linea *l, WINDOW *win){
 do{	
	   
   	choice = wgetch(win);
		if(countmv == 8 ) keypad(win , false);
		if(choice == ERR || countmv >= 8 ){ 
			l->mvdown();
			countmv=0;
		}
		l->getmv(choice);
		keypad(win , true);
		l->display();
		box(win, 0, 0);
		wrefresh(win);
		refresh();
		if(l->isbottom()==true){
			l->saveTetramino();
			wmove(win , 3 , dimw_x/2 - 2);
			isplaying=false;
		}
		countmv++;
  }while(isplaying == true);
}

 
int main(){
 srand(time(0));
 initscr();
 noecho();
 WINDOW *win = newwin( dimw_y ,dimw_x , y_start_w , x_start_w); 
 wtimeout(win, 450);		 

 do{	
 	isplaying=true; 		//se lo metto alla fine del while, non rientra più nel ciclo 
 	if((rand()%5)<3){   //Per ora condizione sempre vera, test sul quadrato
   	Quadrato *q = new Quadrato(win, 3, dimw_x/2 - 2);	
   	countmv=0;
		gameQ(q, win);
 	}
 	else{
 		Linea *l = new Linea(win , 3 , dimw_x/2 - 2);	
		countmv=0;
		gameL(l, win);
 	} 
 }while(!isplaying);
 endwin();
 return 0; 
}	



	








