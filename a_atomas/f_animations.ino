// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\drawing.ino --output-dir ./
#include <Arduboy2.h>

// degrees * pi/180

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
    //getXY(index, oldCount, fx, fy);
    getXY(index, oldCount, 0.5, fx, fy);
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