#include <cstring>
#include <ncurses.h>
#include <iostream>
#include <ctime>

using namespace std;

#define R 2
#define C 4
#define L 8

const int dimw_y=40;
const int dimw_x=32;
const int y_start_w=5;
const int x_start_w=20;

class Tetramini
{
protected:
	 int xloc, yloc, xmax, ymax;
public:
	 int cur_rotation;
	 int choice;
    WINDOW *curwin;  //devo poterci accedere nel main

    Tetramini(){
	 	  curwin = newwin(dimw_y, dimw_x, y_start_w, x_start_w);
		  //getmaxyx(curwin,ymax,xmax);
    }

    void mvdown(){
        yloc++;

    }

    void mvleft()
    {
        xloc = xloc - 2;
    }

    void mvright()
    {
        xloc = xloc + 2;
    }

    void rotation(){

    }

	 void saveTetramino();

    int getmv(){
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

    void empty2(){
        int y=yloc;
        int x=xloc;
        for (int i = 0; i < L; i++)
        {
        if(cur_rotation==90){        //
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

    void empty1(){
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

	void display();
};



class Quadrato : public Tetramini{
    protected:
    public:
    Quadrato( WINDOW *win , int y, int x){
	 	  curwin = win;
        keypad(curwin, true);
        getmaxyx(curwin,ymax,xmax);
        yloc=y;
        xloc=x;
        display();
    };

    void mvdown(){
        empty1();
        if (yloc<ymax-3) yloc++;
    }

    void mvleft(){
        empty1();
        if(xloc>2) xloc = xloc - 2;
    }

    void mvright(){
        empty1();
        if(xloc< xmax-6) xloc = xloc + 2;
    }

    int getmv(int choice){
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
    
    void display(){
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

    bool isbottom(){
	 	   if(yloc == dimw_x + 5) return true; 
		   else if ((mvwinch(curwin, yloc + 2, xloc) != ' ') || (mvwinch(curwin, yloc + 2, xloc + 2) != ' ')) return true;
		   else	return false;
	 }

    bool leftIsBlocked() {
    	if ((mvwinch(curwin, yloc, xloc - 2) == ' ') && (mvwinch(curwin, yloc + 1, xloc - 2) == ' ')) return false;
	return true;
    }

     bool rightIsBlocked() {
    	if ((mvwinch(curwin, yloc, xloc + 4) == ' ') && (mvwinch(curwin, yloc + 1, xloc + 4) == ' ')) return false;
	return true;
    }


	 void saveTetramino(){
			keypad(curwin , false);
			display();
	 }
};

class Linea : public Tetramini{
    protected:
	 int flag_rot;       //flag che indica lo stato della rotazione 
    public:
    Linea (WINDOW *win,int y, int x){
        curwin=win;
        keypad(curwin, true);
        getmaxyx(curwin,ymax,xmax);
        yloc=y;
        xloc=x;
        cur_rotation=90;
        display();
    }
    
    void mvdown(){
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

    void mvright(){
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

     void mvleft(){
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

    void rotation(){
        empty2();
        int rotation_angle= (cur_rotation+90) % 360;
        cur_rotation= rotation_angle;
       
    }

    bool canRotate() {
    	if (cur_rotation == 90 && mvwinch(curwin, yloc + 2, xloc - 2) == ' ' && mvwinch(curwin, yloc + 2, xloc + 2) == ' ' && mvwinch(curwin, yloc + 2, xloc + 4) == ' ') return true;
	else if (cur_rotation == 180 && mvwinch(curwin, yloc, xloc + 2) == ' ' && mvwinch(curwin, yloc + 1, xloc + 2) == ' ' && mvwinch(curwin, yloc + 3, xloc + 2) == ' ') return true;
	else if (cur_rotation == 270 && mvwinch(curwin, yloc + 1, xloc - 2) == ' ' && mvwinch(curwin, yloc + 1, xloc) == ' ' && mvwinch(curwin, yloc + 1, xloc + 4) == ' ') return true;
	else if (cur_rotation == 0 && mvwinch(curwin, yloc, xloc) == ' ' && mvwinch(curwin, yloc + 2, xloc) == ' ' && mvwinch(curwin, yloc + 3, xloc) == ' ') return true;

	return false;
    }

    bool checkBotLine() {
        bool c = false;
	
    	for (int i = 0; i < dimw_x, i++) {
		if (mvwinch(curwin, dimw_y, i) == ' ' ) {
			c = false;
			break;
		}
		else {
			c = true;
		}
	}

	return c;
    }

    bool check_horizontal_180() {
    	if ((mvwinch(curwin, yloc + 3, xloc - 2) != ' ') || (mvwinch(curwin, yloc + 3, xloc) != ' ') || (mvwinch(curwin, yloc + 3, xloc + 2) != ' ') || (mvwinch(curwin, yloc + 3, xloc + 4) != ' ')) return true;
	
	return false;
    }
    bool check_horizontal_0() {
    	if ((mvwinch(curwin, yloc + 2, xloc - 2) != ' ') || (mvwinch(curwin, yloc + 2, xloc) != ' ') || (mvwinch(curwin, yloc + 2, xloc + 2) != ' ') || (mvwinch(curwin, yloc + 2, xloc + 4) != ' ')) return true;
	
	return false;
    }
    bool isbottom(){
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

     bool leftIsBlocked() {
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

     bool rightIsBlocked() {
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


       void display(){
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
    }; 

	 void saveTetramino(){
    		keypad(curwin, false); 
			display();
	 }
    
    int getmv(int choice){
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
};
