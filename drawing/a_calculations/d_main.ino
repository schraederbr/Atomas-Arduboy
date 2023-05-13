// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\drawing.ino --output-dir ./
#include <Arduboy2.h>
Node* current = new Node();

void add(int atoms[], int i){
	int left = atoms[(i - 1) % count];
	int right = atoms[(i + 1) % count];
	arduboy.print("Index: ");
	arduboy.print("L: ");
	arduboy.print((i - 1) % count);
	arduboy.print(" R: ");
	arduboy.print((i + 1) % count);
	arduboy.println();
	arduboy.print("Values");
	arduboy.print("L: ");
	arduboy.print(left);
	arduboy.print(" R: ");
	arduboy.print(right);
	arduboy.println();

	if(left == right){
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
		atoms[(i - 1) % count] = 0;
		atoms[(i + 1) % count] = 9;
		deleteAtIndex(atoms, (i + 1) % count);
		deleteAtIndex(atoms, (i - 1) % count);
		//This if might not quite be right
		if(count > 2){
			printArray(atoms);
			add(atoms, ((i - 2) % count));
		}
	}
	else{
		if(atoms[i % count] == -1){
			atoms[i % count] == -2;
		}
	}

	
}

void addAtom(int i, int num)
{
	count++;
	for (int j = count - 1; j > i; j--)
	{
		atoms[j] = atoms[j - 1];
	}
	atoms[i] = num;
	evaluatePlus(atoms);
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

void setup(){
	arduboy.begin();
    arduboy.clear();
	// printArray(atoms);
	evaluatePlus(atoms);
	// arduboy.print("Final \n");
	// printArray(atoms);
	// arduboy.display();
}

void loop()
{
	arduboy.pollButtons();
	if (arduboy.justPressed(A_BUTTON)){
		addAtom(index + 1, nextNum);
		generateAtomNum();
	}

	if (arduboy.justPressed(LEFT_BUTTON)){
		if (index > 0){
			index--;
		}
		else{
			index = count - 1;
		}
	}

	if (arduboy.justPressed(RIGHT_BUTTON))
	{
		if (index < count - 1){
			index++;
		}
		else{
			index = 0;
		}
	}

	arduboy.clear();
	drawAtoms(atoms);
	if(count != 0){
		drawLine();
	}
	arduboy.display();
}
