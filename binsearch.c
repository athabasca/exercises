#include <stdio.h>

unsigned int binary_search(int* array, unsigned int length, int value) {
	int low, mid, high;
	low = 0;
	high = length - 1;

	while (low <= high) {
		mid = low + ((high - low)/2);
		if (value == array[mid]) {
			return 1;
		}
		else if (value < array[mid]) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return 0;
}

int main(void) {
	int array[] = {-5, -2, -1, 0, 1, 4, 5, 8};
	unsigned int length = 8;
	int present = -1, notpresent = 9;

	if (binary_search(array, length, present) == 1) {
		printf("Found present value\n");
	}
	else {
		printf("Didn't find present value\n");
	}

	if (binary_search(array, length, notpresent) == 1) {
		printf("Found nonpresent value\n");
	}
	else {
		printf("Didn't find nonpresent value\n");
	}
	return 0;	
}
