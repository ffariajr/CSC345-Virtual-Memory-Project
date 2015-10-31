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


int grantChance(void* data) {
  if (v) {
    printf("<Grant 2nd Chance>\n");
  }
  int tqs = ((c2*) data)->counter++;
  if (!((((c2*) data)->counter++) % (((c2*) data)->forgiveness))) {
    frame* f = *((c2*) data)->f;
    if (v) {
      printf("Feeling Generous\n");
    }
    while (f) {
      if (v) {
        printf("Second Chance Granted: [ < %4d , %3d > , %5d ]\n", f->pid, f->page, f->lastUsed);
      }
      f->lastUsed = 1;
      f = f->next;
    }
  }
  if (v) {
    printf("Time Quantums Until Next Generosity: %d\n", (((c2*) data)->forgiveness) - ((((c2*) data)->counter++) % (((c2*) data)->forgiveness)));
    printf("<\\Grant 2nd Chance>\n");
  }
  return 0;
}
