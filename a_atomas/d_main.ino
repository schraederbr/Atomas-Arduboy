// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\a_atomas.ino --output-dir ./
#include <Arduboy2.h>
Node *current = new Node();

int debugMode = 0;


void mainSetup()
{
	//Works
	// int arr[] = {3,2,3,2,-1,2};
	// count = 6;
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(0.1);
	if (debugMode == 1){
		printArray(atoms);
		//evaluatePlus(atoms);
		arduboy.print("Final \n");
		printArray(atoms);
	}
	arduboy.display();
}
void debugMode1(){
    
	arduboy.clear();
	printArray(atoms);
    arduboy.print("\n");
    arduboy.print("Symmetry: ");
	int start, end;
    arduboy.print(maxSymmetry(atoms, count, &start, &end));
	arduboy.print("\n");
	arduboy.print(start);
	arduboy.print(" ");
	arduboy.print(end);
	arduboy.display();
	while(true){
	}
}

void debugMode2(){
    arduboy.clear();
	printArray(atoms);
	addThings();
	printArray(atoms);
    // int testarr[20] = {2,1,2,3,1,1,3,2,1,2};
    // printArray(testarr, 10);
    // arduboy.print("\n");
	// int finalAtom = 0;
    // int score = calculateScore(testarr, 10, 0, finalAtom);
    // arduboy.print("Score: ");
    // arduboy.print(score);
    arduboy.display();
    while(true){
    }
}

void setup(){
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(1);
	arduboy.initRandomSeed();
}
void doMinus(){
	deepCopyArray(atoms, prevAtoms, count);
	oldCount = count;
	nextNum = atoms[index];
	deleteAtIndex(atoms,index);
	inMinus = true;
}

void loseGame(){
    arduboy.clear();
    arduboy.print("You lasted ");
    arduboy.print(turn);
    arduboy.print(" turns");
    arduboy.print("\n");
    saveScore();
    arduboy.print("High Score: ");
    arduboy.print(EEPROM.read(512));
    arduboy.display();
    while(true){
        arduboy.pollButtons();
        if(arduboy.justPressed(A_BUTTON) | arduboy.justPressed(B_BUTTON)){
            fullReset();
            return;
        }
    }
    
}

//Might need to randomize the seed. Or that could just be the emulator.
void fullReset(){
    for(int i = 0; i < count; i++){
        atoms[i] = 0;
        prevAtoms[i] = 0;
    }
    atoms[0] = 1;
    count = 1;
    oldCount = 0;
    plusEnabled = true;
    sincePlus = 0;
    turn = 0;
	currentScore = 0;
    baseNum = 1;
    range = 4;
    nextNum = 1;
    index = 0;
    frames = 0;
    totalFrames = 60;
    animationCount = 0;
    inMinus = false;
    animate = false;
}

void loop()
{
	//debugMode = 2;
	if (!arduboy.nextFrame()) return;
	arduboy.pollButtons();
	if(arduboy.justPressed(DOWN_BUTTON)){
		plusEnabled = !plusEnabled;
	}
	
	if (debugMode == 1){
		debugMode1();
	}
    else if (debugMode == 2){
        debugMode2();
    }
	if (debugMode != 0){
		return;
	}
	if(animate == true){
		animateLoop();
	}
	else{
		if (arduboy.justPressed(A_BUTTON)){
			if(nextNum != -2){
				deepCopyArray(atoms, prevAtoms, count);
				oldCount = count;
				addAtom(index + 1, nextNum);
				generateAtomNum();
				//preAnimate();
				
				//animate = true;
			}
			else if(nextNum == -2){
				doMinus();
			}
				
		}
		if (arduboy.justPressed(B_BUTTON)){
			if(inMinus){
				nextNum = -1;
				inMinus = false;
			}
			else{
				debugMode = 2;
			}
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
        if(count > 16){
            loseGame();
        }
		arduboy.clear();
		drawAtoms(atoms);
        //drawSymmetryStraight();
		drawSymmetryCircle();
		drawTurn();
		//drawScore();
		if(nextNum == -2){
			drawLine(0);
		}
		else{
			drawLine(0.5);
		}
		arduboy.display();
	}
	
}
