// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\drawing.ino --output-dir ./
#include <Arduboy2.h>
Arduboy2 arduboy;
int centerX = 64;
int centerY = 32;
int radius = 24;
int baseNum = 1;
int index = 0;
int nextNum = 1;
int nums[50] = {1};
extern int count;
extern int atoms[];
// degrees * pi/180

void drawCircleNumber(int x, int y, int num)
{
	arduboy.drawCircle(x, y, 5, WHITE);
	arduboy.setCursor(x - 2, y - 3);
	arduboy.print(num);
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
	arduboy.drawLine(centerX, centerY, centerX + cos(angle) * radius, centerY + sin(angle) * radius, WHITE);
	return;
}

void addAtom(int i, int num)
{
	count++;
	for (int j = count - 1; j > i; j--)
	{
		nums[j] = nums[j - 1];
	}
	nums[i] = num;
}

void generateAtomNum()
{
	nextNum = baseNum;
	baseNum++;
}

void setup() {
    arduboy.begin();
    arduboy.clear();
    //Print all atoms with a for loop
    arduboy.print(count);
    arduboy.print(" Atoms: ");
    for(int i = 0; i < count; i++){
        arduboy.print(atoms[i]);
    }
    arduboy.print("\n");
	//for(int i = 0; i < count; i++){
		recAdd(atoms, 8);
	//}
    
    arduboy.display();
}

void loop()
{
	// arduboy.pollButtons();
	// if (arduboy.justPressed(A_BUTTON))
	// {
	// 	addAtom(index + 1, nextNum);
	// 	generateAtomNum();
	// }

	// if (arduboy.justPressed(LEFT_BUTTON))
	// {
	// 	if (index > 0)
	// 	{
	// 		index--;
	// 	}
	// 	else
	// 	{
	// 		index = count - 1;
	// 	}
	// }

	// if (arduboy.justPressed(RIGHT_BUTTON))
	// {
	// 	if (index < count - 1)
	// 	{
	// 		index++;
	// 	}
	// 	else
	// 	{
	// 		index = 0;
	// 	}
	// }
	// arduboy.clear();
	// drawAtoms(nums);
	// drawLine();
	// arduboy.display();
}