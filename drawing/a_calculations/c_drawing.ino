// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\drawing.ino --output-dir ./
#include <Arduboy2.h>
int centerX = 64;
int centerY = 32;
int radius = 24;

// degrees * pi/180





void drawCircleNumber(int x, int y, int num)
{
	arduboy.drawCircle(x, y, 5, WHITE);
	arduboy.setCursor(x - 2, y - 3);
	if(num == -1){
		arduboy.print("+");
	}
	else if(num == -2){
		arduboy.print("-");
	}
	else{
		arduboy.print(num);
	}
	//This is to fill in the circle
	//The print call deletes part of the cicle
	arduboy.drawPixel(x + 3, y + 4);
	
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

void drawLine(){
	drawLine(0.5);
}

//Inverse. offset is on the bottom of division
void drawLine(float offset)
{
	float currentStep = 2 * PI / count;
	drawLineOnCircle(index * currentStep + (currentStep * offset), 10, radius);
}

void drawLineOnCircle(float angle, int innerRadius, int outerRadius)
{
	arduboy.drawLine(centerX + cos(angle) * innerRadius, centerY + sin(angle) * innerRadius, centerX + cos(angle) * outerRadius, centerY + sin(angle) * outerRadius, WHITE);
	return;
}

void drawTurn(){
	arduboy.setCursor(3,3);
	arduboy.print(turn);
}

void getXY(int i, int count, int centerX, int centerY, int radius, int &outX, int &outY){
	float currentStep = 2 * PI / count;
	arduboy.print(currentStep);
	arduboy.println();
	outX = centerX + cos(i * currentStep) * radius;
	outY = centerY + sin(i * currentStep) * radius;
}

void getXY(int i, int count, int &outX, int &outY){
	getXY(i, count, centerX, centerY, radius, outX, outY);
}


int lerp(int startValue, int endValue, int currentFrame, int totalFrames) {
  return startValue + ((endValue - startValue) * currentFrame + totalFrames / 2) / totalFrames;
}

void updatePosition(AtomAnimation &aa, int currentFrame, int totalFrames){
	updatePosition(aa.currentX, aa.currentY, aa.startX, aa.startY, aa.endX, aa.endY, currentFrame, totalFrames);
}

void updatePosition(int &currentX, int &currentY, int startX, int startY, int endX, int endY, int currentFrame, int totalFrames) {
  	currentX = lerp(startX, endX, currentFrame, totalFrames);
  	currentY = lerp(startY, endY, currentFrame, totalFrames);
}

