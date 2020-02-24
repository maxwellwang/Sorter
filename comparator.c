#include <stdio.h>

typedef struct node_tmp {
  int data;
  //  char * data;
  struct node_tmp * next;
} Node;



void print(Node * head) {
  Node * db = head;
  for (; db != NULL; db = db->next) {
    printf("%d ", db->data);
  }
  printf("\n");
}

//comparators return 1 if 2nd argument is larger, 0 otherwise
//doesn't care about being equal
int intComp(void * a, void * b) {
  return *((int *) a) < *((int * ) b) ? 1 : 0;
}

int strComp(void * a, void * b) {
  char * strA = (char *) a;
  char * strB = (char *) b;
  int i = 0;
  int j = -1;

  while (strA[i] != 0 && strB[i++] != 0) {}
  while (j++ <= i) {
    if (strA[j] != strB[j]) {
      return strA[j] < strB[j] ? 1 : 0;
    }
  }
  return 0;
}

void * partition(void * head_in, void * end_in, int (*comparator)(void*, void*)) {
  Node * head = (Node *) head_in;
  Node * pvt = head;
  Node * i = head;
  Node * j;
  Node tmp;
  for (j = head; j != NULL; j = j->next) {
    if (comparator((void *) &(j->data), (void *) &(pvt->data))) {
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

void * quickSortHelper(void * head_in, void * end_in, int (*comparator)(void*, void*)) {
  Node * head = (Node *) head_in;
  Node * end = (Node *) end_in;
  if (head == NULL || head->next == NULL) {
      return head;
  }
  Node * ptr = (Node *) partition(head, end, comparator);
  Node * tmp = head;
  
  if (tmp != ptr) { //need this check?
    while (tmp->next != ptr) {
      tmp = tmp->next;
    }
    tmp->next = NULL;
    head = (Node *) quickSortHelper(head, tmp, comparator);
    tmp = head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = ptr;
  }
  ptr->next = (Node *) quickSortHelper(ptr->next, end, comparator);
  return head;
}


int quickSort(void * head, int (*comparator)(void*, void*)) {
  if (head == NULL) {
    return -1;
  }
  Node * ptr = (Node *) head;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  quickSortHelper(head, ptr, comparator);
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
    while (ptr != edge->next && !comparator((void*) &(edge->next->data), (void*) &(ptr->data))) {
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


int main(int argc, char * argv[]) {
  int (*intCompare)(void*, void*) = intComp;
  //int (*strCompare)(void*, void*) = strComp;
  Node a1 = {8, NULL};
  Node b1 = {1, &a1};
  Node c1 = {1, &b1};
  Node d1 = {19999, &c1};
  Node e1 = {1, &d1};
  Node f1 = {-1, &e1};
  Node g1 = {50, &f1};
  Node h1 = {7, &g1};
// Node a = {"hi", NULL};
// Node b = {"bye", &a};
// Node c = {"by", &b};
// Node d = {"byeee", &c};
// Node e = {"", &d};
// Node f = {"z", &e};
// Node g = {"h", &f};
// Node h = {"asa", &g};
  
//  Node * tmp = &h;
  Node * tmp1 = &h1;
//  if (quickSort((void *) tmp, strCompare)) {
//    print(tmp);
//  }
  if (insertionSort((void *) tmp1, intCompare)) {
    print(tmp1);
  }
  return 0;
}
