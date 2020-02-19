#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define DEBUG 1

typedef struct Node {
	char* data;
	struct Node* next;
} Node;

// prints LL contents
void printLL(Node* front) {
	Node* ptr = front;
	while (ptr != NULL) {
		printf("%s\n", ptr->data);
		ptr = ptr->next;
	}
}

// insert node, insert "elementSize" chars from "data" into LL
void insert(Node** frontPtr, char* data, int elementSize) {
	int j;
	if (*frontPtr == NULL) {
		*frontPtr = malloc(sizeof(Node));
		if (!(*frontPtr)) {
			perror("Error");
		}
		(*frontPtr)->data = malloc(elementSize);
		if ((*frontPtr)->data == NULL) {
			perror("Error");
		}
		for (j = 0; j < elementSize; j++) {
			((*frontPtr)->data)[j] = data[j];
		}
		(*frontPtr)->next = NULL;
	} else {
		Node* temp = malloc(sizeof(Node));
		if (temp == NULL) {
			perror("Error");
		}
		temp->data = malloc(elementSize);
		if (temp->data == NULL) {
			perror("Error");
		}
		for (j = 0; j < elementSize; j++) {
			(temp->data)[j] = data[j];
		}
		temp->next = *frontPtr;
		*frontPtr = temp;
	}
}

// delete front
void delete(Node** frontPtr) {
	if (*(frontPtr) == NULL) {
		return;
	}

	Node* temp = *frontPtr;
	free((*frontPtr)->data);
	*frontPtr = (*frontPtr)->next;
	free(temp);
}

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
	// handle input errors and open file
	if (argc != 3) {
		printf("Fatal Error: Expected 2 arguments, had %d\n", argc - 1);
		exit(0);
	}
	if (argv[1][0] != '-' || (argv[1][1] != 'i' && argv[1][1] != 'q') || argv[1][2] != '\0') {
		printf("Fatal Error: \"%s\" is not a valid sort flag, enter \"-i\" for insertion sort or \"-q\" for quicksort\n", argv[1]);
		exit(0);
	}
	int fd = open(argv[2], O_RDONLY);
	if (fd == -1) {
		perror("Fatal Error");
		exit(0);
	}
	if (DEBUG) {
		printf("Flag: %s\n", argv[1]);
		printf("File Path: %s\n", argv[2]);
	}
	
	// buffer to hold each element, doubles every time limit is reached
	char* buffer = malloc(10);
	if (!buffer) {
		perror("Error");
	}
	// current size of buffer
	int size = 10;
	// size of element being inserted (ignore anything after)
	int elementSize = 0;
	// temporary spot for current char
	char c = '?';
	// where to write new chars
	char* head = buffer;
	// "head" is "written" bytes after "buffer"
	int written = 0;
	// reallocated buffer with double size
	char* nextBuffer;
	// front of LL
	Node* front = NULL;
	// int (*compPtr)(void*, void*) = comparator;
	
	
	// read from file and make LL
	int elementFound = 0;
	while (read(fd, &c, 1) > 0) {
		if (isalpha(c) || isdigit(c)) {
			// add to buffer and increment written
			elementFound = 1;
			*head = c;
			written++;
			elementSize++;
		} else if (c == ',') {
			// element complete, insert into LL
			written = 0;
			insert(&front, buffer, elementSize);
			elementSize = 0;
		}
		
		if (head + 1 == buffer + size) {
			// reached end of buffer, realloc with double size
			nextBuffer = malloc(2 * size);
			size *= 2;
			if (nextBuffer == NULL) {
				perror("Error");
			}
			memcpy(nextBuffer, buffer, strlen(buffer));
			free(buffer);
			buffer = nextBuffer;
		}
		
		head = buffer + written;
	}
	if (c != ',') {
		// insert one element
		insert(&front, buffer, elementSize);
	}
	
	// handle file content warnings
	if (strlen(buffer) == 0) {
		printf("Warning: File is empty\n");
	}
	if (!elementFound) {
		printf("Warning: File does not contain strings nor integers\n");
	}
	
	// close file
	int status = close(fd);
	if (status == -1) {
		perror("Error");
	}
	
	// call sorts here
	
	// print sorted LL
	printLL(front);
	
	// free all malloced memory
	free(buffer);
	while (front != NULL) {
		delete(&front);
	}
	
	return 0;
}
