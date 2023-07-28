// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\a_atomas --output-dir ./
#include <Arduboy2.h>
int centerX = 64;
int centerY = 32;
int radius = 24;
int innerRadius = 16;

// degrees * pi/180

void drawCircleNumber(int x, int y, int num) {
	arduboy.drawCircle(x, y, 5, WHITE);
	arduboy.setCursor(x - 2, y - 3);
	if (num == -1) {
		arduboy.print("+");
	} else if (num == -2) {
		arduboy.print("-");
	} else {
		arduboy.print(num);
	}
	// This is to fill in the circle
	// The print call deletes part of the cicle
	arduboy.drawPixel(x + 3, y + 4);
}

void drawAtom(int i, int num) {
	float currentStep = 2 * PI / count;
	int x = centerX + cos(i * currentStep) * radius;
	int y = centerY + sin(i * currentStep) * radius;
	drawCircleNumber(x, y, num);
}

void drawAtoms(int nums[]) {
	for (int i = 0; i < count; i++) {
		drawAtom(i, nums[i]);
	}
	drawCircleNumber(centerX, centerY, nextNum);
}

void drawLine() { drawLine(0.5); }

// Inverse. offset is on the bottom of division
void drawLine(float offset) {
	float currentStep = 2 * PI / count;
	drawLineOnCircle(index * currentStep + (currentStep * offset), 10, radius);
}

void drawLineOnCircle(float angle, int innerRadius, int outerRadius) {
	arduboy.drawLine(centerX + cos(angle) * innerRadius,
					 centerY + sin(angle) * innerRadius,
					 centerX + cos(angle) * outerRadius,
					 centerY + sin(angle) * outerRadius, WHITE);
	return;
}

void drawTurn() {
	arduboy.setCursor(3, 3);
	arduboy.print(turn);
}

// This should use the base getXY function
void getXYFromIndex(int i, int rad, int &outX, int &outY) {
	float currentStep = 2 * PI / count;
	outX = centerX + cos(i * currentStep) * rad;
	outY = centerY + sin(i * currentStep) * rad;
}

// This needs to ignore pluses
// Draws symmetry with straight lines
void drawSymmetryStraight() {
	int start, end;
	int maxSym = maxSymmetry(atoms, count, &start, &end);
	int x0, y0, x1, y1;
	for (int i = 0; i < maxSym - 1; i++) {
		getXYFromIndex((start + i) % count, innerRadius - 3, x0, y0);
		getXYFromIndex((start + i + 1) % count, innerRadius - 3, x1, y1);
		arduboy.drawLine(x0, y0, x1, y1, WHITE);
	}
}

// This almost works. But tends to break when circle exceeds half of atoms
void drawSymmetryCircle() {
	int start, end;
	int maxSym = maxSymmetry(atoms, count, &start, &end);
	int x0, y0, x1, y1;
	for (int i = 0; i < maxSym - 1; i++) {
		getXYFromIndex((start + i) % count, innerRadius, x0, y0);
		getXYFromIndex((start + i + 1) % count, innerRadius, x1, y1);
		drawPartialCircle(innerRadius, x0, y0, x1, y1);
	}
}

void swapFloat(float &a, float &b) {
	float c = a;
	a = b;
	b = c;
}

void drawPartialCircle(int r, int x0, int y0, int x1, int y1) {
	int centerX = 64, centerY = 32;

	float theta0 = atan2(y0 - centerY, x0 - centerX);
	float theta1 = atan2(y1 - centerY, x1 - centerX);

	if (fabs(theta0 - theta1) < 3.14159) {
		if (theta0 > theta1) {
			swapFloat(theta0, theta1);
		}
	} else {
		if (theta0 < theta1) {
			swapFloat(theta0, theta1);
		}
	}

	if (theta1 < 0) {
		theta1 += 2 * 3.14159;
	}

	if (theta0 > theta1) {
		swapFloat(theta0, theta1);
	}

	for (float theta = theta0; theta <= theta1; theta += 0.05) {
		int x = centerX + r * cos(theta);
		int y = centerY + r * sin(theta);
		arduboy.drawPixel(x, y, WHITE);
	}
}

// Need to make this ignore pluses. At least if plus is in the middle
// There might be other cases where pluses should be considered. Like 2+11.
// Not sure if the actual game does that
int maxSymmetry(int arr[], int len, int *start, int *end) {
	int max_sym = 0;
	*start = *end = 0;
	for (int i = 0; i < len; i++) {
		for (int k = 2; k <= len; k += 2) {
			int count = 0;
			for (int j = 0; j < k / 2; j++) {
				if (arr[(i + j) % len] == arr[(i + k - j - 1) % len]) {
					count++;
				} else {
					break;
				}
			}
			if (count == k / 2 && k > max_sym) {
				max_sym = k;
				*start = i;
				*end = (i + k - 1) % len;
			}
		}
	}
	return max_sym;
}

void getXY(int i, int count, float offset, int centerX, int centerY, int radius,
		   int &outX, int &outY) {
	float currentStep = 2 * PI / count;
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
