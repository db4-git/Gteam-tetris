#include <cstring>
#include <ncurses.h>
#include <iostream>
#include <ctime>

using namespace std;

#define R 2
#define C 4
#define L 8

const int dimw_y=45;
const int dimw_x=32;
const int y_start_w=5;
const int x_start_w=20;

class Tetramini
{
protected:
    // XY pezzo[4];
	 int xloc, yloc, xmax, ymax;
    int cur_rotation;
public:
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
        xloc--;
    }

    void mvright()
    {
        xloc++;
    }

    void rotation(){

    }

    int getmv(){
        int choice = wgetch(curwin);
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

    void empty2(){
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
            }
            else if (cur_rotation == 180) {
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
            } else if (cur_rotation == 0) {
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

   /* void get_tetram(){
        srand(time(0));
        int a= rand()%2;
        if (a==0)
        {
            Quadrato(curwin, 0,5);
        }
        else Linea (curwin, 0,6);
    }*/
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
        if(xloc>1) xloc--;
    }

    void mvright(){
        empty1();
        if(xloc< xmax-5) xloc++;;
    }

    int getmv(){
        int choice = wgetch(curwin);
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


};

class Linea : public Tetramini{
    protected:
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
        if(cur_rotation==90 && xloc<xmax-3){
            xloc++;
        }
        else if ((cur_rotation == 180 || cur_rotation==0) && xloc<xmax-7) {
            xloc++;    
        } else if (cur_rotation == 270 && xloc<xmax-5) {
               xloc++;
        }
    }

     void mvleft(){
        empty2();
        if(cur_rotation==90 && xloc>1){
            xloc--;
        }
        else if ((cur_rotation == 180 || cur_rotation==0) && xloc>3) {
            xloc--;    
        } else if (cur_rotation == 270 && xloc>-1) {
               xloc--;
        }
    }

    void rotation(){
        empty2();
        int rotation_angle= (cur_rotation+90) % 360;
        cur_rotation= rotation_angle;
       
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
    
    int getmv(){
        int choice = wgetch(curwin);
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
