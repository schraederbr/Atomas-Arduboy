// Use this to get hex file:
// arduino-cli compile --fqbn arduboyC:avr:arduboyC .\drawing.ino --output-dir ./
#include <Arduboy2.h>
Arduboy2 arduboyC;
int centerX = 64;
int centerY = 32;
int radius = 24;
int baseNum = 1;
int index = 0;
int nextNum = 1;
//int nums[50] = {1};
extern int count;
extern int atoms[];
// degrees * pi/180

//DoublyLinkedList list;

void drawCircleNumber(int x, int y, int num)
{
	arduboyC.drawCircle(x, y, 5, WHITE);
	arduboyC.setCursor(x - 2, y - 3);
	arduboyC.print(num);
}

void drawAtom(int i, int num)
{
	float currentStep = 2 * PI / count;
	int x = centerX + cos(i * currentStep) * radius;
	int y = centerY + sin(i * currentStep) * radius;
	drawCircleNumber(x, y, num);
}

void drawAtoms(int nums[])
{
	for (int i = 0; i < count; i++)
	{
		drawAtom(i, nums[i]);
	}
	drawCircleNumber(centerX, centerY, nextNum);
}

void drawLine()
{
	float currentStep = 2 * PI / count;
	drawLineOnCircle(index * currentStep + currentStep / 2);
}

void drawLineOnCircle(float angle)
{
	arduboyC.drawLine(centerX, centerY, centerX + cos(angle) * radius, centerY + sin(angle) * radius, WHITE);
	return;
}

void addAtom(int i, int num)
{
	count++;
	for (int j = count - 1; j > i; j--)
	{
		atoms[j] = atoms[j - 1];
	}
	atoms[i] = num;
}

void generateAtomNum()
{
	nextNum = baseNum;
	baseNum++;
}

// void setup() {
//     arduboyC.begin();
//     arduboyC.clear();
//     // for(int i = 0; i < count; i++){
//     //     list.addNode(atoms[i]);
//     // }
//     // list.printList();
//     //list.processList();
//     //list.printList();
//     //Print all atoms with a for loop
//     arduboyC.print(count);
//     arduboyC.print(" Atoms: ");
//     for(int i = 0; i < count; i++){
//         arduboyC.print(atoms[i]);
//     }
//     arduboyC.print("\n");
// 	//for(int i = 0; i < count; i++){
// 		recAdd(atoms, 8);
// 	//}
    
//     arduboyC.display();
// }
// // void setup(){

// // }
// void loop()
// {
// 	arduboyC.pollButtons();
// 	if (arduboyC.justPressed(A_BUTTON))
// 	{
// 		addAtom(index + 1, nextNum);
// 		generateAtomNum();
// 	}

// 	if (arduboyC.justPressed(LEFT_BUTTON))
// 	{
// 		if (index > 0)
// 		{
// 			index--;
// 		}
// 		else
// 		{
// 			index = count - 1;
// 		}
// 	}

// 	if (arduboyC.justPressed(RIGHT_BUTTON))
// 	{
// 		if (index < count - 1)
// 		{
// 			index++;
// 		}
// 		else
// 		{
// 			index = 0;
// 		}
// 	}
// 	arduboyC.clear();
// 	drawAtoms(nums);
// 	drawLine();
// 	arduboyC.display();
// }
