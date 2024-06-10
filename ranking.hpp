#include <iostream>
#include <cstring>
#include <ncurses.h>
#include <ctime>
#include <fstream>
using namespace std;
struct node {
  int val;
  node* next;
};


typedef node* plist;

plist addNode(int points, plist head);
  

void save_data(int points);

plist load_data(plist head);
  
void create_ranking(int ymax,int xmax, int &a);