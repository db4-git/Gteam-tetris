#include <iostream>
using namespace std;

struct node {
  int val;
  node* next;
};

typedef node* plist;

void saveData(int points);
void loadData();
