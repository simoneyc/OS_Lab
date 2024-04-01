#include <stdio.h>
#include "lib.h"

void sort(int array[], int n) {
	for(int i = 0; i < n; i++) {
		int min_index = i;
		for(int j = i+1; j < n; j++) {
			if(array[j] < array[min_index]) {
				min_index = j;
			}
		}
		int temp = array[min_index];
		array[min_index] = array[i];
		array[i] = temp;
	}
}
