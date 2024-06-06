#include <ncurses.h>
//#include "Tetramoni.hpp"
bool isplaying = true;
int choice;
int countmv;
int AT[2];   //array che contiene i tetramini successivi
int contT=0;  




/*void gameQ(Quadrato *q , WINDOW *win){   //passati per riferimento perchè inizializzati dopo nel main
 do{  
	  
   	choice = wgetch(win);
		if(countmv == 5) keypad(win, false);
		if(choice == ERR || countmv >= 8 ){
	 		q->mvdown();
			countmv=0;
		}
		else if (choice == KEY_LEFT && !q->leftIsBlocked()) {
			q->getmv(choice);
		}
		else if (choice == KEY_RIGHT && !q->rightIsBlocked()) {
			q->getmv(choice);
		}
		else if (choice == KEY_UP || choice == KEY_DOWN) {
			q->getmv(choice);
		}
		keypad(win , true);
		q->display();
		box(win, 0, 0);
		wrefresh(win);
		refresh();
		if(q->isbottom()==true){
			q->saveTetramino();
			wmove(win , 3 , dimw_x/2);
			isplaying=false;
		}
   	countmv++;
 }while(isplaying == true);

}
void gameL(Linea *l, WINDOW *win){
 do{	
	   
   	choice = wgetch(win);
		if(countmv == 5 ) keypad(win , false);
		if(choice == ERR || countmv >= 8 ){ 
			l->mvdown();
			countmv=0;
		}
                else if (choice == KEY_LEFT && !l->leftIsBlocked()) l->getmv(choice);
		else if (choice == KEY_RIGHT && !l->rightIsBlocked()) l->getmv(choice);
		else if (choice == KEY_UP && l->canRotate()) l->getmv(choice);
		else if (choice == KEY_DOWN) l->getmv(choice);
		keypad(win , true);
		l->display();
		box(win, 0, 0);
		wrefresh(win);
		refresh();
		if(l->isbottom()==true){
			l->saveTetramino();
			wmove(win , 3 , dimw_x/2 - 1);
			isplaying=false;
		}
		countmv++;
  }while(isplaying == true);
}*/

void create_griglia(){
    WINDOW* griglia=newwin(40, 32, 5, 20);
    WINDOW *gamestat = newwin( 20 , 26 , 10, 60);
    box(griglia, 0,0);
    box(gamestat, 0,0);
    wrefresh(griglia);
    wrefresh(gamestat);
}