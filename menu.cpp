#include <ncurses.h>
using namespace std;
struct scelte
{
    char a[20];
};


int main(int argc, char ** argv){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);


    WINDOW *menu= newwin(4, 20, maxy/2, maxx/2);
    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);


    int highlight=0;
    int choice;
    scelte o[2]={{" NUOVA PARTITA "},{"  CLASSIFICA  "}};
    
    wrefresh(menu);

    while (1)
    {
       
        for(int i = 0; i < 2; i++)
        {
            //vogliamo evidenziare cosa stiamo facendo ora
            if (i == highlight)
            {
                //attron per una specifica finestra
                wattron(menu, A_STANDOUT);
            }
            mvwprintw(menu,i+1, 3, o[i].a);
            
            wattroff(menu,A_STANDOUT);
        }
        
        choice=wgetch(menu);

        switch (choice)
        {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                {
                    highlight=1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight==2)
                {
                    highlight=0;
                }
                break;
            default:
                break;
        }
        if (choice == 10) //10 è il valore di del tasto invio
        {
           break;
        }
        
    }
    
    endwin();

}