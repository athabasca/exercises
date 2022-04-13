#include <stdio.h>

void print_array(int* array, unsigned int length) {
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

unsigned int partition(int* array, unsigned int low, unsigned int high) {
	int temp;
	int pivot = array[low + ((high - low)/2)];
	int i = low - 1, j = high + 1;

	while (1) {
		do { i++; } while (array[i] < pivot);
		do { j--; } while (array[j] > pivot);
		if ( i >= j) {
			return j;
		}
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

void quicksort(int* array, unsigned int low, unsigned int high) {
	if (low >= high) { return; }

	unsigned int pivot = partition(array, low, high);

	quicksort(array, low, pivot);
	quicksort(array, pivot + 1, high);
}



int main(void) {
	int array[] = { -2, -4, 5, 3, 20, -15, 2, 0, 5, 13, -1, 7};
	int sorted[] = { -15, -4, -2, -1, 0, 2, 3, 5, 5, 7, 13, 20};
	unsigned int length = 12;

	quicksort(array, 0, length - 1);

	char success = 1;
	for (int i = 0; i < length; i++) {
		if (array[i] != sorted[i]) {
			success = 0;
			break;
		}
	}

	if (1 == success) {
		puts("Sort works");
	}
	else {
		puts("Sort error");
		print_array(sorted, length);
	}
}
