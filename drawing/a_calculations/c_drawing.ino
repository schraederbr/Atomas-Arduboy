// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\drawing.ino --output-dir ./
#include <Arduboy2.h>
int centerX = 64;
int centerY = 32;
int radius = 24;
int baseNum = 1;
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