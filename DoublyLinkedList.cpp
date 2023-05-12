#include "DoublyLinkedList.h"
#include <Arduboy2.h>
#include <Arduino.h>
Arduboy2 ab;

//Need to make sure this is circularly linked
DoublyLinkedList::DoublyLinkedList() : head(NULL), tail(NULL) {}

void DoublyLinkedList::addNode(int value) {
  Node *newNode = new Node();
  newNode->data = value;
  newNode->next = NULL;
  newNode->prev = NULL;

  if (!head) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
}

void DoublyLinkedList::removeNode(Node *node) {
  if (node->prev) {
    node->prev->next = node->next;
  } else {
    head = node->next;
  }

  if (node->next) {
    node->next->prev = node->prev;
  } else {
    tail = node->prev;
  }

  delete node;
}

// void DoublyLinkedList::processList() {
//   Node *current = head;
//   while (current) {
//     if (current->data == -1 && current->prev && current->next && current->prev->data == current->next->data) {
//       current->data = current->prev->data + 1;
//       Node *tempPrev = current->prev;
//       Node *tempNext = current->next;

//       current->prev = tempPrev->prev;
//       if (tempPrev->prev) {
//         tempPrev->prev->next = current;
//       } else {
//         head = current;
//       }

//       current->next = tempNext->next;
//       if (tempNext->next) {
//         tempNext->next->prev = current;
//       } else {
//         tail = current;
//       }

//       delete tempPrev;
//       delete tempNext;
//     }
//     current = current->next;
//   }
// }

void DoublyLinkedList::printList() {
  Node *current = head;
  while (current) {
    ab.print(current->data);
    ab.print("_");
    current = current->next;
  }
  ab.println();
}