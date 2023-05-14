// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\a_calculations.ino --output-dir .\build\

#include <Arduboy2.h>
Arduboy2 arduboy;
//Broken Maybe:
// extern int atoms[50] = {4,3,2,1,4,3,5,-1,5,4,1,2};
// extern int count = 12;
extern int atoms[50] = {1};
extern int count = 1;
extern bool plusEnabled = true;
extern int sincePlus = 0;
int turn = 0;
int baseNum = 1;
int range = 3;
int nextNum = 1;
extern int index = 0;
class Node {
  public:
    int data;
    Node *prev;
    Node *next;
};


void generateAtomNum()
{
	if(turn % 40 == 0){
		baseNum++;
		range++;
	}
	nextNum = random(baseNum,baseNum+range);
    if(random(1,5) == 1){
        nextNum = -1;
    }
	for(int i = 0; i < count; i++){
		if(atoms[i] < baseNum){
			//Have a change that numbers below basenum will spawn
			//If they are already in the circle
		}
	}
    if(sincePlus > 4){
        nextNum = -1;
        sincePlus = 0;
    }
    sincePlus++;
}

void printArray(int as[])
{
   printArray(as, count);
}

void printArray(int as[], int n)
{
    arduboy.print(n);
    arduboy.print(": ");
    for (int i = 0; i < n; i++)
    {
        arduboy.print(as[i]);
    }
    arduboy.print("\n");
}

void add(int atoms[], int i){
    if(count < 3){
        return;
    }
	int leftIndex = (i - 1) % count;
	if(i - 1 < 0 ){
		leftIndex = i - 1 + count;
	}
	
	int left = atoms[leftIndex];
	int right = atoms[((i + 1) % count)];
	arduboy.print("I: ");
	arduboy.print("L:");
	arduboy.print(leftIndex);
	arduboy.print(" R:");
	arduboy.print((i + 1) % count);
	arduboy.print(" V: ");
	arduboy.print("L:");
	arduboy.print(left);
	arduboy.print(" R:");
	arduboy.print(right);
	arduboy.println();

	if(left == right && (left != -1 || right != -1)){
		if(atoms[i % count] == -1){
			atoms[i % count] = left + 1;
		}
		else{
			if(left > atoms[i % count]){
				atoms[i % count] = left + 2;
			}
			else{
				atoms[i % count]++;
			}
		}
		//This probably isn't perfect deleting is weird. Sometimes have to do i - 1 sometimes i - 2
		atoms[leftIndex] = 0;
		atoms[(i + 1) % count] = 9;
		if(i == 0){
			deleteAtIndex(atoms, 1);
			deleteAtIndex(atoms, count - 1);
			if(count > 2){
				printArray(atoms);
				add(atoms, 0);
			}
		}
		else{
			deleteAtIndex(atoms, (i + 1) % count);
			if(i == count){
				deleteAtIndex(atoms, (i - 2) % count);
			}
			else{
				deleteAtIndex(atoms, (i - 1) % count);
			}
			//This if might not quite be right
			if(count > 2){
				printArray(atoms);
				add(atoms, ((i - 1) % count));
			}
		}
	}
}

void addAtom(int i, int num)
{
	turn++;
	i = i % count;
	count++;
	for (int j = count - 1; j > i; j--)
	{
		atoms[j] = atoms[j - 1];
	}
	atoms[i] = num;
	if(plusEnabled){
		evaluatePlus(atoms);
	}
	
}

void deleteAtIndex(int atoms[], int index) {
    index = index % count;
    for (int i = index; i < count - 1; ++i) {
        atoms[i] = atoms[i + 1];
    }
    count--;
}

void evaluatePlus(int atoms[]){
	//This is really janky, but it might work perfectly. It runs through the atoms a bunch of time. 
	for(int i = 0; i < count * 4; i++){
		if(atoms[i % count] == -1){
			add(atoms, i % count);
		}
	}
}

bool hasPlus(int atoms[]){
	return hasPlus(atoms, count);
}

bool hasPlus(int atoms[], int count){
	for(int i = 0; i < count; i++){
		if(atoms[i] == -1){
			return true;
		}
	}
	return false;
}
