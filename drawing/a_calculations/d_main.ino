// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\drawing.ino --output-dir ./
#include <Arduboy2.h>
Node *current = new Node();

extern int atoms[50];
// int a[10] = {1, 4, 1, -1};
// int co = 4;
extern int count;
int debugMode = 0;
// void setup()
// {
// 	//Works
// 	// int arr[] = {3,2,3,2,-1,2};
// 	// count = 6;
// 	arduboy.begin();
// 	arduboy.clear();
// 	arduboy.setFrameRate(60);
// 	if (debugMode == 1)
// 	{
// 		printArray(atoms);
// 		evaluatePlus(atoms);
// 		arduboy.print("Final \n");
// 		printArray(atoms);
// 	}
// 	arduboy.display();
// }

// void loop()
// {
// 	if (!arduboy.nextFrame()) return;
// 	if(arduboy.justPressed(DOWN_BUTTON)){
// 		plusEnabled = !plusEnabled;
// 	}
// 	if (arduboy.justPressed(B_BUTTON))
// 	{
// 		debugMode = 1;
// 		if (debugMode == 1)
// 		{
// 			arduboy.clear();
// 			printArray(atoms);
// 			arduboy.display();
// 			evaluatePlus(atoms);
// 			arduboy.print("Final \n");
// 			printArray(atoms);
// 			arduboy.display();
// 			while(true){

// 			}
// 		}
// 	}
// 	if (debugMode != 0)
// 	{
// 		return;
// 	}

// 	if (debugMode == 0)
// 	{
// 		arduboy.pollButtons();
// 		if (arduboy.justPressed(A_BUTTON))
// 		{
// 			addAtom(index + 1, nextNum);
// 			generateAtomNum();
// 		}

// 		if (arduboy.justPressed(LEFT_BUTTON))
// 		{
// 			if (index > 0)
// 			{
// 				index--;
// 			}
// 			else
// 			{
// 				index = count - 1;
// 			}
// 		}

// 		if (arduboy.justPressed(RIGHT_BUTTON))
// 		{
// 			if (index < count - 1)
// 			{
// 				index++;
// 			}
// 			else
// 			{
// 				index = 0;
// 			}
// 		}
// 		arduboy.clear();
// 		drawAtoms(atoms);
// 		if (count != 0)
// 		{
// 			drawLine();
// 		}
// 		arduboy.display();
// 	}
// }
