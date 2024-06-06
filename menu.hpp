#include <ncurses.h>
#include "ranking.hpp"
//#include "griglia.hpp"
using namespace std;
struct scelte
{
    char a[20];
};

/*class Game_Menu
{
    protected:
    WINDOW *menuwin;
    Ranking *classifica;
public:
    Game_Menu(int ymax,int xmax, int highlight){
    menuwin= newwin(4, 20, ymax / 2, xmax / 2);
    box(menuwin, 0,0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);
    //int highlight=0;
    scelte o[2]={{" NUOVA PARTITA "},{"  CLASSIFICA  "}};
    int choice;
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
            
            //wclear(menuwin);
            //wrefresh(menuwin);
            //delwin(menuwin);
            classifica= new Ranking(ymax, xmax);
            
        }
        
        
        if (choice == 10  && highlight==0) //10 è il valore di del tasto invio
        {
            wclear(menuwin);
            wrefresh(menuwin);
            delwin(menuwin);
            break;
        }
       
        
    }
    }


};
*/
void create_menu(int  ymax,int xmax, int &highlight, int &choice){

    WINDOW *menu= newwin(4, 20, ymax/2, xmax/2);
    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);


    //int highlight=0;
    //int choice;
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
        if (highlight==1 && choice==10)
        {
            wclear(menu);
            wrefresh(menu);
            delwin(menu);
            //create_ranking(ymax, xmax);
            break;
        }
        
        if (choice == 10 && highlight==0) //10 è il valore di del tasto invio
        {
            wclear(menu);
            wrefresh(menu);
            delwin(menu);
            break;
        }
        
    }
    //create_griglia();
    //getch();
}



