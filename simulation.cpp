/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;
int atoms[20] = {3,-1,3,2,4,1,5,2};
int count = 8;
int currentScore = 0;

void deepCopyArray(int* source, int* dest, int size) {
  for (int i = 0; i < size; i++) {
    dest[i] = source[i];
  }
}

void deleteAtIndex(int atoms[], int& c, int index) {
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

int getPlusSymmetry(int arr[], int len, int i, int &start, int &end){
	//Middle needs to be a plus
	if(arr[i] != -1){
		return 0;
	}
	if(len < 3){
		return 0;
	}
	start = i - 1 < 0 ? len -1 : i - 1; // use length-1 (last item), if next start position is out of bounds
	end = i + 1 >= len ? 0 : i + 1; // use 0 (first item), if next end position is out of bounds
	if(arr[start] != arr[end]){
		return 0;
	}
	int counter=0; // added a counter here
	while(arr[(start + len - 1) % len] == arr[(end + 1) % len]){
		//Break if plus is found
		if(arr[(start + len - 1) % len] == -1 || arr[(end + 1) % len] == -1) break;
		if(counter==len) break; // if counter equals length of array, break the loop
		start = (start + len - 1) % len; // use mod to circle back to end if out of bounds
		end = (end + 1) % len; // use mod to circle back to start if out of bounds
		counter++;
	}
	return counter;
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
			int width = getPlusSymmetry(atoms, count, i, start, end);
			int subset[20];
			int subsetSize;
			subsetArrayCircular(atoms, count, start, end, subset, subsetSize);
			int outAtom;
			deleteAtIndex(subset, subsetSize, subsetSize/2);
			int subScore = calculateScore(subset, subsetSize, 0, outAtom);
			currentScore += subScore;
			int tempArray[20];
			int newSize = deleteFromCircularArrayAndInsert(atoms, count, i, width, tempArray, outAtom);
			deepCopyArray(tempArray, atoms, newSize);
			count = newSize;
		}
	}
}


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







int main()
{
    int testArr[20] = {2,1,1,2};
    int out;
    int s = calculateScore(testArr, 4, 0, out);
    cout << s << "\n";
    printArray(atoms);
    addThings();
    printArray(atoms);
    cout << 5/2;
}
