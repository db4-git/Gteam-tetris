#include "grafiche.hpp"

using namespace std;

bool isplaying = true;
int choice;
int countmv;
int AT[2];   //array che contiene i tetramini successivi
int contT=0;  //conta i tetramini che vengono generati per capire a che profondita' riempire l' AT
int score = 0;



void UpdateScore(WINDOW *win, int cont) {
	mvwprintw(win, 15, 8, "SCORE: %d", score);
	score = score + (cont * 100);
	wrefresh(win);
}

bool gameOverL(WINDOW *win) {
    if (mvwinch(win, 1, dimw_x/2 - 1) != ' ' || mvwinch(win, 2, dimw_x/2 - 1) != ' ' || mvwinch(win, 3, dimw_x/2 - 1) != ' ' || mvwinch(win, 4, dimw_x/2 - 1) != ' ') return true;

	return false;
     }

bool gameOverQ(WINDOW *win) {
	if (mvwinch(win, 1, dimw_x/2 - 1) != ' ' || mvwinch(win, 2, dimw_x/2 - 1) != ' ') return true;

	return false;
}

bool checkLine(WINDOW *win, int y) {
	bool c = false;
	
    	for (int i = 1; i < dimw_x - 1; i++) {
		if (mvwinch(win, y, i) == ' ' ) {
			c = false;
			break;
		}
		else {
			c = true;
		}
	}
	
	return c;
}

void replaceLines(WINDOW *win, int y) {
	bool b = false;

	for (int i = y; i > 2; i--) {
		for (int j = 1; j < dimw_x - 1; j++) {
			/*if (checkFullEmptyLine(win, i)) {
				b = true;
				break;
			}*/

			chtype r = mvwinch(win, i - 1, j);

			mvwaddch(win, i, j, 'r');	
		}
		if (b) break;
	}

	//wrefresh(win);
	//refresh();
}

int delLines(WINDOW *win) {
	int countLines = 0;

	for (int i = dimw_y - 2; i > 1; i--) {
		if (checkLine(win, i)) {
			replaceLines(win, i);
			countLines++;
			i++;
		}
	}

	//wrefresh(win);
	//refresh();

	return countLines;
}



void gameQ(Quadrato *q , WINDOW *win, WINDOW *gwin){   //passati per riferimento perchè inizializzati dopo nel main
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
			int contS = delLines(win);
			UpdateScore(gwin, contS);
		}
   	countmv++;
 }while(isplaying == true);

}
void gameL(Linea *l, WINDOW *win, WINDOW *gwin){
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
			int contS = delLines(win);
			UpdateScore(gwin, contS);
		}
		countmv++;
  }while(isplaying == true);
}
					

void UpdateStatTetramini(int A[]){			//Aggiorna continuamente l'array di tetramini da generare 
	if(contT == 0){		//primo turno della partita: primo pezzo generato in assoluto: contT = 0;
 		for(int i=0 ; i<2 ; i++){
			A[i] = rand()%5;
		}		
	}
	else{				//cont > 0 
		   A[0] = A[1];    //shift 
			A[1] = rand()%5;
			contT = 0;
	}
}


void DisplayTetramini(int A[], WINDOW *win){
	int xloc , yloc;
	int xf, yf;
	wclear(win);
	box(win , 0 , 0);
	for(int z=0; z<2 ; z++){	
		if(z==0) yloc = 5, xloc = 10;
		else yloc = 10, xloc = 10;
		mvwprintw(win , 5 , 1 , "CURRENT->" ); 
		mvwprintw(win , 10 , 1 ,  "NEXT-> ");
		if(A[z]<2){
		//stampa quadrato
			for(int i=0; i<2; i++){
					wmove(win , yloc , xloc);
					for(int j=0; j<4; j++){
							if(j%2==0) wprintw(win,"[");
							else wprintw(win,"]");
					}
					yloc++;
			}
		}
		else{
   		//stampa linea
			for(int i=0; i<4; i++){
				wmove(win , yloc , xloc);
				for(int j=0; j<2; j++){
						if(j%2==0) wprintw(win, "[");
						else wprintw(win , "]");
				}
				yloc++;	
			}	
		} 
	}
	refresh();
	wrefresh(win);
}
