#include "lru.h"

void lruRepl(frame** head) {
  if (v) {
    printf("<LRU Replacement>\n");
  }

  frame* leastPrev = 0;
  int lastUsed = ~(1 << ((sizeof(int)*8) -1));

  frame* temp = *head;
  frame* prev = 0;
  while (temp && temp->next) {
    if (prev && lastUsed > temp->lastUsed) {
      if (v) {
        printf("Found Smaller: [ < %4d , %3d > , %5d ]\n", temp->pid, temp->page, temp->lastUsed);
      }
      leastPrev = prev;
      lastUsed = temp->lastUsed;
    }
    prev = temp;
    temp = temp->next;
  }
  if (leastPrev) {
    temp = leastPrev->next;
    leastPrev->next = temp->next;
    temp->next = *head;
    *head = temp;
  }

  if (v) {
    printf("<\\LRU Replacement>\n");
  }
}
