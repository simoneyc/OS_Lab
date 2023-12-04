#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/msg.h>

#define MAX_SIZE 1000
#define MSG_FILE "/etc/passwd"

struct msg_form {
	long mtype;
	char mtext[MAX_SIZE];
};

int msqid;
pthread_t thsender, threceiver;

void *sender(void *arg) {
	struct msg_form msg;
	while(1) {
		msg.mtype = 2;
		printf("<Enter some text>\n");
		scanf("%s", msg.mtext);
		msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
		if(strcmp(msg.mtext, "exit") == 0) {
			break;
		}
	}
	pthread_cancel(threceiver);
	pthread_exit(NULL);
}

void *receiver(void *arg) {
	struct msg_form msg;
	while(1) {		
		msgrcv(msqid, &msg, MAX_SIZE, 1, 0);
		printf("Received: %s\n\n", msg.mtext);
		if(strcmp(msg.mtext, "exit") == 0) {
			break;
		}
	}
	pthread_cancel(thsender);
	pthread_exit(NULL);
}

int main() {
	key_t key;
	struct msg_form msg;

	if((key = ftok(MSG_FILE,'z')) < 0) {
		perror("ftok error");
		exit(-1);
	}
	if((msqid = msgget(key, IPC_CREAT|0777)) == -1) {
		perror("msgget error");
                exit(-1);
	}

	int r;
	r = pthread_create(&thsender, NULL, sender, NULL);
	if(r) {
		printf("CREATE ERROR");
		exit(-1);
	}
	r = pthread_create(&threceiver, NULL, receiver, NULL);
	if(r) {
		printf("CREATE ERROR");
		exit(-1);
	}

	void *ret;
	r = pthread_join(thsender, &ret);
	if(r) {
		printf("JOIN ERROR\n");
		exit(-1);
	}
	r = pthread_join(threceiver, &ret);
        if(r) {
                printf("JOIN ERROR\n");
                exit(-1);
        }

	return 0;
}
