#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

sem_t mutex;
int count = 0;

void inc(void);
void dec(void);

int main(void) {
	sem_init(&mutex, 0, 1);
	int i = 0;
	pthread_t id[4];
	pthread_create(&id[0],NULL,(void*)dec,NULL);
	pthread_create(&id[1],NULL,(void*)inc,NULL);
	pthread_create(&id[2],NULL,(void*)dec,NULL);
	pthread_create(&id[3],NULL,(void*)inc,NULL);
	for(i=0; i<4; i++) {
		pthread_join(id[i], NULL);
	}
	printf("\noutput is %d\n",count);
	sem_destroy(&mutex);
	return 0;
}

void inc(void) {
	sem_wait(&mutex);
	int i = 0;
	for(i=0; i<25000000; i++) {
		count++;
	}
	sem_post(&mutex);
	pthread_exit(NULL);
}

void dec(void) {
	sem_wait(&mutex);
	int i = 0;
	for(i=0; i<25000000; i++) {
		count--;
	}
	sem_post(&mutex);
	pthread_exit(NULL);
}

