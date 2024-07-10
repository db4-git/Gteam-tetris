#include "Tetramini.hpp"

using namespace std;

Tetramini::Tetramini() {
    curwin = newwin(dimw_y, dimw_x, y_start_w, x_start_w);
}

void Tetramini::mvdown() {
        yloc++;
}

void Tetramini::mvleft() {
        xloc = xloc - 2;
}

void Tetramini::mvright() {
        xloc = xloc + 2;
}

void Tetramini::rotation() {}

void Tetramini::saveTetramino() {}

int Tetramini::getmv(){
        this->choice = wgetch(curwin);
        switch (choice)
        {
        case KEY_DOWN:
            mvdown();
            break;
        case KEY_LEFT:
            mvleft();
            break;
        case KEY_RIGHT:
            mvright();
            break;
        case KEY_UP:
            rotation();
            break;
        default:
            break;
        }
    return this->choice;
}

void Tetramini::empty2(){
        int y=yloc;
        int x=xloc;
        for (int i = 0; i < L; i++)
        {
        if(cur_rotation==90){        
            if (i % 2 == 0) {
                if (i != 0) {
                    y++;
                    x = xloc;
                }
               
                } 
                mvwaddch(curwin, y, x, ' ');
                x++;
            }else if(cur_rotation == 180){     //posizione orizzontale +1 verso il basso
                if(i==0) y=y+2, x=x-2;
                mvwaddch(curwin, y, x, ' ');
                x++;
                
            } else if (cur_rotation == 270) {
                if(i==0){ 
                    x=x+2;
                }
                if (i % 2 == 0) {
                if (i != 0) {
                    y++;
                    x = xloc+2;
                }
                }
                mvwaddch(curwin, y, x, ' ');
                x++;
            } else if (cur_rotation == 0) {   //posizone orizzontale 
                if(i==0) y++, x=x-2;
                mvwaddch(curwin, y, x, ' ');
                x++;
                
            }
        }

		}

void Tetramini::empty1(){
        int x=xloc;
        int y=yloc;
        for (int  i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                mvwaddch(curwin,y,x, ' ');
                x++;
                if(j==3) x=xloc, y++;
            }
            
        }
    }

void Tetramini::display() {}

Quadrato::Quadrato( WINDOW *win , int y, int x){
	 	  curwin = win;
        keypad(curwin, true);
        getmaxyx(curwin,ymax,xmax);
        yloc=y;
        xloc=x;
        display();
}

void Quadrato::mvdown(){
        empty1();
        if (yloc<ymax-3) yloc++;
    }

void Quadrato::mvleft(){
        empty1();
        if(xloc>2) xloc = xloc - 2;
    }

void Quadrato::mvright(){
        empty1();
        if(xloc< xmax-6) xloc = xloc + 2;
    }

int Quadrato::getmv(int choice){
		  switch (choice)
        	{
       	 case KEY_DOWN:
            	mvdown();
         	   break;
       	 case KEY_LEFT:
            	mvleft();
         	   break;
        	case KEY_RIGHT:
            	mvright();
         	   break;
        	default:
         	   break;
      	}
			return choice;
    	}
    
void Quadrato::display(){
        int x=xloc;
        int y=yloc;
        for (int  i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                if(j%2==0){
                    mvwaddch(curwin,y,x, '[');
                }
                else mvwaddch(curwin,y,x, ']');
                x++;
                if(j==3)x=xloc, y++;
            }
        }
    }

bool Quadrato::isbottom(){
	 	   if(yloc == dimw_x + 5) return true; 
		   else if ((mvwinch(curwin, yloc + 2, xloc) != ' ') || (mvwinch(curwin, yloc + 2, xloc + 2) != ' ')) return true;
		   else	return false;
}

bool Quadrato::leftIsBlocked() {
    	if ((mvwinch(curwin, yloc, xloc - 2) == ' ') && (mvwinch(curwin, yloc + 1, xloc - 2) == ' ')) return false;
	return true;
}

bool Quadrato::rightIsBlocked() {
    	if ((mvwinch(curwin, yloc, xloc + 4) == ' ') && (mvwinch(curwin, yloc + 1, xloc + 4) == ' ')) return false;
	return true;
}

