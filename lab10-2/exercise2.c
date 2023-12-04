#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int* result;
void* child(void* arg) {
	printf("child thread:\n");
	int* input = (int*) arg;
	result = malloc(sizeof(int)*1);
	*result = input[0] + input[1];
	int i = 1;
	for(i = 1; i <= 3; i++) {
		sleep(1);
		printf("sleep: %d\n", i);
	}
	pthread_exit((void*) result);
}

int main() {
	pthread_t t;
	void *ret;
	int input[2] = {1, 2};
	pthread_create(&t, NULL, child, (void*) input);

	pthread_join(t,&ret);

	int r = pthread_cancel(t);
	if(r) {
		printf("pthread_cancel fail\n");
		return 0;
	}
	else {
		printf("pthread_cancel successfully\n");	
	}
	
	printf("main thread:\n");
	printf("%d + %d = %d\n", input[0], input[1], *result);
	
	free(result);
	return 0;
}
