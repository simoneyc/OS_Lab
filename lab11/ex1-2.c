#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	
	pid_t pid = fork();
	if(pid < 0) {
		printf("error");
		return 0;
	}
	else if(pid == 0) {
		printf("I am child, pid = %d, ppid = %d\n", getpid(), getppid());
		int a=kill(getppid(), SIGKILL);
		return 0;

	}
	else {
		printf("I am parent, pid = %d, ppid = %d\n", getpid(), getppid());
		wait(NULL);
		return 0;

	}

	return 0;
}
