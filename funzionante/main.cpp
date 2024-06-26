//#include "Tetramini.hpp"
//#include "menu.hpp"
#include "griglia.hpp"
//#include "ranking.hpp"
//#include "grafiche.hpp"
//#include "Tetrisgame.hpp"
#include <ncurses.h>

using namespace std; 

//Griglia creata in Tetramini.hpp
/*bool isplaying = true;
int choice;
int countmv;
int AT[2];   //array che contiene i tetramini successivi
int contT=0;  //conta i tetramini che vengono generati per capire a che profondita' riempire l' AT
int score = 0;*/
/*
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

bool checkFullEmptyLine(WINDOW *win, int y, int x = 1) {
	if (x == dimw_x - 1) return true;

	return (mvwinch(win, y, x) == ' ') && checkFullEmptyLine(win, y, x + 1); 
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
			if (checkFullEmptyLine(win, i)) {
				b = true;
				break;
			}

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
*/
int main(){
/* srand(time(0));

 initscr();
 noecho();
 curs_set(0);*/
/* WINDOW *win = newwin( dimw_y ,dimw_x , y_start_w , x_start_w);
 WINDOW *gamestat = newwin( 20 , 26 , 10, 60);   //finestra con le statistiche di gioco (tetramini successivi, punteggio attuale, ecc..) 
 wtimeout(win, 250);		 
 //pongo a false l'arrayp contenente i tetramini
 box(gamestat, 0 ,0 );
 refresh();
 wrefresh(gamestat);
 do{	
 	isplaying=true; 		//se lo metto alla fine del while, non rientra più nel ciclo
	UpdateStatTetramini(AT);
	DisplayTetramini(AT, gamestat);
	UpdateScore(gamestat, 0);
	if((AT[contT]<2)){     		
		if (gameOverQ(win)) {
			wclear(win);
			wclear(gamestat);
			wrefresh(win);
			wrefresh(gamestat);
			delwin(win);
			delwin(gamestat);
			//mvwaddch(win, 1, dimw_x - 3, 'a');
			//break;
			create_menu(dimw_y, dimw_x);
		}
		Quadrato *q = new Quadrato(win, 1 , dimw_x/2 - 1);	
		countmv=0;
		gameQ(q, win, gamestat);
	}
 	else{ 	
		if (gameOverL(win)) {
			wclear(win);
			wclear(gamestat);
			wrefresh(win);
			wrefresh(gamestat);
			delwin(win);
			delwin(gamestat);
			//mvwaddch(win, 1, dimw_x - 3, 'a');
			//break;
			create_menu(dimw_y, dimw_x);
		}
		Linea *l = new Linea(win , 1 , dimw_x/2 - 1);	
		countmv=0;
		gameL(l, win, gamestat);
 	}
	contT++;   //Ogni volta che un tetramino generato arriva in fondo, si incrementa contT
	refresh();
	wrefresh(gamestat); 
 }while(!isplaying);
 */
        initscr();    //queste sono le funzioni che inizializzano tutto ncurses
        noecho();
        cbreak();
        curs_set(0);
	int xmax, ymax;
        getmaxyx(stdscr, ymax, xmax);
     
        int sce;
        int highlight=0;
        create_menu(ymax, xmax, highlight, sce);
      
        
            while (1)  //ciclo infinito che si interrompe solo con control c poi decidete voi
            {
                 if (highlight==0 && sce == 10) // crea la griglia quando si seleziona il tasto NUOVA PARTITA
            {
                create_griglia(highlight, sce);
                    create_menu(ymax, xmax, highlight, sce);
                
                
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
 

 endwin();
 return 0; 
}	



	
