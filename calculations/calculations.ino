#include <Arduboy2.h>
Arduboy2 arduboy;
// -1 is a plus
int count = 8;
//Need some way to make this array wrap around
//Maybe I can just make it big and use modulo some how

int atoms[50] = {1,2,3,-1,3,1,2,2};

//Stands for get index
int gi(int i){
    return i % count;
}

int addAtoms(int left, int middle, int right){
    if(left != right){
        return 0;
    }
    //encountered a plus, or empty
    if(middle < 1){
        return left + 1;
    }
    if(left > middle){
        return left + 2;
    }
    if(left <= middle){
        return middle + 1;
    }
    return 0; //should never get here
}

void calculatePlus(int atoms[], int i) {
    int left = atoms[gi(i-1)];
    int middle = atoms[gi(i)];
    int right = atoms[gi(i+1)];
    atoms[gi(i)] = addAtoms(left, middle, right);
}

void calculateTurn(int atoms[]){
    for(int i = 0; i < count; i++){
        if(atoms[i] == -1){
            calculatePlus(atoms, i);
        }
    }
}

void setup() {
    arduboy.begin();
    arduboy.clear();
    //Print all atoms with a for loop
    arduboy.print("Atoms: ");
    for(int i = 0; i < count; i++){
        arduboy.print(atoms[i]);
    }
    arduboy.display();
}

void loop() {

  
}