// Use this to get hex file:
// arduino-cli compile --fqbn arduboy:avr:arduboy .\a_atomas --output-dir ./
#include <Arduboy2.h>

bool verify(char before[], char expected[], byte c1, byte c2) {
	tinyfont.print(",");
	char after[50];
	deepCopy(before, after, c1);
	evaluatePlus(after);
	// printArray(after);
	for (char i = 0; i < c2; i++) {
		// tinyfont.print(after[i]);
		// tinyfont.print("=");
		// tinyfont.print(expected[i]);
		if (after[i] != expected[i]) {
			return false;
		}
	}
	return true;
}

void deepCopy(char arr[], char copy[], byte count) {
	for (char i = 0; i < count; i++) {
		copy[i] = arr[i];
	}
}

bool tests() {
	char b1[1] = {-1};
	char f1[1] = {-1};
	tinyfont.print(verify(b1, f1, 1, 1));
	char b2[2] = {-1, 1};
	char f2[2] = {-1, 1};
	tinyfont.print(verify(b2, f2, 2, 2));
	char b3[2] = {-1, -1};
	char f3[2] = {-1, -1};
	tinyfont.print(verify(b3, f3, 2, 2));
	char b4[3] = {1, -1, 1};
	char f4[3] = {2};
	tinyfont.print(verify(b4, f4, 3, 1));
	char b5[3] = {-1, 1, 1};
	char f5[3] = {2};
	tinyfont.print(verify(b5, f5, 3, 1));
	char b6[4] = {4, 1, -1, 1};
	char f6[4] = {4, 2};
	tinyfont.print(verify(b6, f6, 4, 2));
	// This one broken?
	char b7[4] = {1, 4, 1, -1};
	char f7[4] = {2, 4};
	tinyfont.println();
	tinyfont.print(verify(b7, f7, 4, 2));
	char b8[4] = {-1, 1, 4, 1};
	char f8[4] = {2, 4};
	tinyfont.print(verify(b8, f8, 4, 2));
	char b9[5] = {2, 1, -1, 1, 2};
	char f9[5] = {3};
	tinyfont.print(verify(b9, f9, 5, 1));
	char b10[5] = {1, 2, 1, -1, 2};
	char f10[5] = {1, 2, 1, -1, 2};
	tinyfont.print(verify(b10, f10, 5, 5));
	char b11[5] = {1, -1, 1, 2, 3};
	char f11[5] = {2, 2, 3};
	tinyfont.print(verify(b11, f11, 5, 3));
	char b12[5] = {1, -1, 1, 3, 2};
	char f12[5] = {2, 3, 2};
	tinyfont.print(verify(b12, f12, 5, 3));
	char b13[5] = {1, 3, 2, 1, -1};
	char f13[5] = {3, 4, 2};
	tinyfont.print(verify(b13, f13, 5, 3));
}
