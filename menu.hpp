#include <ncurses.h>
#include "file.hpp"
using namespace std;
struct scelte
{
    char a[20];
};

class Game_Menu
{
    protected:
    WINDOW *menuwin;
public:
    Game_Menu(int ymax,int xmax){
    menuwin= newwin(4, 20, ymax / 2, xmax / 2);
    box(menuwin, 0,0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);

     int highlight=0;
    int choice;
    scelte o[2]={{" NUOVA PARTITA "},{"  CLASSIFICA  "}};
    
    wrefresh(menuwin);

    while (1)
    {
       
        for(int i = 0; i < 2; i++)
        {
            //vogliamo evidenziare cosa stiamo facendo ora
            if (i == highlight)
            {
                //attron per una specifica finestra
                wattron(menuwin, A_STANDOUT);
            }
            mvwprintw(menuwin,i+1, 3, o[i].a);
            
            wattroff(menuwin,A_STANDOUT);
        }
        
        choice=wgetch(menuwin);

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
        if (highlight== 1 & choice == 10)
        {
            ranking();
        }
        if (choice== 'q'){
            delwin(menuwin);
            clear();
        }
        
        if (choice == 10) //10 è il valore di del tasto invio
        {
           break;
        }
        
    }
    }


};





