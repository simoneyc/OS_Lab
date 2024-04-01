#include<stdio.h>
#include "lib.h"

int main() {
	int array[] = {12, 5, 7, 26, 18};
	printf("Before sort: ");
	for(int i = 0; i < 5; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	
	sort(array, 5);
	
	printf("After sort: ");
	for(int i = 0; i < 5; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	
	return 0;
}
