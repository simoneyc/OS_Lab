#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mtx;
pthread_cond_t cond1, cond2, cond3, cond4;

void *print8(void* arg) {
	while(1) {
		pthread_cond_wait(&cond1, &mtx);
		
		printf("8 ");
		
		pthread_cond_signal(&cond2);
	}
}

void *print9(void* arg) {
	while(1) {
		pthread_cond_wait(&cond2, &mtx);
		
		printf("9 ");
		
		pthread_cond_signal(&cond3);
	}
}

void *print6(void* arg) {
	while(1) {
		pthread_cond_wait(&cond3, &mtx);
		
		printf("6 ");
		
		pthread_cond_signal(&cond4);
	}
}

void *print4(void* arg) {
	while(1) {
		pthread_cond_wait(&cond4, &mtx);
		
		printf("4 ");
		
		pthread_cond_signal(&cond1);
	}
}

int main(void) {
	int p;
	pthread_mutex_init(&mtx, NULL);
	
	pthread_cond_init(&cond1, NULL);
	pthread_cond_init(&cond2, NULL);
	pthread_cond_init(&cond3, NULL);
	pthread_cond_init(&cond4, NULL);
	
	pthread_t t1, t2, t3, t4;
	
	pthread_create(&t1, NULL, print8, NULL);
	pthread_create(&t2, NULL, print9, NULL);
	pthread_create(&t3, NULL, print6, NULL);
	pthread_create(&t4, NULL, print4, NULL);
	
	sleep(1);
	pthread_cond_signal(&cond1);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	
	pthread_mutex_destroy(&mtx);
	
	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond2);
	pthread_cond_destroy(&cond3);
	pthread_cond_destroy(&cond4);
	
	return 0;
}
