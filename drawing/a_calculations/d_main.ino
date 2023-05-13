// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\drawing.ino --output-dir ./
#include <Arduboy2.h>
Node* current = new Node();



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
