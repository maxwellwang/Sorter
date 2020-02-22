#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define DEBUG 0

// Node has strings containing token and pointer to next Node
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

// insert 'tokenLength' chars from 'data' into node and insert node into LL
void insert(Node** frontPtr, char* data, int tokenLength) {
	int j;
	if (*frontPtr == NULL) {
		*frontPtr = malloc(sizeof(Node));
		if (!(*frontPtr)) {
			perror("Error");
		}
		(*frontPtr)->data = malloc(tokenLength);
		if ((*frontPtr)->data == NULL) {
			perror("Error");
		}
		for (j = 0; j < tokenLength; j++) {
			((*frontPtr)->data)[j] = data[j];
		}
		(*frontPtr)->next = NULL;
	} else {
		Node* temp = malloc(sizeof(Node));
		if (temp == NULL) {
			perror("Error");
		}
		temp->data = malloc(tokenLength);
		if (temp->data == NULL) {
			perror("Error");
		}
		for (j = 0; j < tokenLength; j++) {
			(temp->data)[j] = data[j];
		}
		temp->next = *frontPtr;
		*frontPtr = temp;
	}
}

// delete front and free allocated memory
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
	int fd = open(argv[2], O_RDONLY|O_NONBLOCK);
	if (fd == -1) {
		perror("Fatal Error");
		exit(0);
	}
	if (DEBUG) {
		printf("Flag: %s\n", argv[1]);
		printf("File Path: %s\n", argv[2]);
	}
	
	// buffer to hold each token, doubles every time limit is reached
	char* buffer = malloc(10);
	if (buffer == NULL) {
		perror("Error");
	}
	// current size of buffer
	int size = 10;
	// size of token being inserted (ignore anything after)
	int tokenLength = 0;
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
	// function pointer to be used in sort call
	int (*compPtr)(void*, void*) = comparator;
	
	
	// read from file and make LL
	int newToken = 0;
	while (read(fd, &c, 1) > 0) {
		if (isalpha(c) || isdigit(c)) {
			// add to buffer and increment written
			if (written == 0) {
				newToken = 1;
			}
			*head = c;
			written++;
			tokenLength++;
		} else if (c == ',') {
			// token complete, insert into LL
			written = 0;
			insert(&front, buffer, tokenLength);
			tokenLength = 0;
			newToken = 0;
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
	if (newToken) {
		// insert one more token
		insert(&front, buffer, tokenLength);
	}
	
	// close file
	int status = close(fd);
	if (status == -1) {
		perror("Error");
	}
	
	// handle file content warnings
	if (c == '\n' && front == NULL) {
		printf("Warning: File is empty\n");
	}
	
	// call sorts here
	if (argv[1][1] == 'i') {
		insertionSort(&front, compPtr);
	} else if (argv[1][1] == 'q') {
		quickSort(&front, compPtr);
	}
	
	// print sorted LL
	printLL(front);
	
	// free all allocated memory
	free(buffer);
	while (front != NULL) {
		delete(&front);
	}
	
	return 0;
}
