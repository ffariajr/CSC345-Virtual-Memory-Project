#include "fifo.h"

void fifoRepl(frame* head) {
  frame* temp;
  frame* f = head;
  while (f && f->next) {
    temp = f;
    f = f->next;
  }
  if (f) {
    temp->next = 0;
    f->next = head;
    head = f;
  }
}
