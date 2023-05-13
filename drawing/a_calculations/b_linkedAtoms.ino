// Use this to get hex file:
// arduino-cli compile --fqbn arduboyB:avr:arduboyB .\calculations.ino --output-dir ./
//#include "DoublyLinkedList.h"
#include <Arduboy2.h>
Arduboy2 arduboyB;

extern int count;
extern int atoms[];
// void evaluateAtoms(DoublyLinkedList l){
//     Node* current = l.head;
//     int steps = 0;
//     while(current->data != -1){
//         current = current->next;
//         steps++;
//         if(steps > count){
//             return;
//         }
//     }
//     if(current->data != -1){
//         //This should never happen
//     }
//     evaluatePlus(l, current);

// }

// void evaluatePlus(DoublyLinkedList l, Node* current){
//     if(current->prev->data == current->next->data){
//         current->data = current->prev->data + 1;
//         current->prev->data = 0;
//         current->next->data = 0;
//     }
// }

// void deleteZeros(DoublyLinkedList l, int steps){
//     Node* current = l.head;
//     while(steps < count){
//         steps++;
//         Node* nextNode = current->next;
//         if(current->data == 0){
//             l.removeNode(current);
//             count--;
//             steps--;
//             deleteZeros(l, steps);
//         }  
//         current = nextNode;
        
//     }
    
// }

//Need to make sure this is circular
Node* insertNode(Node* current, int value){
    Node* newNode = new Node();
    newNode->data = value;
    newNode->prev = current;
    newNode->next = current->next;
    current->next->prev = newNode;
    current->next = newNode;
    return newNode;
}

void printNodes(Node* current){
    printNodes(current, count);
}

void printNodes(Node* current, int count){
    arduboyB.print(count);
    arduboyB.print(": ");
    for(int i = 0; i < count; i++){
        arduboyB.print(current->data);
        current = current->next;
    }
    arduboyB.println();
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
// void setup() {
//     arduboyB.begin();
//     arduboyB.clear();
//     Node* head = new Node();
//     head->data = atoms[0];
//     head->prev = head;
//     head->next = head;
    
//     for(int i = 1; i < count; i++){
//         insertNode(head, atoms[i]);
//     }
    
//     //Print all atoms with a for loop
//     arduboyB.print(count);
//     arduboyB.print(":");
//     printNodes(head);
//     // for(int i = 0; i < count; i++){
//     //     list.addNode(atoms[i]);
//     // }
//     // list.printList();
//     // evaluateAtoms(list);
//     // list.printList();
//     // deleteZeros(list, 0);
//     // list.printList();
//     arduboyB.display();
// }

// void loop() {

// }