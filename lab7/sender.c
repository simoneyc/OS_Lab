#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <mqueue.h>

#define NAME "/myMsgQueue"
#define MAX_MSGSIZE 1000

int main() {
	mqd_t mqd = mq_open(NAME, O_WRONLY | O_CREAT, 0644, NULL);;
	
	
	if(mqd == -1) {
		perror("Failed to open or create the message queue. \n");
		return 1;
	}
	
	
	while(1) {
		char buffer[MAX_MSGSIZE];
		for(int i = 0; i < sizeof(buffer); i++) {
			buffer[i] = '\0';
		}
		printf("send to receiver: \n");
		printf("> ");
		fgets(buffer, MAX_MSGSIZE, stdin);
		
		int send = mq_send(mqd, buffer, strlen(buffer) + 1, 0);
		if(send == -1) {
			perror("Failed to send a message. \n");
			return 1;
		}
		if(strncmp(buffer, "exit", 4) == 0) {
			break;
		}
	}

	return 0;
}
