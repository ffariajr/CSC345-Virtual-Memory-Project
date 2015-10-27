#include "2c.h"

void c2Repl(frame* head) {
  frame* temp = 0;
  frame* tempPrev;
  frame* f = head;
  frame* fPrev;

  while (f) {
    if (f->lastUsed) {
      temp = f;
      tempPrev = fPrev;
    }
    fPrev = f;
    f = f->next;
  }

  if (!temp) {
    temp = f;
    tempPrev = fPrev;
  }

  tempPrev->next = 0;
  temp->next = head;
  head = temp;
}
