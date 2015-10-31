#include "fifo.h"

void fifoRepl(frame** head) {
  if (v) {
    printf("<FIFO Replacement>\n");
  }

  frame* prev = 0;
  frame* temp = *head;
  while (temp && temp->next) {
    if (v) {
      printf("Allocated [ < %d , %d > ]\n", temp->pid, temp->page);
    }
    prev = temp;
    temp = temp->next;
  }
  if (prev && temp) {
    prev->next = 0;
    temp->next = *head;
    *head = temp;
  }
  if (v) {
    printf("<\\FIFO Replacement>\n");
  }
}
