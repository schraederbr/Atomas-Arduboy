// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\a_atomas.ino --output-dir .\build\

#include <Arduboy2.h>
Arduboy2 arduboy;
#include <EEPROM.h>
#include "src/fonts/Font3x5.h"
Font3x5 font3x5 = Font3x5();
#include "src/fonts/Font4x6.h"
Font4x6 font4x6 = Font4x6();

#define EEPROM_START 806
//Should randomly start with 2-6 atoms or something like that
//Also, might want to adjust the max atoms
int maxAtoms = 16;
int prevAtoms[20];
int atoms[20] = {1};
int count = 1;
int oldCount = 0;
bool plusEnabled = true;
int sincePlus = 0;
int turn = 0;
int baseNum = 1;
int range = 4;
int nextNum = 1;
int index = 0;
int frames = 0;
int totalFrames = 60;
int animationCount = 0;
bool inMinus = false;
bool animate = false;
class Node {
  public:
    int data;
    Node *prev;
    Node *next;
};

struct AtomAnimation{
	int num;
	int startX;
	int startY;
	int currentX;
	int currentY;
	int endX;
	int endY;

};

struct SymLine{
    int count;
    int start;
};

void generateAtomNum()
{
	if(turn % 40 == 0){
		baseNum++;
	}
	if(turn % 150 == 0){
		range++;
	}
	nextNum = random(baseNum,baseNum+range);
    if(random(1,10) == 1){
        nextNum = -1;
		sincePlus = 0;
    }
	int lowNums[count];
	int lowNumsCount = 0;
	for(int i = 0; i < count; i++){
		if(atoms[i] < baseNum && atoms[i] != -1 && atoms[i] != -2){
			lowNums[lowNumsCount] = atoms[i];
			lowNumsCount++;
		}
	}
	//This might not be perfect
	if(random(0,count) < lowNumsCount){
		nextNum = lowNums[random(0,lowNumsCount)];
	}

    if(sincePlus > 5){
        nextNum = -1;
        sincePlus = 0;
    }
	if(turn % 20 == 0){
		nextNum = -2;
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

void deepCopyArray(int* source, int* dest, int size) {
  for (int i = 0; i < size; i++) {
    dest[i] = source[i];
  }
}

//This might not work when combining into a single atom
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
	// arduboy.print("I: ");
	// arduboy.print("L:");
	// arduboy.print(leftIndex);
	// arduboy.print(" R:");
	// arduboy.print((i + 1) % count);
	// arduboy.print(" V: ");
	// arduboy.print("L:");
	// arduboy.print(left);
	// arduboy.print(" R:");
	// arduboy.print(right);
	// arduboy.println();

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
        //preCombineAnimate();
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

int calculateScore(int arr[], int size, int reactions, int& z){
	if(size % 2 != 0){
        return 0;
    }
    if(arr[(size/2) - 1] != arr[size/2]){
        return 0;
    }
    if(size < 2){
        return 0;
    }
	reactions++;
	float m = 1 + (0.5 * float(reactions));
	if(reactions == 1){
		z = arr[size/2];
		if(size == 2){
		    z++;
			return floor(m * float(z));
		}
		else{
			for(int i = (size/2) + 1; i < size + 1; i++){
				arr[i-2] = arr[i];
			}
			z = z + 1;
			return floor(m * float(z)) + calculateScore(arr, size - 2, reactions, z);
		}
	}
	else{
		int zo = arr[size/2];
		int subScore = floor(m * float(z + 1));
		
		int bonus = 2.0 * m * float(zo - z + 1);
		if(zo >= z){
			subScore += bonus;
		}
		//cout << "R: " << reactions << " subScore: " << subScore << "\n";
		if(zo < z){
			z = z + 1;
		}
		else{
			z = zo + 2;
		}
		for(int i = (size/2) + 1; i < size + 1; i++){
			arr[i-2] = arr[i];
		}
		return subScore + calculateScore(arr, size - 2, reactions, z);
	}
}

void evaluatePlus(int atoms[]){
	//This is really janky, but it might work perfectly. It runs through the atoms a bunch of time. 
	//May need to adjust the count multiplier
	for(int i = 0; i < count * 10; i++){
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

void saveScore(){
    int highScore = EEPROM.read(EEPROM_START);
    if(turn > highScore){
        EEPROM.update(EEPROM_START, turn);
    }
}

