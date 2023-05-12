//Use this to get hex file:
//arduino-cli compile --fqbn arduboy:avr:arduboy .\calculations.ino --output-dir ./

#include <Arduboy2.h>
Arduboy2 arduboy;
// -1 is a plus
int count = 8;
//Need some way to make this array wrap around
//Maybe I can just make it big and use modulo some how

int atoms[50] = {1,2,3,-1,3,2,1,2};

void moveElements(int arr[], int n, int start, int moveBy) {
    if (moveBy >= 0) {
        for (int i = n - 1; i >= start; i--) {
            arr[i + moveBy] = arr[i];
        }
    } else {
        for (int i = start; i < n; i++) {
            arr[i + moveBy] = arr[i];
        }
    }
}


//Stands for get index
int gi(int i){
    return i % count;
}

void recAdd(int as[], int i){
    if(as[gi(i - 1)] != as[gi(i + 1)]){
        return;
    }
    as[gi(i-1)] = as[gi(i-1)] + 1;
    as[gi(i)] = 0;
    as[gi(i+1)] = 0;
    // for(int tempi = gi(i + 1); tempi < count - 2; tempi++){
    //     as[gi(tempi+1)] = as[gi(tempi+3)];
    // }
    //count = count - 2;
    moveElements(as, count, gi(i + 2), -2);
    count = count - 2;
    printArray(as);
    recAdd(as, i - 1);
}

void printArray(int as[]){
    arduboy.print(count);
    arduboy.print(" Atoms: ");
    for(int i = 0; i < count; i++){
        arduboy.print(as[i]);
    }
    arduboy.print("\n");
}

int addAtoms(int left, int middle, int right){
    if(left != right){
        return middle;
    }
    //encountered a plus
    if(middle == -1){
        
        return left + 1;
        count = count - 2;
    }
    // if(left > middle){
    //     return left + 2;
    // }
    // if(left <= middle){
    //     return middle + 1;
    // }
    return 0; //should never get here
}

void calculatePlus(int atoms[], int i) {
    int left = atoms[gi(i-1)];
    int middle = atoms[gi(i)];
    int right = atoms[gi(i+1)];
    atoms[gi(i)] = addAtoms(left, middle, right);
}

void calculateTurn(int atoms[], int i){
    if(i > count){
        return;
    }
    for(i; i < count; i++){
        if(atoms[i] == -1){
            calculatePlus(atoms, i);
            calculateTurn(atoms, i);
        }
    }
}

void setup() {
    arduboy.begin();
    arduboy.clear();
    //Print all atoms with a for loop
    arduboy.print(count);
    arduboy.print(" Atoms: ");
    for(int i = 0; i < count; i++){
        arduboy.print(atoms[i]);
    }
    arduboy.print("\n");
    recAdd(atoms, 3);
    // arduboy.print("\n");
    // arduboy.print(count);
    // arduboy.print(" Atoms: ");
    // for(int i = 0; i < count; i++){
    //     arduboy.print(atoms[i]);
    // }
    // calculateTurn(atoms, 0);
    // arduboy.print("Atoms: ");
    // for(int i = 0; i < count; i++){
    //     arduboy.print(atoms[i]);
    // }
    arduboy.display();
}

void loop() {

  
}