/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;
#define MAX_ARRAY_SIZE 20
int atoms[20] = {4,2,3,2,4,2,-1,2};
int atomsD[20];
int countD = 0;
int scoreAtoms[20];
int scoreAtomsCount = 0;
int count = 8;
int currentScore = 0;

void printArray(int as[], int n)
{
    cout << n;
    cout << ": ";
    for (int i = 0; i < n; i++)
    {
        cout << as[i];
    }
    cout << "\n";
}

void printArray(int as[])
{
   printArray(as, count);
}

void deepCopyArray(int* source, int* dest, int size) {
  for (int i = 0; i < size; i++) {
    dest[i] = source[i];
  }
}

void deleteAtIndex(int atoms[], int& c, int index) {
    if(c == 0){
        return;
    }
    index = index % c;
    for (int i = index; i < c - 1; ++i) {
        atoms[i] = atoms[i + 1];
    }
    c--;
}

bool hasPlus(int atoms[], int count){
	for(int i = 0; i < count; i++){
		if(atoms[i] == -1){
			return true;
		}
	}
	return false;
}

bool hasPlus(int atoms[]){
	return hasPlus(atoms, count);
}

int deleteFromCircularArrayAndInsert(int* array, int arrayLength, int index, int width, int* outputArray, int num) {
    int outputArrayIndex = 0;

    for (int i = 0; i < arrayLength; ++i) {
        // If the current index is outside the range to delete, copy it to the output array
        if (!(i >= index && i < (index + width) % arrayLength)) {
            outputArray[outputArrayIndex++] = array[i];
        }

        // Insert new number at the index position
        if (i == ((index + width - 1) % arrayLength)) {
            outputArray[outputArrayIndex++] = num;
        }
    }

    return outputArrayIndex; 
}

// int findSymmetry(int index){
//   if (atoms[index] != -1) return 0;

//   int symmetry_length = 0;
//   int left_index = index - 1;
//   int right_index = index + 1;

//   while(symmetry_length < count) { // limit loop by count to avoid infinite loop.
//     if(left_index < 0) left_index = count - 1; // wrap around to the end
//     if(right_index == count) right_index = 0; // wrap around to the start

//     if(atoms[left_index] != atoms[right_index])
//       break;

//     symmetry_length++; // Increase the symmetric length
//     --left_index;
//     ++right_index;
//   }

//   return symmetry_length * 2; // multiply by 2 because we are counting symmetric pairs
// }

//THis function is broken
int getPlusSymmetry(int arr[], int len, int i, int &start, int &end){
	start = i;
	end = i;
	
	int distanceFromIndex = 0;
	//while(distanceFromIndex * 2 - 1 < len){
	while(distanceFromIndex <= len / 2){
	    cout << "Start: " << start << " End: " << end << " Distance: : " << distanceFromIndex << "\n";
		if(atoms[i] != -1){
		    cout << "One" << "\n";
			return distanceFromIndex * 2;
		}
		if(len < 3){
		    cout << "Two" << "\n";
			return distanceFromIndex * 2;
		}
		int left, right;
        if(i - distanceFromIndex >= 0){
        	left = i - distanceFromIndex;
        }
        else{
        	left = (i - distanceFromIndex + len) % len;
        }
        if(i + distanceFromIndex < len){
		    right = i + distanceFromIndex;
	    }
	    else{
		    right = (i + distanceFromIndex) % len; 
	    }
		if(atoms[left] == atoms[right]){
			start = left;
			end = right;
			distanceFromIndex++;
		}
		else{
		    cout << "Three" << "\n";
			return distanceFromIndex * 2;
		}
	}
	cout << "Four" << "\n";
	return (distanceFromIndex) * 2 ;
}

int sym(int i, int& center){
    deepCopyArray(atoms, atomsD, MAX_ARRAY_SIZE);
    countD = count;
    int left, right;
    int width = 0;
    while(countD >= 3){
        i = i % countD;
        //Make sure i is in bounds
        if(i - 1 < 0){
            left = countD - 1;
        }
        else{
            left = i - 1;
        }
        if(i + 1 >= countD){
            right = 0;
        }
        else{
            right = i + 1;
        }
        if(atomsD[left] == atomsD[right]){
            width += 2;
            //Delete the two things
            //These might not be right order. 
            //Just delete the one that doesn't require changing index first
            if(left > i && right < i){
                deleteAtIndex(atomsD, countD, left);
                deleteAtIndex(atomsD, countD, right);
                i--;
            }
            else if(left < i && right > i){
                deleteAtIndex(atomsD, countD, right);
                deleteAtIndex(atomsD, countD, left);
                i--;
            }
            else if(left > i && right > i){
                if(left > right){
                    deleteAtIndex(atomsD, countD, left);
                    deleteAtIndex(atomsD, countD, right);
                }
                else{
                    deleteAtIndex(atomsD, countD, right);
                    deleteAtIndex(atomsD, countD, left);
                }
                //i doesn't change?
            }
            else if( left < i && right < i){
                if(left > right){
                    deleteAtIndex(atomsD, countD, left);
                    deleteAtIndex(atomsD, countD, right);
                }
                else{
                    deleteAtIndex(atomsD, countD, right);
                    deleteAtIndex(atomsD, countD, left);
                }
                i -= 2;
            }
            else{
                cout << "UHHH something messed up";
            }
            
        }
        else{
            break;
        }
    }
    cout << "I: " << i << "\n";
    center = i - 1;
    return width;
    
}

