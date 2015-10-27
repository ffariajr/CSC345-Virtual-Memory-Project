#include "frame.h"

frame* findFrame(frame* list, int pid, char page) {
  frame* temp = list;
  while (temp) {
    if (temp->pid == pid && temp->page == page) {
      return temp;
    }
    temp = temp->next;
  }
  return 0;
}

frame* frameInit() {
  frame* new = (frame*) malloc(sizeof(frame));
  new->pid = -1;
  new->page = -1;
  new->lastUsed = 0;
  new->next = 0;
  return new;
}

void updateFrame(frame* f) {
  f->lastUsed = 0;
}

void incrementFrames(frame* list) {
  while (list && list->next) {
    list->lastUsed++;
    list = list->next;
  }
  if (list) {
    list->lastUsed++;
  }
}
