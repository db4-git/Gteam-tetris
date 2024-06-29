#include "griglia.hpp"
//#include "grafiche.hpp"

void create_griglia(int &h, int &c){
  /*  WINDOW *griglia=newwin(40, 32, 5, 50);
    WINDOW *gamestat = newwin( 20 , 26 , 10, 90);
    box(griglia, 0,0);
    box(gamestat, 0,0);
    wrefresh(griglia);
    wrefresh(gamestat);*/
     WINDOW *win = newwin( dimw_y ,dimw_x , y_start_w , x_start_w);
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
			save_data(score);
			score = 0;
			wclear(win);
			wclear(gamestat);
			wrefresh(win);
			wrefresh(gamestat);
			delwin(win);
			delwin(gamestat);
			//mvwaddch(win, 1, dimw_x - 3, 'a');
			//break;
			//create_menu(dimw_y, dimw_x, h, c);
			return;
		}
		Quadrato *q = new Quadrato(win, 1 , dimw_x/2 - 1);	
		countmv=0;
		gameQ(q, win, gamestat);
	}
 	else{ 	
		if (gameOverL(win)) {
			save_data(score);
			score = 0;
			wclear(win);
			wclear(gamestat);
			wrefresh(win);
			wrefresh(gamestat);
			delwin(win);
			delwin(gamestat);
			//create_menu(dimw_y, dimw_x, h, c);
			return;
		}
		Linea *l = new Linea(win , 1 , dimw_x/2 - 1);	
		countmv=0;
		gameL(l, win, gamestat);
 	}
	contT++;   //Ogni volta che un tetramino generato arriva in fondo, si incrementa contT
	refresh();
	wrefresh(gamestat); 
 }while(!isplaying);
 
}

