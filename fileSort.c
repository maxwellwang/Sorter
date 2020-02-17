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
	
	// holds the current char that was read
	char c = '?';
	// buffer for elements
	char* buffer = malloc(1);
	if (!buffer) {
		printf("Malloc failed\n");
		return 0;
	}
	// where to insert into buffer
	char* head = buffer;
	// updated buffer which can hold one more char than previous buffer
	char* nextBuffer;
	// int (*compPtr)(void*, void*) = comparator;

	
	// read from file
	int elementFound = 0;
	int fileEmpty = 1;
	int written = 0;
	while (read(fd, &c, 1) > 0) {
		if (fileEmpty) {
			fileEmpty = 0;
		}
		if (elementFound == 0 && (isalpha(c) || isdigit(c))) {
			elementFound = 1;
		}
		if (isalpha(c) || isdigit(c) || c == ',') {
			if (head == (buffer + strlen(buffer))) {
				// realloc to allow one more char
				if (DEBUG) {
					printf("Size of buffer: %zu\n", strlen(buffer));
				}
				nextBuffer = malloc(strlen(buffer) + 1);
				if (!nextBuffer) {
					printf("Malloc failed\n");
					return 0;
				}
				memcpy(nextBuffer, buffer, strlen(buffer));
				free(buffer);
				buffer = nextBuffer;
				nextBuffer = NULL;		
			}
			
			written += sprintf(head, "%c", c);
			if (DEBUG) {
				printf("Wrote %c\n", c);
			}
			head = buffer + written;
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
		for (i = 0; i < strlen(buffer); i++) {
			printf("%c", buffer[i]);
		}
	}
	
	int status = close(fd);
	if (status == -1) {
		perror("Error");
	}
	
	free(buffer);
	free(nextBuffer);
	return 0;
}
