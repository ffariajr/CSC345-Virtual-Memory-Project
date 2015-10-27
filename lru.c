#include "lru.h"

void lruRepl(frame* head) {
  frame* temp;
  frame* f = head;
  frame* least = head;
  frame* leastPrev;
  while (f && f->next) {
    temp = f;
    f = f->next;
    if (least->lastUsed >= f->lastUsed) {
      leastPrev = temp;
      least = f;
    }
  }
  if (f && least->lastUsed >= f->lastUsed) {
    leastPrev = temp;
    least = f;
  }
  leastPrev->next = 0;
  least->next = head;
  head = least;
}
