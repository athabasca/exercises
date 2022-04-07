int removeElement(int* nums, int numsSize, int val){
    int src = 0, dst = 0;
    while (src < numsSize && val != nums[src]) {
        src++; dst++;
    }
    
    while (1) {
        while (src < numsSize && val == nums[src]) {
            src++;
        }
        if (numsSize == src) {
            break;
        }
        nums[dst] = nums[src];
        dst++;    
	src++;
    }
    return dst;
    /* Simpler solution:
     * int i, count = 0;
     * for (i = 0; i < numsSize; i++) {
     * 	nums[i-count] = nums[i];
     * 	if (nums[i] == val) { count++; }
     * }
     * return numsSize - count;
}

int main(void) {
	int array[] = {3, 2, 2, 3};
	int size = 4;
	int toRemove = 3;

	removeElement(array, size, toRemove);

	return 0;
}
