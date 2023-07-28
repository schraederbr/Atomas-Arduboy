// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\a_atomas.ino --output-dir .\build\

#include <Arduboy2.h>
#include <EEPROM.h>
Arduboy2 arduboy;
//This is just after the EEPROM claimed by the LATE multi game.
#define EEPROM_START 848

//Should randomly start with 2-6 atoms or something like that
int prevAtoms[20];
int atoms[20] = {3,5,5,3};
int count = 4;
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

void evaluatePlus(int atoms[]){
	//This is really janky, but it might be fine. It runs through the atoms a bunch of time. 
	//May want to adjust the count multiplier
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


//Based off: 
//Score
//Sr = floor(M * (Z + 1))
//Bonus
//B = 2 * M * (Zo - Z + 1)
//score = Sr       if Zo < Z
//        Sr + B   if Zo >= Z
//Assume even number of atoms
//Needs the recursive part and probably needs to cut the array
int calculateScore(int arr[], int size, int reactions, int prevAtom, int tempScore){
    if(size % 2 != 0){
        return 0;
    }
    if(arr[(size/2) - 1] != arr[size/2]){
        return 0;
    }
    //Multiplier
    reactions++;
    float m = 1f + (0.5 * float(reactions))
    int middleAtom = arr[size/2];
    int score = floor(1.5 * float(middleAtom + 1));
    int bonus = 2 * m * (middleAtom - prevAtom + 1);
    if(prevAtom == 0){
        bonus = 0;
    }
    if(middleAtom > prevAtom){
        score += bonus;
    }
    if(size == 2){
        return score;
    }
    else{

    }
    



}

void saveScore(){
    int highScore = EEPROM.read(EEPROM_START);
    if(turn > highScore){
        EEPROM.update(EEPROM_START, turn);
    }
}

