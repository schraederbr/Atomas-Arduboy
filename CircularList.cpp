#include "Arduino.h"
#include "CircularList.h"
CircularList::CircularList() {
  _head = NULL;
  _tail = NULL;
}

void CircularList::addNode(int value) {
  Node* newNode = new Node;
  newNode->data = value;

  if (_head == NULL) {
    _head = newNode;
    _tail = newNode;
    newNode->next = _head;
    newNode->prev = _tail;
  } else {
    newNode->prev = _tail;
    newNode->next = _head;
    _tail->next = newNode;
    _head->prev = newNode;
    _tail = newNode;
  }
}

void CircularList::removeNode(Node* node) {
  if (_head == NULL || node == NULL) {
    return;
  }

  if (_head == _tail && _head == node) {
    _head = NULL;
    _tail = NULL;
  } else {
    node->prev->next = node->next;
    node->next->prev = node->prev;

    if (node == _head) {
      _head = node->next;
    }
    if (node == _tail) {
      _tail = node->prev;
    }
  }
  delete node;
}

void CircularList::printList() {
  if (_head == NULL) {
    Serial.println("List is empty.");
    return;
  }

  Node* currentNode = _head;
  do {
    Serial.print(currentNode->data);
    Serial.print(" ");
    currentNode = currentNode->next;
  } while (currentNode != _head);
  Serial.println("");
}

int CircularList::length() {
  if (_head == NULL) {
    return 0;
  }

  int count = 0;
  Node* currentNode = _head;
  do {
    count++;
    currentNode = currentNode->next;
  } while (currentNode != _head);

  return count;
}