void subsetArrayCircular(int arr[], int size, int start, int end, int outArr[], int& outSize) {
    int idx = 0; 
    if (start > end) {
        // Starting from start position, loop through array to the first element
        for (int i = start; i < size; i++) {
            outArr[idx] = arr[i];
            idx++;
        }
        // Continue from the last element back to end position
        for (int i = 0; i <= end; i++) {
            outArr[idx] = arr[i];
            idx++;
        }
    }
    // Handle the case when start argument is less than or equal to end argument
    else {
        // Loop through the array from start position to end position
        for (int i = start; i <= end; i++) {
            outArr[idx] = arr[i];
            idx++;
        }
    }
    outSize = idx;
}

int calculateScore(int arr[], int size, int reactions, int& z){
	if(size % 2 != 0){
        return 0;
    }
    if(arr[(size/2) - 1] != arr[size/2]){
        return 0;
    }
    if(size < 2){
        return 0;
    }
	reactions++;
	float m = 1 + (0.5 * float(reactions));
	if(reactions == 1){
		z = arr[size/2];
		if(size == 2){
			return floor(m * float(z + 1));
		}
		else{
			for(int i = (size/2) + 1; i < size + 1; i++){
				arr[i-2] = arr[i];
			}
			z = z + 1;
			return floor(m * float(z)) + calculateScore(arr, size - 2, reactions, z);
		}
	}
	else{
		int zo = arr[size/2];
		int subScore = floor(m * float(z + 1));
		
		int bonus = 2.0 * m * float(zo - z + 1);
		if(zo >= z){
			subScore += bonus;
		}
		//cout << "R: " << reactions << " subScore: " << subScore << "\n";
		if(zo < z){
			z = z + 1;
		}
		else{
			z = zo + 2;
		}
		for(int i = (size/2) + 1; i < size + 1; i++){
			arr[i-2] = arr[i];
		}
		return subScore + calculateScore(arr, size - 2, reactions, z);
	}
}

void addAtIndex(int index, int value) {
    if(index <  MAX_ARRAY_SIZE && index >= 0) {
        // shift elements to the right of the index to make space
        for (int i =  MAX_ARRAY_SIZE-1; i > index; i--) {
            atoms[i] = atoms[i - 1];
        }
        // insert new value
        atoms[index] = value;
        count++;
    }
}

void addScoreAtoms(int index, int value){
    if(index <  MAX_ARRAY_SIZE && index >= 0) {
        // shift elements to the right of the index to make space
        for (int i =  MAX_ARRAY_SIZE-1; i > index; i--) {
            scoreAtoms[i] = scoreAtoms[i - 1];
        }
        // insert new value
        scoreAtoms[index] = value;
        scoreAtomsCount++;
    }
}


int deleteSymmetry(int center, int width){
    //printArray(atoms);
    //addAtIndex(0, atoms[center]);
	deleteAtIndex(atoms, count, center);
	//printArray(atoms);
	scoreAtomsCount = 0;
	//cout << "Width: " << width << "\n";
	for(int i = 0; i < width/2; i++){
	    center--;
	    addScoreAtoms(0, atoms[center]);
        deleteAtIndex(atoms, count, center);
        //printArray(atoms);
        addScoreAtoms(scoreAtomsCount, atoms[center]);
        deleteAtIndex(atoms, count, center);
        //printArray(atoms);
	}
	return center;
}

int calculateCircularDistance(int start, int end, int length) {
  if(start == end) 
    return 0;
  else if (start < end) 
    return (end - start == 1) ? length + 1 : (end - start) + 1;
  else
    return (start - end == 1) ? length + 1 : (length - start + end) + 1;
}

void addThings(){
	while(hasPlus(atoms)){
		int i = 0;
		for(; i < count; i++){
			if(atoms[i] == -1){
				break;
			}
		}
		if(atoms[i] == -1){
			int start, end;
			//This width probably isn't correct
			//int width = findSymmetry(i);
			//int width = getPlusSymmetry(atoms, count, i, start, end);
			int realMiddle;
			int width = sym(i, realMiddle);
			cout << "Width: " << width << "\n";
            //width = calculateCircularDistance(start, end, count);
			int endMiddle = deleteSymmetry(i, width);
			cout << "EndMiddle: " << endMiddle << "\n";
			int outAtom;
			int subScore = calculateScore(scoreAtoms, scoreAtomsCount, 0, outAtom);
			cout << "outAtom: " << outAtom << "\n";
			currentScore += subScore;
			
			
			if(count == 0){
				addAtIndex(0, outAtom);
			}
			else{
				//addAtIndex(endMiddle, outAtom);
				addAtIndex(realMiddle, outAtom);
			}
		}
	}
}








int main()
{

    // int width = calculateCircularDistance(4,2,10);
    // cout << width;
    // int middle = deleteSymmetry(5, 6);
    // addAtIndex(middle, 8);
    // printArray(scoreAtoms, scoreAtomsCount);
    printArray(atoms);
    addThings();
    printArray(atoms);
    // // cout << "currentScore: " << currentScore << "\n";
    // int testarr[20] = {2,1,2,3,1,1,3,2,1,2};
    // int out;
    // int s = calculateScore(testarr, 10, 0, out);
    // cout << s << "\n";
    // cout << "Out atom: " << out << "\n";
    // printArray(atoms);
    // addThings();
    // printArray(atoms);
}
