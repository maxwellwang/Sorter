#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define DEBUG 1

int main(int argc, char* argv[]) {
	// handle input errors
	if (argc != 3) {
		printf("Fatal Error: Expected 2 arguments, had %d\n", argc - 1);
		return 1;
	}
	if (strcmp(argv[1], "-i") && strcmp(argv[1], "-q")) {
		printf("Fatal Error: Invalid flag entered, enter -i for insertion sort or -q for quicksort\n");
		return 1;
	}
	int fd = open(argv[2], O_RDONLY);
	if (fd == -1) {
		printf("Fatal Error: Invalid file path entered\n");
		return 1;
	}
	
	if (DEBUG) {
		printf("Flag: %s\n", argv[1]);
		printf("File Path: %s\n", argv[2]);
	}
	
	return 0;
}
