//Jonathan Holmes (crait)
//November 1st, 2016
//Moving Character Demo
#include <Arduboy2.h>
Arduboy2 arduboy;
// -1 is a plus
int count = 8;
int atoms[50] = {1,2,3,-1,3,1,2,2}

int addAtoms(int left, int middle, int right){
    if(left != right){
        return 0;
    }
    if(middle < 1){
        if(left == right){
            return left + 1;
        }
    }
    if(left > middle){
        return left + 2;
    }
    if(left <= middle){
        return left + 1;
    }
}


void calculatePlus(int[] atoms, int i) {
    if(atoms[i] == -1) {
        atoms[i] = atoms[i-1] + atoms[i+1];
        atoms[i-1] = 0;
        atoms[i+1] = 0;
    }
}


void setup() {
    arduboy.begin();
    arduboy.clear();
}

void loop() {

  arduboy.clear();
  arduboy.pollButtons();

  arduboy.display();
}