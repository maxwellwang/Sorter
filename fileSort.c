#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#define DEBUG 1

int comparator(void* a, void* b) {
	return 0;
}

int insertionSort(void* toSort, int (*comparator)(void*, void*)) {
	return 0;
}
			
int quickSort(void* toSort, int (*comparator)(void*, void*)) {
	return 0;
}

int main(int argc, char* argv[]) {
	char c = '?';
	//int (*compPtr)(void*, void*) = comparator;
	
	// handle input errors
	if (argc != 3) {
		printf("Fatal Error: Expected 2 arguments, had %d\n", argc - 1);
		exit(1);
	}
	
	if (argv[1][0] != '-' || (argv[1][1] != 'i' && argv[1][1] != 'q') || argv[1][2] != '\0') {
		printf("Fatal Error: \"%s\" is not a valid sort flag, enter \"-i\" for insertion sort or \"-q\" for quicksort\n", argv[1]);
		exit(1);
	}
	int fd = open(argv[2], O_RDONLY);
	if (fd == -1) {
		perror("Fatal Error");
		exit(1);
	}
	if (DEBUG) {
		printf("Flag: %s\n", argv[1]);
		printf("File Path: %s\n", argv[2]);
	}
	
	// read from file
	int bytesRead = read(fd, &c, 1);
	if (bytesRead == 0) {
		printf("Warning: File is empty\n");
	}
	while (read(fd, &c, 1) > 0) {
		printf("%c\n", c);
	}
	
	int status = close(fd);
	if (status == -1) {
		perror("Error");
	}
	
	return 0;
}
