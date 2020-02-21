#include <stdio.h>

typedef struct node_tmp {
  int value;
  struct node_tmp * next;
} Node;

void print(Node * head) {
  Node * db = head;
  for (; db != NULL; db = db->next) {
    printf("%d ", db->value);
  }
  printf("\n");
}

Node * partition(Node * head, Node * end) {
  Node * pvt = head;
  int pivot = head->value;
  Node * i = head;
  Node * j;
  int tmp;

  for (j = head; j != NULL; j = j->next) {
    if (j->value < pivot) {
      if (i == pvt) {
	pvt = j;
      }
      tmp = j->value;
      j->value = i->value;
      i->value = tmp;
      i = i->next;
    }
  }
  pvt->value = i->value;
  i->value = pivot;
  return i;
}

Node * quickSortHelper(Node * head, Node * end) {
  if (head == NULL || head->next == NULL) {
      return head;
  }
  
  Node * ptr = partition(head, end);
  Node * tmp = head;
  
  if (tmp != ptr) { //need this check?
    while (tmp->next != ptr) {
      tmp = tmp->next;
    }
    tmp->next = NULL;
    head = quickSortHelper(head, tmp);
    tmp = head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = ptr;
  }
  ptr->next = quickSortHelper(ptr->next, end);
  return head;
}


int quickSort(Node ** head) {
  if ((*head) == NULL) {
    return -1;
  }
  Node * ptr = (*head);
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  *head = quickSortHelper(*head, ptr);
  return 1;
}

int main(int argc, char * argv[]) {
  Node a = {8, NULL};
  Node b = {1, &a};
  Node c = {1, &b};
  Node d = {19999, &c};
  Node e = {1, &d};
  Node f = {-1, &e};
  Node g = {50, &f};
  Node h = {7, &g};
  Node * tmp = &h;
  if (quickSort(&tmp)) {
    Node * ptr = tmp;
    print(tmp);
  }
  return 1;
}