void Quadrato::saveTetramino(){
			keypad(curwin , false);
			display();
}

Linea::Linea (WINDOW *win,int y, int x){
        curwin=win;
        keypad(curwin, true);
        getmaxyx(curwin,ymax,xmax);
        yloc=y;
        xloc=x;
        cur_rotation=90;
        display();
    }
    
void Linea::mvdown(){
        empty2();
        if((cur_rotation==90 || cur_rotation==270) && yloc<ymax-5){
            yloc++;
        }
        else if (cur_rotation == 180 && yloc<ymax-4) {
            yloc++;    
        } else if (cur_rotation == 0 && yloc<ymax-3) {
               yloc++;
        }
    }

void Linea::mvright(){
        empty2();
        if(cur_rotation==90 && xloc<xmax-0){
            xloc = xloc + 2;
        }
        else if ((cur_rotation == 180 || cur_rotation==0) && xloc<xmax-4) {
            xloc = xloc + 2;    
        } else if (cur_rotation == 270 && xloc<xmax-2) {
               xloc = xloc + 2;
        }
    }

void Linea::mvleft(){
        empty2();
        if(cur_rotation==90 && xloc>2){
            xloc = xloc - 2;
        }
        else if ((cur_rotation == 180 || cur_rotation==0) && xloc>4) {
            xloc = xloc - 2;    
        } else if (cur_rotation == 270 && xloc>0) {
               xloc = xloc - 2;
        }
    }

void Linea::rotation(){
        empty2();
        int rotation_angle= (cur_rotation+90) % 360;
        cur_rotation= rotation_angle;
       
    }

bool Linea::canRotate() {
    	if (cur_rotation == 90 && mvwinch(curwin, yloc + 2, xloc - 2) == ' ' && mvwinch(curwin, yloc + 2, xloc + 2) == ' ' && mvwinch(curwin, yloc + 2, xloc + 4) == ' ') return true;
	else if (cur_rotation == 180 && mvwinch(curwin, yloc, xloc + 2) == ' ' && mvwinch(curwin, yloc + 1, xloc + 2) == ' ' && mvwinch(curwin, yloc + 3, xloc + 2) == ' ') return true;
	else if (cur_rotation == 270 && mvwinch(curwin, yloc + 1, xloc - 2) == ' ' && mvwinch(curwin, yloc + 1, xloc) == ' ' && mvwinch(curwin, yloc + 1, xloc + 4) == ' ') return true;
	else if (cur_rotation == 0 && mvwinch(curwin, yloc, xloc) == ' ' && mvwinch(curwin, yloc + 2, xloc) == ' ' && mvwinch(curwin, yloc + 3, xloc) == ' ') return true;

	return false;
    }

bool Linea::check_horizontal_180() {
    	if ((mvwinch(curwin, yloc + 3, xloc - 2) != ' ') || (mvwinch(curwin, yloc + 3, xloc) != ' ') || (mvwinch(curwin, yloc + 3, xloc + 2) != ' ') || (mvwinch(curwin, yloc + 3, xloc + 4) != ' ')) return true;
	
	return false;
    }

bool Linea::check_horizontal_0() {
    	if ((mvwinch(curwin, yloc + 2, xloc - 2) != ' ') || (mvwinch(curwin, yloc + 2, xloc) != ' ') || (mvwinch(curwin, yloc + 2, xloc + 2) != ' ') || (mvwinch(curwin, yloc + 2, xloc + 4) != ' ')) return true;
	
	return false;
    }

bool Linea::isbottom(){
	 		/*if((cur_rotation == 90 || cur_rotation == 270) && (yloc == dimw_x + 3)) return true;
			else if((cur_rotation == 0 || cur_rotation == 180) && (yloc == dimw_x + 4)) return true;
			else if((cur_rotation == 90 || cur_rotation == 270) && (mvwinch(curwin, yloc + 4, xloc) != ' ')) return true;
			else if((cur_rotation == 0 || cur_rotation == 180) && (check_horizontal())) return true;*/
	    if (cur_rotation == 90 && mvwinch(curwin, yloc + 4, xloc) != ' ') return true;
	    else if (cur_rotation == 180 && check_horizontal_180()) return true;
	    else if (cur_rotation == 270 && mvwinch(curwin, yloc + 4, xloc + 2) != ' ') return true;
	    else if (cur_rotation == 0 && check_horizontal_0()) return true;
	    
	    return false;
	 }

