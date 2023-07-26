// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\a_atomas.ino --output-dir
// .\build
#include <Arduboy2.h>
#include <Tinyfont.h>

Arduboy2 arduboy;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
// Broken Maybe:
//  extern int atoms[50] = {4,3,2,1,4,3,5,-1,5,4,1,2};
//  extern int count = 12;

char prevAtoms[20];
char atoms[20] = {1};
byte count = 1;
byte oldCount = 0;
bool plusEnabled = true;
byte sincePlus = 0;
int turn = 0;
byte baseNum = 1;
byte range = 4;
char nextNum = 1;
byte index = 0;
byte frames = 0;
byte totalFrames = 60;
byte animationCount = 0;
bool inMinus = false;
bool animate = false;

struct AtomAnimation {
	int num;
	int startX;
	int startY;
	int currentX;
	int currentY;
	int endX;
	int endY;
};

void generateAtomNum() {
	if (turn % 40 == 0) {
		baseNum++;
	}
	if (turn % 150 == 0) {
		range++;
	}
	nextNum = random(baseNum, baseNum + range);
	if (random(1, 10) == 1) {
		nextNum = -1;
		sincePlus = 0;
	}
	int lowNums[count];
	int lowNumsCount = 0;
	for (int i = 0; i < count; i++) {
		if (atoms[i] < baseNum && atoms[i] != -1 && atoms[i] != -2) {
			lowNums[lowNumsCount] = atoms[i];
			lowNumsCount++;
		}
	}
	// This might not be perfect
	if (random(0, count) < lowNumsCount) {
		nextNum = lowNums[random(0, lowNumsCount)];
	}

	if (sincePlus > 5) {
		nextNum = -1;
		sincePlus = 0;
	}
	if (turn % 20 == 0) {
		nextNum = -2;
	}
	sincePlus++;
}

void printArray(char as[]) { printArray(as, count); }

void printArray(char as[], byte n) {
	tinyfont.print(n);
	tinyfont.print(": ");
	for (byte i = 0; i < n; i++) {
		tinyfont.print(as[i]);
	}
	tinyfont.print("\n");
}

void deepCopyArray(char* source, char* dest, byte size) {
	for (byte i = 0; i < size; i++) {
		dest[i] = source[i];
	}
}

void add(char atoms[], char i) {
	if (count < 3) {
		return;
	}
	char leftIndex = (i - 1) % count;
	if (i - 1 < 0) {
		leftIndex = i - 1 + count;
	}

	char left = atoms[leftIndex];
	char right = atoms[((i + 1) % count)];
	// tinyfont.print("I: ");
	// tinyfont.print("L:");
	// tinyfont.print(leftIndex);
	// tinyfont.print(" R:");
	// tinyfont.print((i + 1) % count);
	// tinyfont.print(" V: ");
	// tinyfont.print("L:");
	// tinyfont.print(left);
	// tinyfont.print(" R:");
	// tinyfont.print(right);
	// tinyfont.println();

	if (left == right && (left != -1 || right != -1)) {
		if (atoms[i % count] == -1) {
			atoms[i % count] = left + 1;
		} else {
			if (left > atoms[i % count]) {
				atoms[i % count] = left + 2;
			} else {
				atoms[i % count]++;
			}
		}
		atoms[leftIndex] = 0;
		atoms[(i + 1) % count] = 9;
		// preCombineAnimate();
		if (i == 0) {
			deleteAtIndex(atoms, 1);
			deleteAtIndex(atoms, count - 1);
			if (count > 2) {
				printArray(atoms);
				add(atoms, 0);
			}
		} else {
			deleteAtIndex(atoms, (i + 1) % count);
			if (i == count) {
				deleteAtIndex(atoms, (i - 2) % count);
			} else {
				deleteAtIndex(atoms, (i - 1) % count);
			}
			if (count > 2) {
				printArray(atoms);
				add(atoms, ((i - 1) % count));
			}
		}
	}
}

void addAtom(char i, char num) {
	turn++;
	i = i % count;
	count++;
	for (char j = count - 1; j > i; j--) {
		atoms[j] = atoms[j - 1];
	}
	atoms[i] = num;
	if (plusEnabled) {
		evaluatePlus(atoms);
	}
}

void deleteAtIndex(char atoms[], char index) {
	index = index % count;
	for (char i = index; i < count - 1; ++i) {
		atoms[i] = atoms[i + 1];
	}
	count--;
}

void evaluatePlus(char atoms[]) {
	// This is really janky, but it mostly works. It runs through the atoms a
	// bunch of time. May need to adjust the count multiplier. Should probably
	// count the number of pluses and use that somehow
	for (char i = 0; i < count * 4; i++) {
		if (atoms[i % count] == -1) {
			add(atoms, i % count);
		}
	}
}

bool hasPlus(char atoms[]) { return hasPlus(atoms, count); }

bool hasPlus(char atoms[], char count) {
	for (char i = 0; i < count; i++) {
		if (atoms[i] == -1) {
			return true;
		}
	}
	return false;
}
