# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

int glo = 10;

int main(int argc, char **argv){
	int loc = 10;
	printf("I'm parent process\n");
	printf("pid : %d	parent id : %d\n",getpid(), getppid());
	printf("global : %d, local : %d\n",glo,loc);		
	printf("Finally print : pid = %d, parent id = %d, global = %d, local = %d\n",getpid(),getppid(),glo,loc);	
	
	if(fork()==0){
		printf("I'm child process\n");
		printf("pid : %d, parent id : %d\n",getpid(), getppid());
		printf("global : %d, local : %d\n",glo,loc);	
		loc += 1;
		glo += 1;
		printf("Finally print : pid = %d, parent id = %d, global = %d, local = %d\n",getpid(),getppid(),glo,loc);	
		return 0;
	}
	wait(NULL);
	return 0;
}
