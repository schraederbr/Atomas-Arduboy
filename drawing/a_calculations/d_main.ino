// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\drawing.ino --output-dir ./
#include <Arduboy2.h>
Node *current = new Node();

// int a[10] = {1, 4, 1, -1};
// int co = 4;
int debugMode = 0;
void mainSetup()
{
	//Works
	// int arr[] = {3,2,3,2,-1,2};
	// count = 6;
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);
	if (debugMode == 1){
		printArray(atoms);
		evaluatePlus(atoms);
		arduboy.print("Final \n");
		printArray(atoms);
	}
	arduboy.display();
}
void debugMode1(){
	arduboy.clear();
	printArray(atoms);
	arduboy.display();
	evaluatePlus(atoms);
	arduboy.print("Final \n");
	printArray(atoms);
	arduboy.display();
	while(true){
	}
}



void loop()
{
	if (!arduboy.nextFrame()) return;
	arduboy.pollButtons();
	if(arduboy.justPressed(DOWN_BUTTON)){
		plusEnabled = !plusEnabled;
	}
	if (arduboy.justPressed(B_BUTTON)){
		debugMode = 1;
	}
	if (debugMode == 1){
		debugMode1();
	}
	if (debugMode != 0){
		return;
	}
	if(animate == true){
		animateLoop();
	}
	else{
		if (arduboy.justPressed(A_BUTTON)){
			deepCopyArray(atoms, prevAtoms, count);
            oldCount = count;
			addAtom(index + 1, nextNum);
			generateAtomNum();
            //preAnimate();
			
			//animate = true;
	}

	if (arduboy.justPressed(LEFT_BUTTON)){
		if (index > 0){
			index--;
		}
		else{
			index = count - 1;
		}
	}

	if (arduboy.justPressed(RIGHT_BUTTON)){
		if (index < count - 1){
			index++;
		}
		else{
			index = 0;
		}
	}
	arduboy.clear();
	drawAtoms(atoms);
	if (count != 0){
		drawLine();
	}
	arduboy.display();
	}
	
}
