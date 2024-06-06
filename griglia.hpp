#include <ncurses.h> 

//crea la griglia
void create_griglia(){
    WINDOW* griglia=newwin(40, 32, 5, 50);
    WINDOW *gamestat = newwin( 20 , 26 , 10, 90);
    box(griglia, 0,0);
    box(gamestat, 0,0);
    wrefresh(griglia);
    wrefresh(gamestat);
}