#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long int num = 0;
void *countNum(void *arg) {
	for(int i = 0; i < *(int*)arg; i++) {
		num++;
	}
	printf("Thread ID is: %ld complete, count is: %ld\n",pthread_self(), num);
	pthread_exit(NULL);
}

int main() {
	pthread_t th1, th2, th3, th4;
	int r, iter = 25000000;

	r = pthread_create(&th1, NULL, countNum, &iter);
	if(r) {
		printf("CREATE ERROR\n");
		exit(-1);
	}
	r = pthread_create(&th2, NULL, countNum, &iter);
        if(r) {
                printf("CREATE ERROR\n");
                exit(-1);
        }
	r = pthread_create(&th3, NULL, countNum, &iter);
        if(r) {
                printf("CREATE ERROR\n");
                exit(-1);
        }
	r = pthread_create(&th4, NULL, countNum, &iter);
        if(r) {
                printf("CREATE ERROR\n");
                exit(-1);
        }

	void *ret;
	r = pthread_join(th1, &ret);
	if(r) {
		printf("JOIN ERROR\n");
		exit(-1);
	}
	r = pthread_join(th2, &ret);
        if(r) {
                printf("JOIN ERROR\n");
                exit(-1);
        }
	r = pthread_join(th3, &ret);
        if(r) {
                printf("JOIN ERROR\n");
                exit(-1);
        }
	r = pthread_join(th4, &ret);
        if(r) {
                printf("JOIN ERROR\n");
                exit(-1);
        }
	printf("Final count value: %ld\n",num);

	return 0;
}