bool Linea::leftIsBlocked() {
	if (cur_rotation == 90) {     
		if ((mvwinch(curwin, yloc, xloc - 1) == ' ') && (mvwinch(curwin, yloc + 1, xloc - 1) == ' ') && (mvwinch(curwin, yloc + 2, xloc - 1) == ' ') && (mvwinch(curwin, yloc + 3, xloc - 1) == ' ')) return false;
      	}
	else if (cur_rotation == 180) {
		if (mvwinch(curwin, yloc + 2, xloc - 3) == ' ') return false;
	}
	else if (cur_rotation == 270) {     
		if ((mvwinch(curwin, yloc, xloc + 1) == ' ') && (mvwinch(curwin, yloc + 1, xloc + 1) == ' ') && (mvwinch(curwin, yloc + 2, xloc + 1) == ' ') && (mvwinch(curwin, yloc + 3, xloc + 1) == ' ')) return false;
      	}
	else if (cur_rotation == 0) {
		if (mvwinch(curwin, yloc + 1, xloc - 3) == ' ') return false;
	}

	return true;
     }

bool Linea::rightIsBlocked() {
    	 if (cur_rotation == 90) {     
    		if ((mvwinch(curwin, yloc, xloc + 2) == ' ') && (mvwinch(curwin, yloc + 1, xloc + 2) == ' ') && (mvwinch(curwin, yloc + 2, xloc + 2) == ' ') && (mvwinch(curwin, yloc + 3, xloc + 2) == ' ')) return false;
      	}
	else if (cur_rotation == 180) {
		if (mvwinch(curwin, yloc + 2, xloc + 6) == ' ') return false;
	}
	else if (cur_rotation == 270) {     
    		if ((mvwinch(curwin, yloc, xloc + 4) == ' ') && (mvwinch(curwin, yloc + 1, xloc + 4) == ' ') && (mvwinch(curwin, yloc + 2, xloc + 4) == ' ') && (mvwinch(curwin, yloc + 3, xloc + 4) == ' ')) return false;
      	}
	else if (cur_rotation == 0) {
		if (mvwinch(curwin, yloc + 1, xloc + 6) == ' ') return false;
	}


	return true;

     }

void Linea::display(){
        int y = yloc;
        int x = xloc;
        for (int i = 0; i < L; i++) {
            if(cur_rotation==90){
            if (i % 2 == 0) {
                if (i != 0) {
                    y++;
                    x = xloc;
                }
                mvwaddch(curwin, y, x, '[');
                } else {
                    mvwaddch(curwin, y, x, ']');
                }
                x++;
            }
            else if (cur_rotation == 180) {
                if(i==0) y=y+2, x=x-2;
                if (i%2==0)
                {
                    mvwaddch(curwin, y, x, '[');
                }
                else mvwaddch(curwin, y, x, ']');
                x++;
                
            } else if (cur_rotation == 270) {
                if(i==0){ 
                    x=x+2;
                }
                if (i % 2 == 0) {
                if (i != 0) {
                    y++;
                    x = xloc+2;
                }
                mvwaddch(curwin, y, x, '[');
                } else {
                    mvwaddch(curwin, y, x, ']');
                }
                x++;
            } else if (cur_rotation == 0) {
                if(i==0) y++, x=x-2;
                if (i%2==0)
                {
                    mvwaddch(curwin, y, x, '[');
                }
                else mvwaddch(curwin, y, x, ']');
                x++;
                
            }
        }
    }

void Linea::saveTetramino(){
    		keypad(curwin, false); 
			display();
	 }
    
int Linea::getmv(int choice){
        switch (choice)
        {
         case KEY_DOWN:
            mvdown();
            break;
         case KEY_LEFT:
            mvleft();
            break;
         case KEY_RIGHT:
            mvright();
            break;
         case KEY_UP:
            rotation();
            break;
         default:
            break;
        }
    return choice;
}
