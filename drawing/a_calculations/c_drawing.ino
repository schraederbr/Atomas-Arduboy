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

void setup(){
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);
	
}
AtomAnimation anims[20];
void preAnimate(){
    if(animationCount == 0){
        animationCount = count;
    }
	for(int i = 0; i < animationCount; i++){
		int bx, by, fx, fy;
		if(i <= index){
			getXY(i, count-1,bx,by);
			getXY(i, count, fx, fy);
		}
		else{
			getXY(i, count-1,bx,by);
			getXY(i + 1, count, fx, fy);
		}
		anims[i] = {atoms[i], bx,by,bx,by,fx,fy};
	}
	// for(int i = 0; i < count; i++){
	// 	arduboy.print(anims[i].currentX);
	// 	arduboy.print(anims[i].)
	// }
}

void preCombineAnimate(){
    int n = prevAtoms[index];
    int bx, by, bx2, by2, fx,fy;
    //May be able to use count + 2 instead of oldCount
    int tempIndex = index - 1 < 0 ? count - 1 : index - 1;
    getXY(tempIndex, oldCount, bx, by);
    getXY(index, oldCount, fx, fy);
    anims[0] = {n, bx, by, bx, by, fx, fy};
    //Use this more
    tempIndex = index + 1 < count ? index + 1 : 0;
    n = prevAtoms[tempIndex];
    getXY(tempIndex, oldCount, bx2, by2);
    anims[1] = {n, bx2, by2, bx2, by2, fx, fy};
    animationCount = 2;
    animate = true;
}

//Need to loop added atom from the center the outside
void animateLoop(){
	arduboy.clear();
	frames++;
	for(int i = 0; i < count; i++){
		updatePosition(anims[i], frames, totalFrames);
		drawCircleNumber(anims[i].currentX, anims[i].currentY, anims[i].num);
		//arduboy.drawCircle(anims[i].currentX, anims[i].currentY, 5, WHITE);
		arduboy.display();
		//delay(1000);
	}
	if(frames > totalFrames){
		animate = false;
		frames = 0;
	}
	
}

// void animateLoop(){
// 	arduboy.clear();
// 	static AtomAnimation anims[20];
// 	for(int i = 0; i <= index; i++){
// 		int x1, y1;
// 		getXY(i, count - 1, x1, y1);
// 		int x2, y2;
// 		getXY(i, count, x2, y2);
// 		arduboy.print(x1);
// 		arduboy.print(",");
// 		arduboy.print(y1);
// 		arduboy.println();
// 		arduboy.print(x2);
// 		arduboy.print(",");
// 		arduboy.print(y2);
// 		arduboy.display();
// 		while(true){};

		
// 	}

// }



// void animateLoop(){
// 	static AtomAnimation anim = {1, 64, 32, 96, 48, 64, 32};
// 	if (!arduboy.nextFrame()) return;
// 	arduboy.clear();
// 	static int frame = 0;
// 	static int totalFrames = 120;
// 	frame++;
// 	if (frame > totalFrames) frame = 0;
// 	if(animate){
// 		updatePosition(anim, frame, totalFrames);
// 	}
// 	drawCircleNumber(anim.currentX, anim.currentY, anim.num);
	
// 	// Example usage of the lerp function
// 	arduboy.display();
// }
