#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

class Node {
  public:
    int data;
    Node *prev;
    Node *next;
};

class DoublyLinkedList {
  public:
    DoublyLinkedList();
    void addNode(int value);
    void removeNode(Node *node);
    //void processList();
    void printList();
    Node *head;
    Node *tail;
};

#endif // DOUBLY_LINKED_LIST_H