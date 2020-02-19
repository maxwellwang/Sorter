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

// insert node
void insert(Node** frontPtr, char* data) {
	if (*frontPtr == NULL) {
		*frontPtr = malloc(sizeof(Node));
		if (!(*frontPtr)) {
			perror("Error");
		}
		(*frontPtr)->data = malloc(strlen(data));
		if ((*frontPtr)->data == NULL) {
			perror("Error");
		}
		(*frontPtr)->data = data;
		(*frontPtr)->next = NULL;
	} else {
		Node* temp = malloc(sizeof(Node));
		if (temp == NULL) {
			perror("Error");
		}
		temp->data = malloc(strlen(data));
		if (temp->data == NULL) {
			perror("Error");
		}
		temp->data = data;
		temp->next = NULL;
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
	
	// buffer to hold file contents, doubles every time limit is reached
	char* buffer = malloc(10);
	if (!buffer) {
		perror("Error");
	}
	// where to write new chars
	char* head = buffer;
	// "head" is "written" bytes after "buffer"
	int written = 0;
	// reallocated buffer with double size
	char* nextBuffer;
	// front of LL
	Node* front = NULL;
	// int (*compPtr)(void*, void*) = comparator;

	
	// read from file into buffer
	while (read(fd, head, 1) > 0) {
		written++;
		
		if (head == (buffer + strlen(buffer))) {
			// reached end of buffer, realloc with double size
			nextBuffer = malloc(2 * strlen(buffer));
			if (nextBuffer == NULL) {
				perror("Error");
			}
			memcpy(nextBuffer, buffer, strlen(buffer));
			free(buffer);
			buffer = nextBuffer;
		}
		
		head = buffer + written;
	}
	
	// handle file content warnings
	if (strlen(buffer) == 0) {
		printf("Warning: File is empty\n");
	}
	if (!isalpha(buffer[0]) && !isdigit(buffer[0]) && buffer[0] != '-') {
		printf("Warning: File does not contain strings nor integers\n");
	}
	
	// close file
	int status = close(fd);
	if (status == -1) {
		perror("Error");
	}
	
	// make LL
	if (DEBUG) {
		int i;
		for (i = 0; i < written; i++) {
			printf("%c", buffer[i]);
		} 
	}
	
	// free all malloced memory
	free(buffer);
	while (front != NULL) {
		delete(&front);
	}
	
	return 0;
}
