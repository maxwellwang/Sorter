#include <stdio.h>


typedef struct node_tmp {
  int value;
  struct node_tmp * next;
} Node;


//int comparator(void * node1, node * node2) {
//  char * num = "0123456789-";
//  //empty string?
//  int i = 0;
//  int isNum = 0;
//  for (; i < 11; i++) {
//    if (num[i] == (((Node *)node1)->data)[0]) {
//      isNum = 1;
//      break;
//    }
//  }
//
//  if (isNum) {
//    if (((Node *) node1)->data == ((Node *) node2)->data) {
//      return 0;
//    }
//    return ((Node *) node1)->data > ((Node *) node2)->data ? 1 : -1;
//  }
//}
//
Node * partition(Node * head, Node * end, Node ** nextHead, Node ** nextEnd) {
  Node * pvt = head;
  Node * i = head;
  Node * j;
  int tmp;
  for (j = head; j != NULL; j = j->next) {
    if (j->value < pvt->value) {
      tmp = j->value;
      j->value = pvt->value;
      pvt->value = tmp;
      i = i->next;
    }
  }
  tmp = pvt->value;
  i->value = pvt->value;
  pvt->value = tmp;
  (*nextHead) = head;
  (*nextEnd) = end;
  return i;
}

Node * quickSortHelper(Node * head, Node * end) {
  if (head == NULL || head->next == NULL) {
    return head;
  }

  Node * nextHead;
  Node * nextEnd;
  Node * ptr = partition(head, end, &nextHead, &nextEnd);

  Node * tmp = nextHead;
  while (tmp->next != end) {
    printf("1");
    tmp = tmp->next;
  }
  tmp->next = NULL;
  nextHead = quickSortHelper(nextHead, tmp);
  tmp = nextHead;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = ptr;
  
  ptr->next = quickSortHelper(ptr->next, nextEnd);

  return nextHead;
}

int quickSort(Node ** head) {
  if ((*head) == NULL) {
    return -1;
  }
  Node * ptr = (*head)->next;
  while (ptr != NULL) {
    printf("2");
    ptr = ptr->next;
  }
  *head = quickSortHelper(*head, ptr);
  return 1;
}

int main() {
  Node a = {1, NULL};
  Node b = {2, &a};
  Node c = {3, &b};
  Node * tmp = &c;
  quickSort(&tmp);
  Node * ptr = tmp;
  for (; ptr != NULL; ptr = ptr->next) {
    printf("%d ", ptr->value);
  }
  return 1;
}
