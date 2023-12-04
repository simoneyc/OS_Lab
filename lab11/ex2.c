#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void SIGALRM_handler2() {
	signal(SIGINT, SIG_DFL);
	printf("Terminating the process after switching to handler2 for 3 seconds.\n");
}

void SIGINT_handler2() {
	signal(SIGINT, SIGINT_handler2);
	printf("Handler 2: I AM FINE!\n");
}

void SIGALRM_handler1() {
	signal(SIGINT, SIGINT_handler2);
	alarm(3);
	signal(SIGALRM, SIGALRM_handler2);
	
}

void SIGINT_handler1() {
	signal(SIGINT, SIGINT_handler1);
	printf("Handler 1: HOW ARE YOU?\n");
}

int main(void) {
	signal(SIGINT, SIGINT_handler1);
	alarm(3);
	signal(SIGALRM, SIGALRM_handler1);
	
	
	for(;;) {
		pause();
	}
	//printf("Terminating the process after switching to handler2 for 3 seconds.\n");

	return 0;
}
