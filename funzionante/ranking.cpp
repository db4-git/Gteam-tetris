#include "ranking.hpp"

plist addNode(int points, plist head) {
  if (head == NULL) {
    head = new node; 
    head->val = points;
    head->next = NULL;
    return head;
  }

  bool added = false;
  plist curr = head;
  plist prev = NULL;

  while (!added && curr != NULL) {
    if (curr->val <= points) {
      plist tmp = new node;
      tmp->val = points;
      tmp->next = curr;
      if (prev != NULL) prev->next = tmp;
      else head = tmp;
      added = true;
    }
    
    prev = curr;
    curr = curr->next;
  }

  if (!added) {
      plist tmp = new node;
      tmp->val = points;
      tmp->next = curr;
      if (prev != NULL) prev->next = tmp;
      else head = tmp;
  }

  return head;
}

void save_data(int points) {
  ofstream file;
  file.open("classifica.txt", ios::app);

  file << points << endl;
  file.close();
}

plist load_data(plist head) {
  ifstream file;
  file.open("classifica.txt"/*, ios_base::in*/);
  int points;
  
  while (file >> points) {
    head = addNode(points, head);
  }

  return head;
}
  
void create_ranking(int ymax,int xmax, int &a){
plist head =NULL;
      head = load_data(head);
      WINDOW *rank= newwin(21, 30, ymax/4, (xmax-6)/2);
      box(rank, 0,0);
      refresh();
      wrefresh(rank);
      refresh();
      keypad(rank, true);
      mvwaddch(rank, 3, 2, 9);
      int r[9]={1,2,3,4,5,6,7,8,9};
      int i=0;
     
      int e=1;
      //int a;
      for (int i = 0; i < 9; i++)    //stampa un elenco di numeri da 1 a 10
        {
          mvwprintw(rank, e, 2, "%d", r[i]);
          mvwaddch(rank, e, 3, '.');
          e=e+2;
        }
      mvwprintw(rank, 19,2, "10");
      mvwaddch(rank, 19,4, '.');
      e=1;
      
      while(head!=NULL & i<10) //inserisci i primi 10 punteggi in classifica
      {
        mvwprintw(rank, e,6,"%d", head->val);
        head=head->next;
        i++;
        e= e+2;
      }

      do //refresha continuamente e la tiene bloccata a schermo finche non si clicca il tasto 'q'
      {
        wrefresh(rank);
        a=wgetch(rank);
      } while (a!='q');
    
    if (a =='q') //elimina la finestra e la cancella dallo schermo
    {
      wclear(rank);
      wrefresh(rank);
      delwin(rank);
    }

  }
