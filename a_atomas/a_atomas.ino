// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\a_atomas.ino --output-dir .\build\

#include <Arduboy2.h>
#include <EEPROM.h>
Arduboy2 arduboy;
//This is just after the EEPROM claimed by the LATE multi game.
#define EEPROM_START 848
#define MAX_ARRAY_SIZE 20
//Should randomly start with 2-6 atoms or something like that
int prevAtoms[MAX_ARRAY_SIZE];
int atoms[MAX_ARRAY_SIZE] = {4,2,2,2,2,4,2,-1,2};;
int scoreAtoms[MAX_ARRAY_SIZE];
int scoreAtomsCount = 0;
int count = 9;
int oldCount = 0;
bool plusEnabled = true;
int sincePlus = 0;
int turn = 0;
int currentScore = 0;
int baseNum = 1;
int range = 4;
int nextNum = -1;
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

//This is currently broken
//int getPlusSymmetry(int arr[], int len, int i, int &start, int &end){
//     if(arr[i] != -1 || len < 3){
//         return 0;
//     }
//     start = i - 1 < 0 ? len -1 : i - 1; // use length-1 (last item), if next start position is out of bounds
//     end = i + 1 >= len ? 0 : i + 1; // use 0 (first item), if next end position is out of bounds

//     if(arr[start] != arr[end]){
//         return 0;
//     }
//     int counter = 0;
//     while(arr[(start + len - 1) % len] == arr[(end + 1) % len] && counter < len){
//         start = (start + len - 1) % len; // use mod to circle back to end if out of bounds
//         end = (end + 1) % len; // use mod to circle back to start if out of bounds
//         counter++;
//     }
//     return counter;
// }

//Rewrite this make it recursive or just do it yourself, don't trust GPT-4
int getPlusSymmetry(int arr[], int len, int i, int &start, int &end){
	
}

// void deleteSubArrayCircular(int arr[], int& size, int start, int end) {
//     if (start < 0 || end >= size || size <= 0) {
//         return;
//     }

//     if (start <= end) {
//         int deleteCount = end - start + 1;
//         for(int i = start; i < size - deleteCount; ++i) {
//             arr[i] = arr[i + deleteCount];
//         }
//         size -= deleteCount;
//     } else {
//         int deleteCount1 = size - start;
//         int deleteCount2 = end + 1;

//         // Shift Elements
//         for (int i = 0; i < deleteCount2; ++i) {
//             arr[i] = arr[i + (deleteCount1 + deleteCount2)];
//         }
//         for (int i = deleteCount2; i < size - (deleteCount1 + deleteCount2); ++i) {
//             arr[i] = arr[i + deleteCount1];
//         }
//         size -= (deleteCount1 + deleteCount2);
//     }
// }

// void subsetArrayCircular(int arr[], int size, int start, int end, int outArr[], int& outSize) {
//     int idx = 0; 
//     if (start > end) {
//         // Starting from start position, loop through array to the first element
//         for (int i = start; i < size; i++) {
//             outArr[idx] = arr[i];
//             idx++;
//         }
//         // Continue from the last element back to end position
//         for (int i = 0; i <= end; i++) {
//             outArr[idx] = arr[i];
//             idx++;
//         }
//     }
//     // Handle the case when start argument is less than or equal to end argument
//     else {
//         // Loop through the array from start position to end position
//         for (int i = start; i <= end; i++) {
//             outArr[idx] = arr[i];
//             idx++;
//         }
//     }
//     outSize = idx;
// }

// void add(int atoms[], int i){
// 	arduboy.clear();
// 	int s, e;
// 	bool hasSymmetry = getPlusSymmetry(atoms, count, i, s, e);
// 	if(hasSymmetry == false){
// 		return;
// 	}
// 	int middleAtom = 0;
// 	int subAtoms[20];
// 	int subAtomsSize = 0;
// 	subsetArrayCircular(atoms, count, s, e, subAtoms, subAtomsSize);
// 	int addedScore = calculateScore(subAtoms, subAtomsSize, 0, middleAtom);
// 	currentScore += addedScore;
// 	printArray(subAtoms, subAtomsSize);

// 	deleteSubArrayCircular(atoms, count, e, s);
// 	printArray(atoms,count);
// 	arduboy.display();
// 	while(true){

// 	}
// }

//This might not work when combining into a single atom
// void add(int atoms[], int i){
//     if(count < 3){
//         return;
//     }
// 	int leftIndex = (i - 1) % count;
// 	if(i - 1 < 0 ){
// 		leftIndex = i - 1 + count;
// 	}
	
// 	int left = atoms[leftIndex];
// 	int right = atoms[((i + 1) % count)];

// 	if(left == right && (left != -1 || right != -1)){
// 		if(atoms[i % count] == -1){
// 			atoms[i % count] = left + 1;
// 		}
// 		else{
// 			if(left > atoms[i % count]){
// 				atoms[i % count] = left + 2;
// 			}
// 			else{
// 				atoms[i % count]++;
// 			}
// 		}
// 		atoms[leftIndex] = 0;
// 		atoms[(i + 1) % count] = 9;
//         //preCombineAnimate();
// 		if(i == 0){
// 			deleteAtIndex(atoms, 1);
// 			deleteAtIndex(atoms, count - 1);
// 			if(count > 2){
// 				printArray(atoms);
// 				add(atoms, 0);
// 			}
// 		}
// 		else{
// 			deleteAtIndex(atoms, (i + 1) % count);
// 			if(i == count){
// 				deleteAtIndex(atoms, (i - 2) % count);
// 			}
// 			else{
// 				deleteAtIndex(atoms, (i - 1) % count);
// 			}
// 			//This if might not quite be right
// 			if(count > 2){
// 				printArray(atoms);
// 				add(atoms, ((i - 1) % count));
// 			}
// 		}
// 	}
// }

