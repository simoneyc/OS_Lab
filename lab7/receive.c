#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>

#define NAME "/myMsgQueue"
#define MAX_MSGSIZE 1000

int main() {
	mqd_t mqd = mq_open(NAME, O_RDONLY|O_CREAT, 0644, NULL);

	if(mqd == -1) {
		perror("Failed to open or create the message queue. \n");
		return 1;
	}
	
	while(1) {
		char buffer[MAX_MSGSIZE];
		ssize_t msg_size = mq_receive(mqd, buffer, 8192, NULL);
		
		if(msg_size == -1) {
			perror("Failed to send a message. \n");
			return 1;
		}
		if(strncmp(buffer, "exit", 4) == 0) {
			break;
		}
		
		printf("received: %s", buffer);
		
	}

	int close = mq_close(mqd);
	if(close == -1) {
		perror("Failed to close the message queue. \n");
		return 1;
	}

	int unlink = mq_unlink(NAME);
	if(unlink == -1) {
		perror("Failed to unlink the message queue. \n");
		return 1;
	}
	
	printf("Exiting receive...\n");
	return 0;
}
