#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mtx;
pthread_cond_t cond1, cond2, cond3;

static void *print1(void *arg) {
	while(1) {
		pthread_cond_wait(&cond1, &mtx);
		
		printf("1 ");
		
		pthread_cond_signal(&cond2);
	}
	
	pthread_exit(NULL);
}

static void *print3(void *arg) {
	
	while(1) {
		pthread_cond_wait(&cond2, &mtx);
		
		printf("3 ");
		
		pthread_cond_signal(&cond3);
	}
	
	pthread_exit(NULL);
}

static void *print5(void *arg) {
	while(1) {
		pthread_cond_wait(&cond3, &mtx);
		
		printf("5 ");
		
		pthread_cond_signal(&cond1);
	}
	
	pthread_exit(NULL);
}

int main(void) {
	pthread_t th1, th2, th3;
	
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond1, NULL);
	pthread_cond_init(&cond2, NULL);
	pthread_cond_init(&cond3, NULL);	
	
	pthread_create(&th1, NULL, print1, NULL);
	pthread_create(&th2, NULL, print3, NULL);
	pthread_create(&th3, NULL, print5, NULL);
	
	sleep(1);
	pthread_cond_signal(&cond1);
	
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);
	
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond2);
	pthread_cond_destroy(&cond3);
	
	return 0;
}
