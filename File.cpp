#include <iostream>
#include <fstream>
using namespace std;

#include "file.hpp"

void save_data(int points) {
  ofstream file;
  file.open("classifica.txt", ios::app);

  file << points;
  file.close();
}

void load_data() {
  ifstream file;
  file.open("classifica.txt");
  int points;
  plist head = NULL;
  
  while (file >> points) {
    addNode(points);
  }
}

plist addNode(int points) {
  if (head == NULL) {
    head = new node;
    head->val = value;
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
