#include <ncurses.h>
#include <cstring>
#include <iostream>
#include <ctime>
using namespace std;
struct scelte
{
    char a[20];
};

bool create_menu(int  ymax,int xmax, int &highlight, int &choice);
