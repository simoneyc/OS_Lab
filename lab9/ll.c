#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

long int count=0;

void *PrintHello(void *arg){

//printf("This is Hello THread\n");


	for(int i=0; i < *(int*)arg; i++)
	count++;
	printf("Thread ID:%lu complete, ", pthread_self());
	printf("count is:%ld\n", count);

	pthread_exit(NULL);

}

int main()

{

	pthread_t t1, t2, t3, t4;

	int rc, t=25000000;

	void *ret;

	rc=pthread_create(&t1, NULL, PrintHello, &t);

	if(rc) {

		printf("CREATE ERROR");

		exit(-1);

	}





	rc=pthread_create(&t2, NULL, PrintHello, &t);

	if(rc) {

		printf("CREATE ERROR");

		exit(-1);

	}



	rc=pthread_create(&t3, NULL, PrintHello, &t);

	if(rc) {

		printf("CREATE ERROR");

		exit(-1);

	}



	rc=pthread_create(&t4, NULL, PrintHello, &t);

	if(rc) {

		printf("CREATE ERROR");

		exit(-1);

	}

	rc=pthread_join(t1, &ret);
	if(rc)
	{
		printf("JOIN ERROR");
		exit(-1);
	}
	rc=pthread_join(t2, &ret);

	if(rc)
	{

		printf("JOIN ERROR");

		exit(-1);

	}

	rc=pthread_join(t3, &ret);

	if(rc)

	{
		printf("JOIN ERROR");
		exit(-1);
	}
	rc=pthread_join(t4, &ret);
	if(rc)

	{

		printf("JOIN ERROR");

		exit(-1);

	}

	//printf("return value:%d\n", (int)ret);

	printf("final count value:%ld\n", count);

	return 0;

}
