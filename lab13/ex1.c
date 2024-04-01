#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int glob = 0;
pthread_mutex_t mtx;

static void *inc(void *arg) {
	int loop = *((int*) arg);
	int loc;
	
	for(int i = 0; i < loop; i++) {
		if(pthread_mutex_lock(&mtx) != 0) {
			printf("inc pthread_mutex_lock error\n");
			exit(0);
		}
		
		loc = glob;
		loc += 2;
		glob = loc;
		
		if(pthread_mutex_unlock(&mtx) != 0) {
			printf("inc pthread_mutex_unlock error\n");
			exit(0);
		}
	}
	
	pthread_exit(NULL);
}

static void *dec(void *arg) {
	int loop = *((int*) arg);
	int loc;
	
	for(int i = 0; i < loop; i++) {
		if(pthread_mutex_lock(&mtx) != 0) {
			printf("dec pthread_mutex_lock error\n");
			exit(0);
		}
		
		loc = glob;
		loc -= 2;
		glob = loc;
		
		if(pthread_mutex_unlock(&mtx) != 0) {
			printf("dec pthread_mutex_unlock error\n");
			exit(0);
		}
	}
	
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	pthread_t th1, th2, th3;
	int loop;
	
	loop = atoi(argv[1]);
	
	pthread_mutex_init(&mtx, NULL);
	
	pthread_create(&th1, NULL, inc, &loop);
	pthread_create(&th2, NULL, dec, &loop);
	pthread_create(&th3, NULL, inc, &loop);
	
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);
	
	printf("glob = %d\n", glob);
	
	pthread_mutex_destroy(&mtx);
	
	return 0;
}
