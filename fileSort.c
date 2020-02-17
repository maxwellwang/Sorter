#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
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
	// buffer for reading one char at a time
	char c = '?';
	// buffer for elements
	char* buffer = malloc(1);
	if (buffer == NULL) {
		printf("Malloc failed\n");
		return 0;
	}
	// updated buffer which can hold one more char than previous buffer
	char* nextBuffer;
	int elementFound = 0;
	int fileEmpty = 1;
	int status = 0;
	// int (*compPtr)(void*, void*) = comparator;
	
	// handle input errors
	if (argc != 3) {
		printf("Fatal Error: Expected 2 arguments, had %d\n", argc - 1);
		return 0;
	}
	
	if (argv[1][0] != '-' || (argv[1][1] != 'i' && argv[1][1] != 'q') || argv[1][2] != '\0') {
		printf("Fatal Error: \"%s\" is not a valid sort flag, enter \"-i\" for insertion sort or \"-q\" for quicksort\n", argv[1]);
		return 0;
	}
	int fd = open(argv[2], O_RDONLY);
	if (fd == -1) {
		perror("Fatal Error");
		return 0;
	}
	if (DEBUG) {
		printf("Flag: %s\n", argv[1]);
		printf("File Path: %s\n", argv[2]);
	}
	
	// read from file
	while (read(fd, &c, 1) > 0) {
		if (fileEmpty) {
			fileEmpty = 0;
		}
		
		// assign type when integer/string is found, and create appropriate buffer
		if (elementFound == 0 && isalpha(c)) {
			elementFound = 1;
		} else if (elementFound == 0 && isdigit(c)) {
			elementFound = 1;
		}
		
		if (isalpha(c) || isdigit(c) || c == ',') {
			// realloc to allow one more char
			if (DEBUG) {
				printf("Size of buffer: %d\n", (int)(sizeof(buffer)));
			}
			nextBuffer = malloc(sizeof(buffer) + 1);
			if (nextBuffer == NULL) {
				printf("Malloc failed\n");
				return 0;
			}
			memcpy(nextBuffer, buffer, sizeof(buffer) + 0);
			free(buffer);
			buffer = nextBuffer;
			nextBuffer = NULL;
			
			sprintf(buffer + sizeof(buffer) - 1, "%c", c);
			if (DEBUG) {
				printf("Printed %c at position %d\n", c, (int)(sizeof(buffer) - 1));
			}
		}
	}
	if (fileEmpty) {
		printf("Warning: File is empty\n");
	}
	if (!elementFound) {
		printf("Warning: No integers/strings found in file\n");
	}
	
	if (DEBUG) {
		int i;
		for (i = 0; i < sizeof(buffer); i++) {
			printf("%c", buffer[i]);
		}
	}
	
	status = close(fd);
	if (status == -1) {
		perror("Error");
	}
	
	free(buffer);
	return 0;
}
