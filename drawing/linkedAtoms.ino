// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\calculations.ino --output-dir ./
#include "DoublyLinkedList.h"
#include <Arduboy2.h>


extern int count;
extern int atoms[];
DoublyLinkedList list;

void evaluateAtoms(DoublyLinkedList l){
    Node* current = l.head;
    int steps = 0;
    while(current->data != -1){
        current = current->next;
        steps++;
        if(steps > count){
            return;
        }
    }
    if(current->data != -1){
        //This should never happen
    }
    evaluatePlus(l, current);

}

void evaluatePlus(DoublyLinkedList l, Node* current){
    if(current->prev->data == current->next->data){
        current->data = current->prev->data + 1;
        current->prev->data = 0;
        current->next->data = 0;
    }
}

void deleteZeros(DoublyLinkedList l, int steps){
    Node* current = l.head;
    while(steps < count){
        steps++;
        Node* nextNode = current->next;
        if(current->data == 0){
            l.removeNode(current);
            count--;
            steps--;
            deleteZeros(l, steps);
        }  
        current = nextNode;
        
    }
    
}

void setup() {
    arduboy.begin();
    arduboy.clear();
    //Print all atoms with a for loop
    arduboy.print(count);
    arduboy.print(":");
    for(int i = 0; i < count; i++){
        list.addNode(atoms[i]);
    }
    list.printList();
    evaluateAtoms(list);
    list.printList();
    deleteZeros(list, 0);
    list.printList();
    arduboy.display();
}

void loop() {

}