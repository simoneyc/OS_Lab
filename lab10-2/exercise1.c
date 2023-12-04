#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

static __thread int glob = 0;
int cnt = 0;

static void *incr(void *loop){
	int loc,j;
	for(j=0; j < *(int*)loop; j++){
		loc = glob;
		loc++;
		glob = loc;
	}
	cnt++;
	printf("thread %d ,glob=%d\n",cnt,glob);
	
	pthread_exit(NULL);
}

int main(){
	cnt = 0;	
	int p1 = 50, p2 = 100;
	pthread_t id[2];
	
	printf("(main thread) glob value before run 2 threads %d\n",glob);
	pthread_create(&id[0],NULL,incr,&p1);
	
	pthread_create(&id[1],NULL,incr,&p2);
	
	pthread_join(id[0],NULL);
	pthread_join(id[1],NULL);
	
	printf("(main thread) glob value after run 2 threads %d\n",glob);

	return 0;
}
