#ifndef CircularList_h
#define CircularList_h
#include "Arduino.h"
struct Node {
  int data;
  Node* prev;
  Node* next;
};

class CircularList {
  public:
    CircularList();
    void addNode(int value);
    void removeNode(Node* node);
    void printList();
    int length();
    Node* _head;
    Node* _tail;
};

#endif