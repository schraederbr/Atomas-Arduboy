// Use this to get hex file:
// arduino-cli compile --fqbn arduboyD:avr:arduboyD .\drawing.ino --output-dir ./
#include <Arduboy2.h>
Arduboy2 arduboyD;
Node* current = new Node();

void setup() {
    arduboyD.begin();
    arduboyD.clear();
    arduboyB.begin();
    arduboyB.clear();
    
    current->data = atoms[0];
    current->prev = current;
    current->next = current;
    
    for(int i = 1; i < count; i++){
        insertNode(current, atoms[i]);
    }
    //Print all atoms with a for loop
    arduboyB.print(count);
    arduboyB.print(":");
    printNodes(current);
    // for(int i = 0; i < count; i++){
    //     list.addNode(atoms[i]);
    // }
    // list.printList();
    //list.processList();
    //list.printList();
    //Print all atoms with a for loop
    
    arduboyD.display();
}
// void setup(){

// }
void loop()
{
	arduboyD.pollButtons();
	if (arduboyD.justPressed(A_BUTTON))
	{
		insertNode(current, 7);

		generateAtomNum();
	}

	if (arduboyD.justPressed(LEFT_BUTTON))
	{
		current = current->prev;
		if (index > 0)
		{
			index--;
		}
		else
		{
			index = count - 1;
		}
	}

	if (arduboyD.justPressed(RIGHT_BUTTON))
	{
		current = current->next;
		if (index < count - 1)
		{
			index++;
		}
		else
		{
			index = 0;
		}
	}
	arduboyD.clear();
	drawAtoms(atoms);
	drawLine();
	arduboyD.display();
}
