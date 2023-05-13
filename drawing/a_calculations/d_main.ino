// Use this to get hex file:
// arduino-cli compile --fqbn arduboyD:avr:arduboyD .\drawing.ino --output-dir ./
#include <Arduboy2.h>
Arduboy2 arduboyD;
Node* current = new Node();

void setup() {
    arduboyD.begin();
    arduboyD.clear();
    arrayToNodes(atoms, count, current);
    for(int i = 1; i < count; i++){
        insertNode(current, atoms[i]);
    }
    printNodes(current);
	int newAtoms[50];
	nodesToArray(newAtoms, count, current);
  	printArray(newAtoms);
	Node* newCurrent = new Node();
	arrayToNodes(newAtoms, count, newCurrent);
	printNodes(newCurrent);
    arduboyD.display();
}
// void setup(){
// }
void loop(){}
// void loop()
// {
// 	arduboyD.pollButtons();
// 	if (arduboyD.justPressed(A_BUTTON))
// 	{
// 		insertNode(current, 7);

// 		generateAtomNum();
// 	}

// 	if (arduboyD.justPressed(LEFT_BUTTON))
// 	{
// 		current = current->prev;
// 		if (index > 0)
// 		{
// 			index--;
// 		}
// 		else
// 		{
// 			index = count - 1;
// 		}
// 	}

// 	if (arduboyD.justPressed(RIGHT_BUTTON))
// 	{
// 		current = current->next;
// 		if (index < count - 1)
// 		{
// 			index++;
// 		}
// 		else
// 		{
// 			index = 0;
// 		}
// 	}
// 	arduboyD.clear();
// 	drawAtoms(atoms);
// 	drawLine();
// 	arduboyD.display();
// }
