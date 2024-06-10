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

    Tetramini();

    void mvdown();

    void mvleft();

    void mvright();

    void rotation();

	void saveTetramino();

    int getmv();

    void empty2();

    void empty1();

	void display();
};

class Quadrato : public Tetramini{
    protected:
    public:
    Quadrato( WINDOW *win , int y, int x);

    void mvdown();

    void mvleft();

    void mvright();

    int getmv(int choice);
    
    void display();

    bool isbottom();

    bool leftIsBlocked();

     bool rightIsBlocked();

	 void saveTetramino();
};

class Linea : public Tetramini{
    protected: 
    public:
    Linea (WINDOW *win,int y, int x);
    
    void mvdown();

    void mvright();

     void mvleft();

    void rotation();

    bool canRotate();

    bool check_horizontal_180();

    bool check_horizontal_0();

    bool isbottom();

     bool leftIsBlocked();

     bool rightIsBlocked();

    void display(); 

	 void saveTetramino();
    
    int getmv(int choice);
};
