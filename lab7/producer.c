#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define NAME "/myShareMemory"
#define SMSIZE 1024

int main() {
	int fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
	if(fd == -1) {
		perror("Failed to open or create the shared memory. \n");
		return 1;
	}
	
	if(ftruncate(fd, SMSIZE) == -1){
		perror("Failed to resize. \n");
		return 1;
	}
	
	void *map_addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(map_addr == MAP_FAILED) {
		perror("Failed to create the map. \n");
		return 1;
	}
	char *ptr, buffer[SMSIZE];
	
	printf("Enter a message: ");
	fgets(buffer, 1024, stdin);
	ptr = map_addr;
	ptr += sprintf(ptr, "%s", buffer);
	
	if(munmap(map_addr, 1024) == -1) {
                perror("Failed to unmap. \n");
		return 1;
        }
	if(close(fd) == -1) {
                perror("Failed to close the shared memory. \n");
		return 1;
        }

	return 0;
}
