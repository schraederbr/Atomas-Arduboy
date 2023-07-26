// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\a_atomas --output-dir ./
#include <Arduboy2.h>
int centerX = 64;
int centerY = 32;
int radius = 24;

void drawCircleNumber(int x, int y, int num) {
	arduboy.drawCircle(x, y, 5, WHITE);
	tinyfont.setCursor(x - 2, y - 3);
	if (num == -1) {
		tinyfont.print("+");
	} else if (num == -2) {
		tinyfont.print("-");
	} else {
		tinyfont.print(num);
	}
	// This is to fill in the circle
	// The print call deletes part of the cicle
	arduboy.drawPixel(x + 3, y + 4);
}

void drawAtom(char i, char num) {
	float currentStep = 2 * PI / count;
	int x = centerX + cos(i * currentStep) * radius;
	int y = centerY + sin(i * currentStep) * radius;
	drawCircleNumber(x, y, num);
}

void drawAtoms(char nums[]) {
	for (byte i = 0; i < count; i++) {
		drawAtom(i, nums[i]);
	}
	drawCircleNumber(centerX, centerY, nextNum);
}

void drawLine() { drawLine(0.5); }

void drawLine(float offset) {
	float currentStep = 2 * PI / count;
	drawLineOnCircle(index * currentStep + (currentStep * offset), 10, radius);
}

void drawLineOnCircle(float angle, int innerRadius, int outerRadius) {
	arduboy.drawLine(centerX + cos(angle) * innerRadius,
					 centerY + sin(angle) * innerRadius,
					 centerX + cos(angle) * outerRadius,
					 centerY + sin(angle) * outerRadius, WHITE);
}

void drawTurn() {
	tinyfont.setCursor(3, 3);
	tinyfont.print(turn);
}

void getXY(int i, int count, float offset, int centerX, int centerY, int radius,
		   int &outX, int &outY) {
	float currentStep = 2 * PI / count;
	tinyfont.print(currentStep);
	tinyfont.println();
	outX = centerX + cos((i * currentStep) + (currentStep * offset)) * radius;
	outY = centerY + sin(i * currentStep) * radius;
}

void getXY(int i, int count, int centerX, int centerY, int radius, int &outX,
		   int &outY) {
	getXY(i, count, 0, centerX, centerY, radius, outX, outY);
}

void getXY(int i, int count, int &outX, int &outY) {
	getXY(i, count, 0, centerX, centerY, radius, outX, outY);
}

void getXY(int i, int count, float offset, int &outX, int &outY) {
	getXY(i, count, offset, centerX, centerY, radius, outX, outY);
}

int lerp(int startValue, int endValue, int currentFrame, int totalFrames) {
	return startValue +
		   ((endValue - startValue) * currentFrame + totalFrames / 2) /
			   totalFrames;
}

void updatePosition(AtomAnimation &aa, int currentFrame, int totalFrames) {
	updatePosition(aa.currentX, aa.currentY, aa.startX, aa.startY, aa.endX,
				   aa.endY, currentFrame, totalFrames);
}

void updatePosition(int &currentX, int &currentY, int startX, int startY,
					int endX, int endY, int currentFrame, int totalFrames) {
	currentX = lerp(startX, endX, currentFrame, totalFrames);
	currentY = lerp(startY, endY, currentFrame, totalFrames);
}
