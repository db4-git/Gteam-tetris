#include "menu.hpp"

void create_menu(int  ymax,int xmax, int &highlight, int &choice){

    WINDOW *menu= newwin(4, 20, ymax/2, xmax/2);
    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);


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

        switch (choice)  //cambia highlight in base alle frecciette
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
        
        //esce dal ciclo elimina la finestra del menu
        if (choice == 10) //10 è il valore di del tasto invio
        {
            wclear(menu);
            wrefresh(menu);
            delwin(menu);
            break;
        }
        
    }
   
}


