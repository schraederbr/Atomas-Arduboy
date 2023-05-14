// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\drawing.ino --output-dir ./
#include <Arduboy2.h>

bool verify(int before[], int expected[], int c1, int c2)
{
	arduboy.print(",");
	int after[50];
	deepCopy(before, after, c1);
	evaluatePlus(after);
	// printArray(after);
	for (int i = 0; i < c2; i++)
	{
		// arduboy.print(after[i]);
		// arduboy.print("=");
		// arduboy.print(expected[i]);
		if (after[i] != expected[i])
		{
			return false;
		}
	}
	return true;
}

void deepCopy(int arr[], int copy[], int count)
{
	for (int i = 0; i < count; i++)
	{
		copy[i] = arr[i];
	}
}

bool tests()
{
	int b1[1] = {-1};
	int f1[1] = {-1};
	arduboy.print(verify(b1, f1, 1, 1));
	int b2[2] = {-1, 1};
	int f2[2] = {-1, 1};
	arduboy.print(verify(b2, f2, 2, 2));
	int b3[2] = {-1, -1};
	int f3[2] = {-1, -1};
	arduboy.print(verify(b3, f3, 2, 2));
	int b4[3] = {1, -1, 1};
	int f4[3] = {2};
	arduboy.print(verify(b4, f4, 3, 1));
	int b5[3] = {-1, 1, 1};
	int f5[3] = {2};
	arduboy.print(verify(b5, f5, 3, 1));
	int b6[4] = {4, 1, -1, 1};
	int f6[4] = {4, 2};
	arduboy.print(verify(b6, f6, 4, 2));
	// This one broken?
	int b7[4] = {1, 4, 1, -1};
	int f7[4] = {2, 4};
	arduboy.println();
	arduboy.print(verify(b7, f7, 4, 2));
	int b8[4] = {-1, 1, 4, 1};
	int f8[4] = {2, 4};
	arduboy.print(verify(b8, f8, 4, 2));
	int b9[5] = {2, 1, -1, 1, 2};
	int f9[5] = {3};
	arduboy.print(verify(b9, f9, 5, 1));
	int b10[5] = {1, 2, 1, -1, 2};
	int f10[5] = {1, 2, 1, -1, 2};
	arduboy.print(verify(b10, f10, 5, 5));
	int b11[5] = {1, -1, 1, 2, 3};
	int f11[5] = {2, 2, 3};
	arduboy.print(verify(b11, f11, 5, 3));
	int b12[5] = {1, -1, 1, 3, 2};
	int f12[5] = {2, 3, 2};
	arduboy.print(verify(b12, f12, 5, 3));
	int b13[5] = {1,3,2,1,-1};
	int f13[5] = {3, 4, 2};
	arduboy.print(verify(b13, f13, 5, 3));
}
