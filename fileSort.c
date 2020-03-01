#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#define DEBUG 0

// Node has strings containing token and pointer to next Node
typedef struct Node {
	char* data;
	struct Node* next;
} Node;

// prints LL contents
void printLL(Node* front, int intMode) {
	Node* ptr = front;
	while (ptr != NULL) {
		if (strlen(ptr->data) == 0 && intMode) {
			printf("0\n");
		} else {
			printf("%s\n", ptr->data);
		}
		ptr = ptr->next;
	}
	return;
}

// insert 'tokenLength' chars from 'data' into node and insert node into LL
void insert(Node** frontPtr, char* data, int tokenLength) {
	int j;
	if (*frontPtr == NULL) {
		*frontPtr = malloc(sizeof(Node));
		if (!(*frontPtr)) {
			perror("Error");
		}
		(*frontPtr)->data = (char*)malloc(tokenLength+1);
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
		temp->data = (char*)malloc(tokenLength+1);
		if (temp->data == NULL) {
			perror("Error");
		}
		for (j = 0; j < tokenLength; j++) {
			(temp->data)[j] = data[j];
		}
		temp->next = *frontPtr;
		*frontPtr = temp;
	}
	return;
}

// delete front and free allocated memory
void delete(Node** frontPtr) {
        Node * temp = *frontPtr;
	while ((*frontPtr) != NULL) {
	  temp = (*frontPtr)->next;
	  free((*frontPtr)->data);
	  free((*frontPtr));
	  *frontPtr = temp;
	}
	return;
}

//comparators return 1 if 2nd argument is larger, 0 otherwise
//doesn't care about being equal
int intComp(void * a, void * b) {
  return atoi((char *) a) < atoi((char *) b);
}

int strComp(void * a, void * b) {
	char * strA = malloc(strlen((char*)a) + 2);
	char * strB = malloc(strlen((char*)b) + 2);
	memset(strA, 0, strlen((char*)a)+2);
	memset(strB, 0, strlen((char*)b)+2);
	memcpy(strA, (char*)a, strlen((char*)a));
	memcpy(strB, (char*)b, strlen((char*)b));
	
	int i = 0;
	int j = -1;
	while (strA[i] != 0 && strB[i++] != 0) {}
	while (j++ <= i) {
		if (strA[j] != strB[j]) {
			return strA[j] < strB[j] ? 1 : 0;
		}
	}
	free(strA);
	free(strB);
	return 0;
}

void * partition(void * head_in, int (*comparator)(void*, void*)) {
	Node * head = (Node *) head_in;
	Node * pvt = head;
	Node * i = head;
	Node * j;
	Node tmp;
	for (j = head; j != NULL; j = j->next) {
		if (comparator((void *) (j->data), (void *) (pvt->data))) {
			pvt = i == pvt ? j : pvt;
			tmp = *j;
			j->data = i->data;
			i->data = tmp.data;
			i = i->next;
		}
	}
	tmp = *pvt;
	pvt->data = i->data;
	i->data = tmp.data;
	return i;
}

void * quickSortHelper(void * head_in, int (*comparator)(void*, void*)) {
	Node * head = (Node *) head_in;
	if (head == NULL || head->next == NULL) {
		return head;
	}
	Node * ptr = (Node *) partition(head, comparator);
	Node * tmp = head;

	if (tmp != ptr) { //need this check?
		while (tmp->next != ptr) {
			tmp = tmp->next;
		}
		tmp->next = NULL;
		head = (Node *) quickSortHelper(head, comparator);
		tmp = head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = ptr;
	}
	ptr->next = (Node *) quickSortHelper(ptr->next, comparator);
	return head;
}


int quickSort(void * head, int (*comparator)(void*, void*)) {
	if (head == NULL) {
		return -1;
	}
	quickSortHelper(head, comparator);
	return 1;
}

int insertionSort(void * head, int (*comparator)(void *, void *)) {
	Node * edge = (Node *) head;
	Node * ptr = (Node *) head;
	Node * tmp0;
	Node tmp;
	Node tmp2;
	Node tmp3;
	while (edge->next != NULL) {
		ptr = head;
		while (ptr != edge->next && !comparator((void*) (edge->next->data), (void*) (ptr->data))) {
			ptr = ptr->next;
		}
		tmp0 = ptr;
		tmp = *(edge->next);
		tmp2 = *ptr;
		while (ptr != edge->next) {
			tmp3 = *(ptr->next);
			ptr->next->data = tmp2.data;
			tmp2 = tmp3;
			ptr = ptr->next;
		}
		tmp0->data = tmp.data;
		edge = edge->next;
				
	}
	return 1;
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
	memset(buffer, 0, 10);

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
	// function pointers to be used in sort call
	int (*intCompPtr)(void*, void*) = intComp;
	int (*strCompPtr)(void*, void*) = strComp;
	
	
	// read from file and make LL
	int newToken = 0;
	int empty = 1;
	int status = read(fd, &c, 1);
	int intMode = 0; // assume strings for now
	while (status) {
	  empty = 0;
		if (status == -1 && errno == EINTR) {
			// signal interrupted resulting in 0 bytes read before EOF, try again
			status = read(fd, &c, 1);
			continue;
		}
		if (isalpha(c) || isdigit(c) || c == '-') {
			// set intMode if int
			if (isdigit(c)) {
				intMode = 1;
			}
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
		if (head + 2 == buffer + size) {
			// reached end of buffer, realloc with double size
			nextBuffer = (char*)malloc(2 * size);
			if (nextBuffer == NULL) {
				perror("Error");
			}
			memcpy(nextBuffer, buffer, size-1);
			free(buffer);
			size *= 2;			
			buffer = nextBuffer;
		}

		head = buffer + written;
		status = read(fd, &c, 1);
	}
	if (newToken) {
		// insert one more token
		insert(&front, buffer, tokenLength);
	}
	
	// close file
	status = close(fd);
	if (status == -1) {
		perror("Error");
	}
	
	// handle file content warnings

	if (empty == 1) {
		printf("Warning: empty file!\n");
		free(buffer);
		return 0;
	}
	// call sorts here
	char a = (front->data)[0];
	int isString = isalpha(a);
	if (argv[1][1] == 'i') {
		if (isString) {
		  insertionSort((void*)front, strCompPtr);
		} else {
			insertionSort((void*)front, intCompPtr);
		}
	} else if (argv[1][1] == 'q') {
		if (isString) {
			quickSort((void*)front, strCompPtr);
		} else {
			quickSort((void*)front, intCompPtr);
		}
	}
	// print sorted LL
	printLL(front, intMode);
	
	// free all allocated memory
	free(buffer);
	while (front != NULL) {
		delete(&front);
	}
	
	return 0;
}
