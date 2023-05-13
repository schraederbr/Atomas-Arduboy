// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\calculations.ino --output-dir ./
//#include "DoublyLinkedList.h"
#include <Arduboy2.h>

extern int count;
extern int atoms[];


Node* insertNode(Node* current, int value){
    Node* newNode = new Node();
    newNode->data = value;
    newNode->prev = current;
    newNode->next = current->next;
    current->next->prev = newNode;
    current->next = newNode;
    return newNode;
}

void removeNode(Node* current){
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
}

void printNodes(Node* current){
    printNodes(current, count);
}

void printNodes(Node* current, int count){
    arduboy.print(count);
    arduboy.print(": ");
    for(int i = 0; i < count; i++){
        arduboy.print(current->data);
        current = current->next;
    }
    arduboy.println();
}

void nodesToArray(int as[], int count, Node* current){
    for(int i = 0; i < count; i++){
        as[i] = current->data;
        current = current->next;
    }
}

void arrayToNodes(int as[], int count, Node* current){
    current->data = atoms[0];
    current->prev = current;
    current->next = current;
    for(int i = 1; i < count; i++){
        insertNode(current, atoms[i]);
    }
}

