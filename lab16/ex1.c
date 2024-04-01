#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	int freeframe[16] = {0};
	char logic1[3][2] = {{'a','b'},{'e','f'},{'c','d'}};
	char logic2[3][2] = {{'r','x'},{'y','y'},{'z','z'}};
	int record[6] = {-1,-1,-1,-1,-1,-1};
	// first process
	for(int i = 0; i < 3; i++) {
		srand(time(NULL));
		while(1) {
			int a = rand()%16;
			if(freeframe[a] == 0) {
				record[i] = a;
				freeframe[a] = 1;
				break;
			}
		}
	}
	// second process
	for(int i = 3; i < 6; i++) {
		srand(time(NULL));
		while(1) {
			int a = rand()%16;
			if(freeframe[a] == 0) {
				record[i] = a;
				freeframe[a] = 1;
				break;
			}
		}
	}
	printf("process A's logical memory\n");
	printf("page	data\n");
	for(int i = 0; i < 3; i++) {
		printf("%d	%c%c\n", i, logic1[i][0], logic1[i][1]);
	}
	
	printf("process A's page table\n");
	for(int i = 0; i < 3; i++) {
		printf("%d	%d\n", i, record[i]);
	}
	printf("process B's logical memory\n");
        printf("page    data\n");
        for(int i = 0; i < 3; i++) {
                printf("%d	%c%c\n", i, logic2[i][0], logic2[i][1]);
        }

        printf("process B's page table\n");
        for(int i = 0; i < 3; i++) {
                printf("%d	%d\n", i, record[i+3]);
        }
        printf("physical memory:\n");
        printf("frame	offset	data\n");
        for(int i = 0; i < 16; i++) {
		int process = -1;
		int page = -1;
		for(int j = 0; j < 3; j++) {
			if(i == record[j]) {
				process = 0;
				page = j;
				break;
			}
			if(i == record[j+3]) {
				process = 1;
				page = j;
				break;
			}
		}
		if(process == 0) {
			printf("%d	0	%c\n", i, logic1[page][0]);
			printf("%d	1	%c\n", i, logic1[page][1]);
		}
		else if(process == 1) {
			printf("%d	0	%c\n", i, logic2[page][0]);
			printf("%d	1	%c\n", i, logic2[page][1]);
		}
		else {
			printf("%d	0	\n", i);
			printf("%d	1	\n", i);
		}
	}
	
	printf("free frame table:\n");
	for(int i = 0; i < 16; i++) {
		if(freeframe[i] == 0) {
			printf("%d ", i);
		}
	}
	printf("\n");
	
	return 0;

}