//does this have a problem?
void addAtom(int i, int num)
{
	turn++;
	i = i % count;
	addAtIndex(i, num);
	// for (int j = count - 1; j > i; j--)
	// {
	// 	atoms[j] = atoms[j - 1];
	// }
	// atoms[i] = num;
	if(plusEnabled){
		addThings();
		//evaluatePlus(atoms);
	}
}

void deleteAtIndex(int atoms[], int index) {
    index = index % count;
    for (int i = index; i < count - 1; ++i) {
        atoms[i] = atoms[i + 1];
    }
    count--;
}

void deleteAtIndex(int atoms[], int& c, int index) {
    index = index % c;
    for (int i = index; i < c - 1; ++i) {
        atoms[i] = atoms[i + 1];
    }
    c--;
}

// void deleteAllPluses(int arr[], int& size) {
//     int newIdx = 0;
//     for (int oldIdx = 0; oldIdx < size; ++oldIdx) {
//         if (arr[oldIdx] != -1) {
//             arr[newIdx] = arr[oldIdx];
//             ++newIdx;
//         }
//     }
//     size = newIdx;
// }

// void evaluatePlus(int atoms[]){
// 	//This is really janky, but it might be fine. It runs through the atoms a bunch of time. 
// 	//May want to adjust the count multiplier
// 	for(int i = 0; i < count * 10; i++){
// 		if(atoms[i % count] == -1){
// 			//Attempted score calculation. But this doesn't quite work
// 			// int s, e;
// 			// bool hasSymmetry = getPlusSymmetry(atoms, count, i, s, e);
// 			// int middleAtom = 0;
// 			// int subAtoms[20];
// 			// int subAtomsSize = 0;
// 			// subsetArrayCircular(atoms, count, s, e, subAtoms, subAtomsSize);
// 			// deleteAllPluses(subAtoms, subAtomsSize);
// 			// int addedScore = calculateScore(subAtoms, subAtomsSize, 0, middleAtom);
// 			// currentScore += addedScore;
// 			// // arduboy.clear();
// 			// // printArray(atoms,count);
// 			// // printArray(subAtoms,subAtomsSize);
// 			// // arduboy.display();
// 			// // arduboy.delayShort(20000);
// 			add(atoms, i % count);
				

// 		}
// 	}
// }

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

int calculateCircularDistance(int start, int end, int length) {
  if(start == end) 
    return 0;
  else if (start < end) 
    return (end - start == 1) ? length + 1 : (end - start) + 1;
  else
    return (start - end == 1) ? length + 1 : (length - start + end) + 1;
}
//The final z value is the final value of the combined atoms
//That might be useful to simplify my add function
//Takes in a symmetrical array
void addThings(){
	arduboy.clear();
	printArray(atoms);
	while(hasPlus(atoms)){
		int i = 0;
		for(; i < count; i++){
			if(atoms[i] == -1){
				break;
			}
		}
		if(atoms[i] == -1){
			int start, end;
			//This width probably isn't correct
			int width;
			getPlusSymmetry(atoms, count, i, start, end);
            width = calculateCircularDistance(start, end, count);
			int endMiddle = deleteSymmetry(i, width);
			int outAtom;
			int subScore = calculateScore(scoreAtoms, scoreAtomsCount, 0, outAtom);
			currentScore += subScore;
			
			
			addAtIndex(endMiddle, outAtom);
		}
	}
	printArray(atoms);
	arduboy.display();
	arduboy.delayShort(3000);
}

int deleteSymmetry(int center, int width){
    //printArray(atoms);
    //addAtIndex(0, atoms[center]);
	deleteAtIndex(atoms, count, center);
	//printArray(atoms);
	scoreAtomsCount = 0;
	for(int i = 0; i < width/2; i++){
	    center--;
	    addScoreAtoms(0, atoms[center]);
        deleteAtIndex(atoms, count, center);
        //printArray(atoms);
        addScoreAtoms(scoreAtomsCount, atoms[center]);
        deleteAtIndex(atoms, count, center);
        //printArray(atoms);
	}
	return center;
}

void addAtIndex(int index, int value) {
    if(index <  MAX_ARRAY_SIZE && index >= 0) {
        // shift elements to the right of the index to make space
        for (int i =  MAX_ARRAY_SIZE-1; i > index; i--) {
            atoms[i] = atoms[i - 1];
        }
        // insert new value
        atoms[index] = value;
        count++;
    }
}

void addScoreAtoms(int index, int value){
    if(index <  MAX_ARRAY_SIZE && index >= 0) {
        // shift elements to the right of the index to make space
        for (int i =  MAX_ARRAY_SIZE-1; i > index; i--) {
            scoreAtoms[i] = scoreAtoms[i - 1];
        }
        // insert new value
        scoreAtoms[index] = value;
        scoreAtomsCount++;
    }
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

void saveScore(){
    // int highScore = EEPROM.read(EEPROM_START);
    // if(currentScore > highScore){
    //     EEPROM.update(EEPROM_START, currentScore);
    // }
}

