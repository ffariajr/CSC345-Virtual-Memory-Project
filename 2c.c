#include "2c.h"

void c2Repl(frame** head) {
  if (v) {
    printf("<2C Replacement>\n");
  }

  frame* fifo2c = 0;

  frame* temp = *head;
  frame* prev = 0;
  while (temp) {
    if (prev && temp->lastUsed) {
      if (v) {
        printf("Found Older Unused: [ < %4d , %3d > , %5d ]\n", temp->pid, temp->page, temp->lastUsed);
      }
      fifo2c = prev;
    }
    prev = temp;
    temp = temp->next;
  }
  if (fifo2c) {
    temp = fifo2c->next;
    fifo2c->next = temp->next;
    temp->next = *head;
    *head = temp;
  }

  if (v) {
    printf("<\\2C Replacement>\n");
  }
}


void grantChance(void* data) {
  int tqs = ((c2*) data)->counter++;
  if (!(tqs % 5)) {
    frame* f = ((c2*) data)->f;

    while (f) {
      f->lastUsed = 1;
      f = f->next;
    }
  }
}
