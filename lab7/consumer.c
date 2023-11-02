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
	int fd = shm_open(NAME, O_RDONLY, 0666);;

	if(fd == -1) {
		perror("Failed to open or create the shared memory. \n");
		return 1;
	}
	char *map_addr = mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);
	if(map_addr == MAP_FAILED) {
		perror("Failed to read the map. \n");
		return 1;
	}
	printf("%s", map_addr);

	return 0;
}
