#include <iostream>
#include <fstream>
#include <ncurses.h>

using namespace std;

struct node {
	int val;
	node* next;
};

typedef node* plist;

plist addNode(int points, plist head) {
  if (head == NULL) {
    head = new node;
    head->val = points;
    head->next = NULL;
    return head;
  }

  bool added = false;
  plist curr = head;

  while (!added && curr != NULL) {
    if (curr->val < points) {
      plist tmp = curr->next;
      curr->next = new node;
      (curr->next)->val = points;
      (curr->next)->next = tmp;
      added = true;
    }

    curr = curr->next;
  }

  if (!added) {
    plist n = new node;
    n->val = points;
    n->next = head;
    head = n;
  }

  return head;
}

void save_data(int points) {
  ofstream file;
  file.open("classifica.txt", ios::app);

  file << points;
  file.close();
}

plist load_data(plist head) {
  ifstream file;
  file.open("classifica.txt");
  int points;
  
  while (file >> points) {
    addNode(points, head);
  }
  return head;
}

int main(int argc, char ** argv){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    plist head = new node;
    head = load_data(head);
    WINDOW *classifica= newwin(21, 30, maxy/4, maxx/4);
    box(classifica, 0,0);
    refresh();
    wrefresh(classifica);
    keypad(classifica, true);
    mvwaddch(classifica, 3, 2, 9);
    int r[9]={1,2,3,4,5,6,7,8,9};
    for (int i = 0; i < 10; i++)  //non funzona segmentation fault
    {                               //dovrebbe inserirmi nell'array i primi 10 puteggi 
      r[i]= head->val;
      head=head->next;
    }
    int e=1;
    int a;
    for (int i = 0; i < 9; i++)    //stampa un elenco di numeri da 1 a 10
      {
        mvwprintw(classifica, e, 2, "%d", r[i]);
        mvwaddch(classifica, e, 3, '.');
        e=e+2;
      }
    mvwprintw(classifica, 19,2, "10");
    mvwaddch(classifica, 19,4, '.');
    do{
      wrefresh(classifica);
      a=wgetch(classifica);
    
    }while (a!=10);
    
    
    endwin();
}
