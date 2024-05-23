#include "Tetramini.hpp"
#include <ncurses.h>
using namespace std; 

//Griglia creata in Tetramini.hpp
bool isplaying = true;
int choice;
int countmv;
int AT[2];   //array che contiene i tetramini successivi
int contT=0;  //conta i tetramini che vengono generati per capire a che profondita' riempire l' AT


void gameQ(Quadrato *q , WINDOW *win){   //passati per riferimento perchè inizializzati dopo nel main
 do{  
	  
   	choice = wgetch(win);
		if(countmv == 5) keypad(win, false);
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
		if(countmv == 5 ) keypad(win , false);
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

/* DA CANCELLARE!
void NextTetramini(arrayp A){      //riaggiorna e stampa i successivi tetramini che verranno generati   //usa una struttura arrayp
	for(int i=0; i<3 ; i++){
		A.val[i]=rand()%5;
		A.generated[i] = false;
	}	
}

void DisplayNextTetramino(arrayp A, WINDOW *win){
	int xloc, yloc;  //come nel piano cartesiano
	//Metto a video i prossimi Tetramini che verranno generati{
		   A.generated[0] = false;
			for(int j=0; j<3 ; j++){    //shift arrayp.val a sinistra
					A.val[j] = A.val[j+1];
			}
			A.val[2] = rand()%5;
	wclear(win);
	box(win , 0 , 0); //così la griglia rimane
	for(int i=0; i<3; i++){   		
			if(i==0){
				yloc = 5 , xloc = 6;
				wmove(win , 5 , 1);
				wprintw(win, "-->");
				}
			else if(i==1) yloc= 10, xloc = 6;
			else if(i==2) yloc = 15 , xloc = 6;
				if(A.val[i]<3){
				//stampa quadrato
				for(int i=0; i<2; i++){
					wmove(win , yloc , xloc);
					for(int j=0; j<4; j++){
						if(j%2==0) wprintw(win,"[");
						else wprintw(win,"]");
					}
					yloc++;
				}
			}else if(A.val[i]>=3){
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
} */

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

int main(){
 srand(time(0));

 initscr();
 noecho();
 curs_set(0);
 WINDOW *win = newwin( dimw_y ,dimw_x , y_start_w , x_start_w);
 WINDOW *gamestat = newwin( 24 , 26 , 10, 60);   //finestra con le statistiche di gioco (tetramini successivi, punteggio attuale, ecc..) 
 wtimeout(win, 250);		 
 //pongo a false l'arrayp contenente i tetramini
 box(gamestat, 0 ,0 );
 refresh();
 wrefresh(gamestat);
 do{	
 	isplaying=true; 		//se lo metto alla fine del while, non rientra più nel ciclo
	UpdateStatTetramini(AT);
	DisplayTetramini(AT, gamestat);
	if((AT[contT]<2)){   
   	Quadrato *q = new Quadrato(win, 3, dimw_x/2 - 2);	
		countmv=0;
		gameQ(q, win);
 	}
 	else{
 		Linea *l = new Linea(win , 3 , dimw_x/2 - 2);	
		countmv=0;
		gameL(l, win);
 	}
	contT++;   //Ogni volta che un tetramino generato arriva in fondo, si incrementa contT
	refresh();
	wrefresh(gamestat); 
 }while(!isplaying);
 endwin();
 return 0; 
}	



	








