#include<arpa/inet.h>

#include<netinet/in.h>

#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include<sys/socket.h>

#include<sys/types.h>

#include<unistd.h>



#define PORT 3009

#define MSG "hello from server"

#define MAX_SIZE 1000



int main(int argc,char *argv[]){

	int num=0;

	int socket_fd;

	int count;

	count=atoi(argv[1]);

	//printf("count: %d\n",count);

	//printf("msg: %s\n",argv[2]);

	

	struct sockaddr_in server_addr, client_addr;

	socklen_t addr_len;

	ssize_t bytes_send, bytes_recv;

	char buffer[MAX_SIZE];

	

	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

	if(socket_fd == -1){

		perror("Failed to create the socket");

		return 1;

	}

	

	memset(&buffer, '\0', sizeof(buffer));

	memset(&server_addr, 0, sizeof(server_addr));

	memset(&client_addr, 0, sizeof(client_addr));

	addr_len = sizeof(client_addr);

	

	server_addr.sin_family = AF_INET;

	server_addr.sin_port = htons(PORT);

	server_addr.sin_addr.s_addr = INADDR_ANY;

	

	if(bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){

		perror("Failed to bind the socket");

		return 1;

	}

	

	while(num < count){

		bytes_recv = recvfrom(socket_fd, buffer, MAX_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len); // pid

		

		

		//if(strncmp(buffer,"exit\n",5) == 0){

		//	break;

		//}

		//

		if(bytes_recv == -1){

			perror("Failed to receive the socket");

			return 1;

		}

		buffer[bytes_recv] = '\0';

		

		

		bytes_send = sendto(socket_fd, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&client_addr, addr_len);

		if(bytes_send == -1){

			perror("Failed to send the socket");

			return 1;

		}

		

		printf("Client %d: %s\n",num, buffer);

		num++;

	}

	printf("All client are ready, send the response.\n");

	

	close(socket_fd);

	return 0;

}