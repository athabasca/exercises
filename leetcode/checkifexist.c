#include <stdio.h>
#include <stdbool.h>

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

bool checkIfExist(int* arr, int arrSize){
    unsigned int i;
    quicksort(arr, 0, arrSize - 1);
    for (i = 0; i < arrSize; i++) {
        if (binary_search(arr, arrSize, arr[i]*2)) {
            return true;
        }
        else if (arr[i] % 2 == 0) {
            if (binary_search(arr, arrSize, arr[i]/2)) {
                return true;
            }
        }
    }
    return false;
}

int main(void) {
	int array[] = {10,2,5,3};
	unsigned int length = 4;
	bool result = checkIfExist(array, length);
	printf("result: %s\n", result ? "true" : "false");
}
